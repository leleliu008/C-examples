cmake_minimum_required(VERSION 3.0.0)

project(chinese-calendar C)

set(PROJECT_VERSION 1.0.0)

configure_file(chinese-calendar.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/chinese-calendar.pc @ONLY)

include_directories(src/include)

add_library(chinese-calendar_static STATIC src/lib/chinese-calendar.c)
set_target_properties(chinese-calendar_static PROPERTIES OUTPUT_NAME chinese-calendar)
set_target_properties(chinese-calendar_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_library(chinese-calendar_shared SHARED src/lib/chinese-calendar.c)
set_target_properties(chinese-calendar_shared PROPERTIES OUTPUT_NAME chinese-calendar)
set_target_properties(chinese-calendar_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_executable(chinese-calendar src/main/chinese-calendar.c)
target_link_libraries(chinese-calendar chinese-calendar_static)

include(GNUInstallDirs)
install(TARGETS chinese-calendar        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS chinese-calendar_static ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS chinese-calendar_shared LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   FindChineseCalendar.cmake        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
install(FILES   chinese-calendar.pc              DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

include(CTest)
if (ENABLE_TESTING)
    add_executable(chinese-calendar-test src/test/test.c)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
    include(FindCUnit)
    if (CUNIT_FOUND)
        target_include_directories(chinese-calendar-test PRIVATE ${CUNIT_INCLUDE_DIR})
        target_link_libraries(chinese-calendar-test chinese-calendar_static)
        target_link_libraries(chinese-calendar-test ${CUNIT_LIBRARY})
    else()
        message(FATAL_ERROR "Couldn't find CUnit library.")
    endif()
    add_test(NAME chinese-calendar-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/chinese-calendar-test)
endif()
