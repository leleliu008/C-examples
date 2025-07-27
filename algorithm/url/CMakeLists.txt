cmake_minimum_required(VERSION 3.15)

project(url C)

set(PROJECT_VERSION 1.0.0)

add_library(url-static STATIC src/lib/url.c)
add_library(url-shared SHARED src/lib/url.c)

set_target_properties(url-static PROPERTIES OUTPUT_NAME url CLEAN_DIRECT_OUTPUT 1)
set_target_properties(url-shared PROPERTIES OUTPUT_NAME url CLEAN_DIRECT_OUTPUT 1)

add_executable(url src/main/url.c)
target_link_libraries(url url-static)
target_include_directories(url PUBLIC src/lib)

configure_file(src/lib/url.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/liburl.pc @ONLY)

include(GNUInstallDirs)
install(TARGETS url        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS url-static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS url-shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   liburl.pc           DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(FILES   src/lib/url.h       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CTest)
if (ENABLE_TESTING)
    add_executable(url-test src/test/url.c)
    target_include_directories(url-test PRIVATE src/lib)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
    include(FindCUnit)
    if (CUNIT_FOUND)
        target_include_directories(url-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(     url-test url-static)
        target_link_libraries(     url-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME url-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/url-test)
endif()
