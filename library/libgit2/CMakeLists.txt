cmake_minimum_required(VERSION 3.0.0)

project(libgit2-examples C)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

########################################################################################

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

find_package(PkgConfig REQUIRED)
find_package(LibGit2   REQUIRED)

########################################################################################

add_executable(git-open         git-open.c)
add_executable(git-clone        git-clone.c)
add_executable(git-clone-simple git-clone-simple.c)

target_link_libraries(     git-open         PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-open         PRIVATE "${LIBGIT2_INCLUDE_DIR}")

target_link_libraries(     git-clone        PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-clone        PRIVATE "${LIBGIT2_INCLUDE_DIR}")

target_link_libraries(     git-clone-simple PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-clone-simple PRIVATE "${LIBGIT2_INCLUDE_DIR}")

########################################################################################

include(GNUInstallDirs)

install(TARGETS git-open git-clone git-clone-simple RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
