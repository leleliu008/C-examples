cmake_minimum_required(VERSION 3.0.0)

project(yaml-based-formula-parser C)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

########################################################################################

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

find_package(PkgConfig REQUIRED)
find_package(LibYaml   REQUIRED)

########################################################################################

add_executable(yaml-based-formula-parser yaml-based-formula-parser.c)

target_link_libraries(yaml-based-formula-parser "${LIBYAML_LIBRARY}")
target_include_directories(yaml-based-formula-parser PRIVATE "${LIBYAML_INCLUDE_DIR}")

########################################################################################

include(GNUInstallDirs)

install(TARGETS yaml-based-formula-parser RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
