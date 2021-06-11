cmake_minimum_required(VERSION 3.0.0)

project(base64 C)

set(PROJECT_VERSION 1.0.0)

configure_file(base64.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/base64.pc @ONLY)

include_directories(src/include)

add_library(base64_static STATIC src/lib/base64.c src/lib/base64_mbedtls.c)
set_target_properties(base64_static PROPERTIES OUTPUT_NAME base64)
set_target_properties(base64_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_library(base64_shared SHARED src/lib/base64.c src/lib/base64_mbedtls.c)
set_target_properties(base64_shared PROPERTIES OUTPUT_NAME base64)
set_target_properties(base64_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_executable(base64 src/main/base64.c)
target_link_libraries(base64 base64_static)

include(GNUInstallDirs)
install(TARGETS base64        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS base64_static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS base64_shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   FindBase64.cmake       DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
install(FILES   base64.pc              DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

include(CTest)
if (ENABLE_TESTING)
    add_executable(base64-test src/test/test.c)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
    include(FindCUnit)
    if (CUNIT_FOUND)
        target_include_directories(base64-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(base64-test base64_static)
        target_link_libraries(base64-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME base64-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/base64-test)
endif()
