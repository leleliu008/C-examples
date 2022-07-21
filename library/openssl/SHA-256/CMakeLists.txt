cmake_minimum_required(VERSION 3.0.0)

project(sha256sum C)

set(PROJECT_VERSION       1.0.0)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

include_directories(src/include)

find_package(OpenSSL REQUIRED)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

########################################################################################

add_library(sha256sum-static STATIC src/lib/sha256sum.c)
add_library(sha256sum-shared SHARED src/lib/sha256sum.c)

set_target_properties(sha256sum-static PROPERTIES OUTPUT_NAME sha256sum CLEAN_DIRECT_OUTPUT 1 EXPORT_NAME static)
set_target_properties(sha256sum-shared PROPERTIES OUTPUT_NAME sha256sum CLEAN_DIRECT_OUTPUT 1 EXPORT_NAME shared)

target_link_libraries(sha256sum-static OpenSSL::Crypto)
target_link_libraries(sha256sum-shared OpenSSL::Crypto)

########################################################################################

add_executable(sha256sum src/main/sha256sum.c)
target_link_libraries(sha256sum sha256sum-static)
target_link_libraries(sha256sum OpenSSL::Crypto)

########################################################################################

include(GNUInstallDirs)

########################################################################################

configure_file(src/lib/sha256sum.pc.in sha256sum.pc @ONLY)
install(
    FILES       "${CMAKE_CURRENT_BINARY_DIR}/sha256sum.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

########################################################################################

set(CMAKE_INSTALL_CONFIGDIR "${CMAKE_INSTALL_LIBDIR}/cmake/sha256sum")

install(
    TARGETS     sha256sum-static sha256sum-shared
    EXPORT      sha256sumTargets
    ARCHIVE
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(
    EXPORT      sha256sumTargets
    FILE        sha256sumTargets.cmake
    NAMESPACE   sha256sum::
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}"
)

########################################################################################

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/sha256sumConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES       "${CMAKE_CURRENT_BINARY_DIR}/sha256sumConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/sha256sumConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sha256sumConfig.cmake"
    INSTALL_DESTINATION  "${CMAKE_INSTALL_CONFIGDIR}"
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/sha256sumConfig.cmake"
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}"
)

########################################################################################

install(TARGETS sha256sum        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS sha256sum-static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sha256sum-shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})

########################################################################################

include(CTest)
if (ENABLE_TESTING)
    add_executable(sha256sum-test src/test/sha256sum.c)
    include(src/test/FindCUnit.cmake)
    if (CUNIT_FOUND)
        target_include_directories(sha256sum-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(sha256sum-test sha256sum-static)
        target_link_libraries(sha256sum-test OpenSSL::Crypto)
        target_link_libraries(sha256sum-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME sha256sum-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/sha256sum-test)
endif()
