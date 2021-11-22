cmake_minimum_required(VERSION 3.0.0)

project(lrc C)

set(PROJECT_VERSION 1.0.0)

add_library(lrc-static STATIC src/lib/lrc.c)
add_library(lrc-shared SHARED src/lib/lrc.c)

set_target_properties(lrc-static PROPERTIES OUTPUT_NAME lrc CLEAN_DIRECT_OUTPUT 1)
set_target_properties(lrc-shared PROPERTIES OUTPUT_NAME lrc CLEAN_DIRECT_OUTPUT 1)

add_executable(lrcsum src/main/lrcsum.c ../base16/src/lib/base16.c)
target_include_directories(lrcsum PRIVATE ../base16/src/lib)
target_include_directories(lrcsum PRIVATE src/lib)
target_link_libraries(lrcsum lrc-static)

configure_file(src/lib/lrc.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/liblrc.pc @ONLY)

include(GNUInstallDirs)
install(TARGETS lrcsum     RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS lrc-static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS lrc-shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   liblrc.pc           DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(FILES   src/lib/lrc.h       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CTest)
if (ENABLE_TESTING)
    add_executable(lrc-test src/test/lrc.c)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
    include(FindCUnit)
    if (CUNIT_FOUND)
        target_include_directories(lrc-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(lrc-test lrc-static)
        target_link_libraries(lrc-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME lrc-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/lrc-test)
endif()
