cmake_minimum_required(VERSION 3.0.0)

project(chinese-calendar C)

set(PROJECT_VERSION 1.0.0)

add_library(chinese-calendar-static STATIC src/lib/chinese-calendar.c)
add_library(chinese-calendar-shared SHARED src/lib/chinese-calendar.c)

set_target_properties(chinese-calendar-static PROPERTIES OUTPUT_NAME chinese-calendar CLEAN_DIRECT_OUTPUT 1)
set_target_properties(chinese-calendar-shared PROPERTIES OUTPUT_NAME chinese-calendar CLEAN_DIRECT_OUTPUT 1)

add_executable(chinese-calendar src/main/chinese-calendar.c)
target_link_libraries(chinese-calendar chinese-calendar-static)
target_include_directories(chinese-calendar PRIVATE src/lib)

configure_file(src/lib/chinese-calendar.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/libchinese-calendar.pc @ONLY)

include(GNUInstallDirs)
install(TARGETS chinese-calendar        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS chinese-calendar-static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS chinese-calendar-shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   libchinese-calendar.pc           DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(FILES   src/lib/chinese-calendar.h       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CTest)
if (ENABLE_TESTING)
    add_executable(chinese-calendar-test src/test/chinese-calendar.c)
    target_include_directories(chinese-calendar-test PRIVATE src/lib)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
    include(FindCUnit)
    if (CUNIT_FOUND)
        target_include_directories(chinese-calendar-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(chinese-calendar-test chinese-calendar-static)
        target_link_libraries(chinese-calendar-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME chinese-calendar-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/chinese-calendar-test)
endif()
