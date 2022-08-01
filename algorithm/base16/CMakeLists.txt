cmake_minimum_required(VERSION 3.0.0)

project(base16 C)

set(PROJECT_VERSION       1.0.0)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

########################################################################################

add_library(base16-static STATIC src/lib/base16.c)
add_library(base16-shared SHARED src/lib/base16.c)

set_target_properties(base16-static PROPERTIES OUTPUT_NAME base16 CLEAN_DIRECT_OUTPUT 1 EXPORT_NAME static)
set_target_properties(base16-shared PROPERTIES OUTPUT_NAME base16 CLEAN_DIRECT_OUTPUT 1 EXPORT_NAME shared)

########################################################################################

add_executable(base16 src/main/base16.c)
target_link_libraries(base16 base16-static)
target_include_directories(base16 PRIVATE src/lib)

########################################################################################

include(GNUInstallDirs)

install(TARGETS base16        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES   src/lib/base16.h       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

########################################################################################

configure_file(src/lib/base16.pc.in base16.pc @ONLY)
install(
    FILES       "${CMAKE_CURRENT_BINARY_DIR}/base16.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

########################################################################################

set(CMAKE_INSTALL_CONFIGDIR "${CMAKE_INSTALL_LIBDIR}/cmake/base16")

install(
    TARGETS     base16-static base16-shared
    EXPORT      base16Targets
    ARCHIVE
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(
    EXPORT      base16Targets
    FILE        base16Targets.cmake
    NAMESPACE   base16::
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}"
)

########################################################################################

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/base16ConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)
install(
    FILES       "${CMAKE_CURRENT_BINARY_DIR}/base16ConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/base16Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/base16Config.cmake"
    INSTALL_DESTINATION  "${CMAKE_INSTALL_CONFIGDIR}"
)
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/base16Config.cmake"
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}"
)

########################################################################################

include(CTest)
if (ENABLE_TESTING)
    add_executable(base16-test src/test/base16.c)
    target_include_directories(base16-test PRIVATE src/lib)
    include(src/test/FindCUnit.cmake)
    if (CUNIT_FOUND)
        target_include_directories(base16-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(base16-test base16-static)
        target_link_libraries(base16-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME base16-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/base16-test)
endif()
