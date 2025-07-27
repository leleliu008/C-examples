cmake_minimum_required(VERSION 3.15)

project(base64 C)

set(PROJECT_VERSION 1.0.0)

include_directories(src/include)

########################################################################################

add_library(base64-static STATIC src/lib/base64.c src/lib/base64_mbedtls.c)
add_library(base64-shared SHARED src/lib/base64.c src/lib/base64_mbedtls.c)

set_target_properties(base64-static PROPERTIES OUTPUT_NAME base64 CLEAN_DIRECT_OUTPUT 1)
set_target_properties(base64-shared PROPERTIES OUTPUT_NAME base64 CLEAN_DIRECT_OUTPUT 1)

########################################################################################

add_executable(base64-encode src/main/base64-encode.c)
add_executable(base64-decode src/main/base64-decode.c)

target_link_libraries(base64-encode base64-static)
target_link_libraries(base64-decode base64-static)

########################################################################################

configure_file(src/lib/base64.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/base64.pc @ONLY)

########################################################################################

include(GNUInstallDirs)
install(TARGETS base64-encode RUNTIME COMPONENT bin DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS base64-decode RUNTIME COMPONENT bin DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS base64-static ARCHIVE COMPONENT lib DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS base64-shared LIBRARY COMPONENT lib DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   base64.pc             COMPONENT dev DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(FILES   src/include/base64.h  COMPONENT dev DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

########################################################################################

include(CTest)
if (ENABLE_TESTING)
    add_executable(base64-test src/test/base64.c)
    include(src/test/FindCUnit.cmake)
    if (CUNIT_FOUND)
        target_include_directories(base64-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(base64-test base64-static)
        target_link_libraries(base64-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME base64-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/base64-test)
endif()
