cmake_minimum_required(VERSION 3.0.0)

project(url C)

set(PROJECT_VERSION 1.0.0)

configure_file(url.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/url.pc @ONLY)

include_directories(src/include)

add_library(url_static STATIC src/lib/url.c)
set_target_properties(url_static PROPERTIES OUTPUT_NAME url)
set_target_properties(url_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_library(url_shared SHARED src/lib/url.c)
set_target_properties(url_shared PROPERTIES OUTPUT_NAME url)
set_target_properties(url_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_executable(url src/main/url.c)
target_link_libraries(url url_static)

include(GNUInstallDirs)
install(TARGETS url        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS url_static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS url_shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   FindURL.cmake       DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
install(FILES   url.pc              DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

include(CTest)
if (ENABLE_TESTING)
    add_executable(url-test src/test/test.c)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
    include(FindCUnit)
    if (CUNIT_FOUND)
        target_include_directories(url-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(url-test url_static)
        target_link_libraries(url-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME url-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/url-test)
endif()
