cmake_minimum_required(VERSION 3.0.0)

project(cJSONTest C)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(cJSON-example cJSON.c cJSON-example.c)
target_include_directories(cJSON-example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GNUInstallDirs)
install(TARGETS cJSON-example RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
