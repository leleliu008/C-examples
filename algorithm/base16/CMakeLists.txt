cmake_minimum_required(VERSION 3.0.0)

project(base16 C)

set(PROJECT_VERSION 1.0.0)

add_library(base16-static STATIC src/lib/base16.c)
add_library(base16-shared SHARED src/lib/base16.c)

set_target_properties(base16-static PROPERTIES OUTPUT_NAME base16 CLEAN_DIRECT_OUTPUT 1)
set_target_properties(base16-shared PROPERTIES OUTPUT_NAME base16 CLEAN_DIRECT_OUTPUT 1)

add_executable(base16 src/main/base16.c)
target_link_libraries(base16 base16-static)
target_include_directories(base16 PRIVATE src/lib)

configure_file(src/lib/base16.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/libbase16.pc @ONLY)

include(GNUInstallDirs)
install(TARGETS base16        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS base16-static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS base16-shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   libbase16.pc           DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(FILES   src/lib/base16.h       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CTest)
if (ENABLE_TESTING)
    add_executable(base16-test src/test/base16.c)
    target_include_directories(base16-test PRIVATE src/lib)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
    include(FindCUnit)
    if (CUNIT_FOUND)
        target_include_directories(base16-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(base16-test base16-static)
        target_link_libraries(base16-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME base16-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/base16-test)
endif()
