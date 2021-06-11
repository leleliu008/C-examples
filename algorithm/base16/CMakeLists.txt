cmake_minimum_required(VERSION 3.0.0)

project(base16 C)

set(PROJECT_VERSION 1.0.0)

configure_file(base16.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/base16.pc @ONLY)

include_directories(src/include)

add_library(base16_static STATIC src/lib/base16.c)
set_target_properties(base16_static PROPERTIES OUTPUT_NAME base16)
set_target_properties(base16_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_library(base16_shared SHARED src/lib/base16.c)
set_target_properties(base16_shared PROPERTIES OUTPUT_NAME base16)
set_target_properties(base16_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_executable(base16 src/main/base16.c)
target_link_libraries(base16 base16_static)

include(GNUInstallDirs)
install(TARGETS base16        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS base16_static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS base16_shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   FindBase16.cmake       DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
install(FILES   base16.pc              DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

include(CTest)
if (ENABLE_TESTING)
    add_executable(base16-test src/test/test.c)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
    include(FindCUnit)
    if (CUNIT_FOUND)
        target_include_directories(base16-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(base16-test base16_static)
        target_link_libraries(base16-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME base16-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/base16-test)
endif()
