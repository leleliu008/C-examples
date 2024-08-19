cmake_minimum_required(VERSION 3.0.0)

project(sysinfo C)

set(PROJECT_VERSION       1.0.0)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

########################################################################################

add_library(sysinfo-static STATIC src/lib/sysinfo.c)
add_library(sysinfo-shared SHARED src/lib/sysinfo.c)

set_target_properties(sysinfo-static PROPERTIES OUTPUT_NAME sysinfo CLEAN_DIRECT_OUTPUT 1 EXPORT_NAME static)
set_target_properties(sysinfo-shared PROPERTIES OUTPUT_NAME sysinfo CLEAN_DIRECT_OUTPUT 1 EXPORT_NAME shared)

########################################################################################

add_executable(sysinfo src/main/sysinfo.c)
target_link_libraries(sysinfo sysinfo-static)
target_include_directories(sysinfo PRIVATE src/lib)

########################################################################################

include(GNUInstallDirs)

install(TARGETS sysinfo RUNTIME   COMPONENT bin DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES   src/lib/sysinfo.h COMPONENT dev DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

########################################################################################

configure_file(src/lib/sysinfo.pc.in sysinfo.pc @ONLY)
install(
    FILES       "${CMAKE_CURRENT_BINARY_DIR}/sysinfo.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
    COMPONENT dev
)

########################################################################################

set(CMAKE_INSTALL_CONFIGDIR "${CMAKE_INSTALL_LIBDIR}/cmake/sysinfo")

install(
    TARGETS     sysinfo-static sysinfo-shared
    EXPORT      sysinfoTargets
    ARCHIVE
    COMPONENT   lib
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(
    EXPORT      sysinfoTargets
    FILE        sysinfoTargets.cmake
    NAMESPACE   sysinfo::
    COMPONENT   dev
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}"
)

########################################################################################

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/sysinfoConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)
install(
    FILES       "${CMAKE_CURRENT_BINARY_DIR}/sysinfoConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}"
    COMPONENT dev
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/sysinfoConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sysinfoConfig.cmake"
    INSTALL_DESTINATION  "${CMAKE_INSTALL_CONFIGDIR}"
)
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/sysinfoConfig.cmake"
    DESTINATION "${CMAKE_INSTALL_CONFIGDIR}"
    COMPONENT dev
)

########################################################################################

include(CTest)
if (ENABLE_TESTING)
    add_executable(sysinfo-test src/test/sysinfo.c)
    target_include_directories(sysinfo-test PRIVATE src/lib)
    include(src/test/FindCUnit.cmake)
    if (CUNIT_FOUND)
        target_include_directories(sysinfo-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(sysinfo-test sysinfo-static)
        target_link_libraries(sysinfo-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME sysinfo-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/sysinfo-test)
endif()
