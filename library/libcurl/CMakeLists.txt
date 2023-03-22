cmake_minimum_required(VERSION 3.0.0)

project(http C)

set(PROJECT_VERSION       1.0.0)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

include_directories(src/include)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

find_package(PkgConfig REQUIRED)

# https://cmake.org/cmake/help/latest/module/FindCURL.html
# https://cmake.org/cmake/help/latest/module/FindOpenSSL.html
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

########################################################################################

add_library(http-static STATIC src/lib/http.c)
add_library(http-shared SHARED src/lib/http.c)

set_target_properties(http-static PROPERTIES OUTPUT_NAME http CLEAN_DIRECT_OUTPUT 1 EXPORT_NAME static)
set_target_properties(http-shared PROPERTIES OUTPUT_NAME http CLEAN_DIRECT_OUTPUT 1 EXPORT_NAME shared)

target_link_libraries(http-static CURL::libcurl)
target_link_libraries(http-shared CURL::libcurl)

target_link_libraries(http-static OpenSSL::SSL)
target_link_libraries(http-shared OpenSSL::SSL)

target_include_directories(http-static PRIVATE ${CURL_INCLUDE_DIRS})
target_include_directories(http-shared PRIVATE ${CURL_INCLUDE_DIRS})

########################################################################################

add_executable(http src/main/http.c)
target_link_libraries(http http-static)
target_link_libraries(http CURL::libcurl)
target_link_libraries(http OpenSSL::SSL)

########################################################################################

include(GNUInstallDirs)

########################################################################################

configure_file(src/lib/http.pc.in http.pc @ONLY)
install(
    FILES       "${CMAKE_CURRENT_BINARY_DIR}/http.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

########################################################################################

set(CMAKE_INSTALL_CONFIGDIR "${CMAKE_INSTALL_LIBDIR}/cmake/http")

install(
    TARGETS     http-static http-shared
    EXPORT      httpTargets
    ARCHIVE
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(
    EXPORT      httpTargets
    FILE        httpTargets.cmake
    NAMESPACE   http::
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}"
)

########################################################################################

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/httpConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES       "${CMAKE_CURRENT_BINARY_DIR}/httpConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/httpConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/httpConfig.cmake"
    INSTALL_DESTINATION  "${CMAKE_INSTALL_CONFIGDIR}"
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/httpConfig.cmake"
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}"
)

########################################################################################

install(TARGETS http        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS http-static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS http-shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})

########################################################################################

include(CTest)
if (ENABLE_TESTING)
    add_executable(http-test src/test/http.c)
    include(src/test/FindCUnit.cmake)
    if (CUNIT_FOUND)
        target_include_directories(http-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(http-test http-static)
        target_link_libraries(http-test CURL::libcurl)
        target_link_libraries(http-test OpenSSL::SSL)
        target_link_libraries(http-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME http-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/http-test)
endif()
