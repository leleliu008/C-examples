cmake_minimum_required(VERSION 3.15)

project(self_exe_path C)

set(PROJECT_VERSION       1.0.0)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

########################################################################################

add_executable(self_exe_path main.c self.c)
add_executable(getexepath getexepath.c)

########################################################################################

include(GNUInstallDirs)

install(TARGETS self_exe_path getexepath RUNTIME COMPONENT bin DESTINATION ${CMAKE_INSTALL_BINDIR})
