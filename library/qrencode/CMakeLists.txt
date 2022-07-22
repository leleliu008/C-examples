cmake_minimum_required(VERSION 3.0.0)

project(qrencode C)

set(PROJECT_VERSION 1.0.0)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
find_package(LibQrencode REQUIRED)

add_executable(qrencode qrencode.c)
target_include_directories(qrencode PRIVATE ${LIBQRENCODE_INCLUDE_DIR})
target_link_libraries(qrencode ${LIBQRENCODE_LIBRARY})

include(GNUInstallDirs)
install(TARGETS qrencode RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
