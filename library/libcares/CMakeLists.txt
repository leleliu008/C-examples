cmake_minimum_required(VERSION 3.15)

project(dns C)

set(PROJECT_VERSION       1.0.0)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

find_package(PkgConfig REQUIRED)

find_package(CARES REQUIRED)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

##########################################

add_executable(dns src/dns.c)
target_link_libraries(dns CARES::libcares)

##########################################

include(GNUInstallDirs)

install(TARGETS dns RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
