cmake_minimum_required(VERSION 3.0.0)

project(untar C)

set(PROJECT_VERSION       1.0.0)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

include_directories(src/include)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

find_package(PkgConfig  REQUIRED)
find_package(LibArchive REQUIRED)

########################################################################################

add_library(untar-static STATIC src/lib/untar.c)
add_library(untar-shared SHARED src/lib/untar.c)

set_target_properties(untar-static PROPERTIES OUTPUT_NAME untar CLEAN_DIRECT_OUTPUT 1 EXPORT_NAME static)
set_target_properties(untar-shared PROPERTIES OUTPUT_NAME untar CLEAN_DIRECT_OUTPUT 1 EXPORT_NAME shared)

target_link_libraries(untar-static LibArchive::LibArchive)
target_link_libraries(untar-shared LibArchive::LibArchive)

########################################################################################

add_executable(untar src/main/untar.c)
target_link_libraries(untar untar-static)

########################################################################################

include(GNUInstallDirs)

########################################################################################

configure_file(src/lib/untar.pc.in untar.pc @ONLY)
install(
    FILES       "${CMAKE_CURRENT_BINARY_DIR}/untar.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

########################################################################################

set(CMAKE_INSTALL_CONFIGDIR "${CMAKE_INSTALL_LIBDIR}/cmake/untar")

install(
    TARGETS     untar-static untar-shared
    EXPORT      untarTargets
    ARCHIVE
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(
    EXPORT      untarTargets
    FILE        untarTargets.cmake
    NAMESPACE   untar::
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}"
)

########################################################################################

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/untarConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES       "${CMAKE_CURRENT_BINARY_DIR}/untarConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/untarConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/untarConfig.cmake"
    INSTALL_DESTINATION  "${CMAKE_INSTALL_CONFIGDIR}"
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/untarConfig.cmake"
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}"
)

########################################################################################

install(TARGETS untar        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS untar-static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS untar-shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})

########################################################################################

include(CTest)
if (ENABLE_TESTING)
    add_executable(untar-test src/test/untar.c)
    include(src/test/FindCUnit.cmake)
    if (CUNIT_FOUND)
        target_include_directories(untar-test PRIVATE "${LIBARCHIVE_INCLUDE_DIR}")
        target_include_directories(untar-test PRIVATE "${CUNIT_INCLUDE_DIR}")
        target_link_libraries(untar-test untar-static)
        target_link_libraries(untar-test "${LIBARCHIVE_LIBRARY}")
        target_link_libraries(untar-test "${CUNIT_LIBRARY}")
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME untar-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/untar-test)
endif()
