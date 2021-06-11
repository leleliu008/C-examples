cmake_minimum_required(VERSION 3.0.0)

project(qrencode C)

set(PROJECT_VERSION 1.0.0)

add_executable(qrencode src/main/qrencode.c)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})

include(FindLibQrencode)
if (LIBQRENCODE_FOUND)
    target_include_directories(qrencode PRIVATE ${LIBQRENCODE_INCLUDE_DIR})
    target_link_libraries(qrencode ${LIBQRENCODE_LIBRARY})
else()
    message(FATAL_ERROR "Couldn't find qrencode library.")
endif()

include(GNUInstallDirs)
install(TARGETS qrencode RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
