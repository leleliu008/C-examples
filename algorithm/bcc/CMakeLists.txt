cmake_minimum_required(VERSION 3.0.0)

project(bcc C)

set(PROJECT_VERSION 1.0.0)

configure_file(libbcc.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/libbcc.pc @ONLY)

include_directories(src/include)

add_library(bcc_static STATIC src/lib/bcc.c)
set_target_properties(bcc_static PROPERTIES OUTPUT_NAME bcc)
set_target_properties(bcc_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_library(bcc_shared SHARED src/lib/bcc.c)
set_target_properties(bcc_shared PROPERTIES OUTPUT_NAME bcc)
set_target_properties(bcc_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_executable(bccsum src/main/bccsum.c ../base16/src/lib/base16.c)
target_include_directories(bccsum PRIVATE ../base16/src/include)
target_link_libraries(bccsum bcc_static)

include(GNUInstallDirs)
install(TARGETS bccsum     RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS bcc_static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS bcc_shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   FindLIBBCC.cmake    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
install(FILES   libbcc.pc           DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

include(CTest)
if (ENABLE_TESTING)
    add_executable(bcc-test src/test/test.c)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
    include(FindCUnit)
    if (CUNIT_FOUND)
        target_include_directories(bcc-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(bcc-test bcc_static)
        target_link_libraries(bcc-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME bcc-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bcc-test)
endif()
