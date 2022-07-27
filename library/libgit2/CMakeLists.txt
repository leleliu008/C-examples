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
add_executable(git-pull         git-pull.c)
add_executable(git-fetch        git-fetch.c)
add_executable(git-clone        git-clone.c)
add_executable(git-clone-simple git-clone-simple.c)
add_executable(git-status-list  git-status-list.c)
add_executable(git-remote-list  git-remote-list.c)
add_executable(git-branch-list  git-branch-list.c)
add_executable(git-config-list  git-config-list.c)
add_executable(git-tag-name-list  git-tag-name-list.c)

target_link_libraries(     git-open         PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-open         PRIVATE "${LIBGIT2_INCLUDE_DIR}")

target_link_libraries(     git-pull         PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-pull         PRIVATE "${LIBGIT2_INCLUDE_DIR}")

target_link_libraries(     git-fetch        PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-fetch        PRIVATE "${LIBGIT2_INCLUDE_DIR}")

target_link_libraries(     git-clone        PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-clone        PRIVATE "${LIBGIT2_INCLUDE_DIR}")

target_link_libraries(     git-clone-simple PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-clone-simple PRIVATE "${LIBGIT2_INCLUDE_DIR}")

target_link_libraries(     git-status-list  PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-status-list  PRIVATE "${LIBGIT2_INCLUDE_DIR}")

target_link_libraries(     git-remote-list  PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-remote-list  PRIVATE "${LIBGIT2_INCLUDE_DIR}")

target_link_libraries(     git-branch-list  PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-branch-list  PRIVATE "${LIBGIT2_INCLUDE_DIR}")

target_link_libraries(     git-config-list  PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-config-list  PRIVATE "${LIBGIT2_INCLUDE_DIR}")

target_link_libraries(     git-tag-name-list  PRIVATE "${LIBGIT2_LIBRARY}")
target_include_directories(git-tag-name-list  PRIVATE "${LIBGIT2_INCLUDE_DIR}")

########################################################################################

include(GNUInstallDirs)

install(TARGETS git-open git-pull git-fetch git-clone git-clone-simple git-status-list git-remote-list git-branch-list git-config-list git-tag-name-list RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
