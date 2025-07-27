cmake_minimum_required(VERSION 3.15)

project(yaml-based-formula-parser C)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

########################################################################################

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

find_package(PkgConfig REQUIRED)
find_package(LibYAML   REQUIRED)

########################################################################################

add_executable(yaml-based-formula-parser yaml-based-formula-parser.c)

target_link_libraries(yaml-based-formula-parser LIBYAML::LIBYAML)

########################################################################################

include(GNUInstallDirs)

install(TARGETS yaml-based-formula-parser RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
