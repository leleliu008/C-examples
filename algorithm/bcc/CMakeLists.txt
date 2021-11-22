cmake_minimum_required(VERSION 3.0.0)

project(bcc C)

set(PROJECT_VERSION 1.0.0)

add_library(bcc-static STATIC src/lib/bcc.c)
add_library(bcc-shared SHARED src/lib/bcc.c)

set_target_properties(bcc-static PROPERTIES OUTPUT_NAME bcc CLEAN_DIRECT_OUTPUT 1)
set_target_properties(bcc-shared PROPERTIES OUTPUT_NAME bcc CLEAN_DIRECT_OUTPUT 1)

add_executable(bccsum src/main/bccsum.c ../base16/src/lib/base16.c)
target_include_directories(bccsum PRIVATE ../base16/src/lib)
target_include_directories(bccsum PRIVATE src/lib)
target_link_libraries(bccsum bcc-static)

configure_file(src/lib/bcc.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/libbcc.pc @ONLY)

include(GNUInstallDirs)
install(TARGETS bccsum     RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS bcc-static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS bcc-shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   libbcc.pc           DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(FILES   src/lib/bcc.h       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CTest)
if (ENABLE_TESTING)
    add_executable(bcc-test src/test/bcc.c)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
    include(FindCUnit)
    if (CUNIT_FOUND)
        target_include_directories(bcc-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(bcc-test bcc-static)
        target_link_libraries(bcc-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME bcc-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bcc-test)
endif()
