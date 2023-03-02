cmake_minimum_required(VERSION 3.0.0)

project(libgit2-examples C)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

########################################################################################

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

find_package(PkgConfig REQUIRED)
find_package(LibGit2   REQUIRED)

########################################################################################

add_executable(git-open          git-open.c)
add_executable(git-sync          git-sync.c)
add_executable(git-pull          git-pull.c)
add_executable(git-fetch         git-fetch.c)
add_executable(git-clone         git-clone.c)
add_executable(git-rev-parse     git-rev-parse.c)
add_executable(git-clone-simple  git-clone-simple.c)
add_executable(git-status-list   git-status-list.c)
add_executable(git-remote-list   git-remote-list.c)
add_executable(git-branch-list   git-branch-list.c)
add_executable(git-config-list   git-config-list.c)
add_executable(git-tag-name-list git-tag-name-list.c)

target_link_libraries(git-open          LIBGIT2::LIBGIT2)
target_link_libraries(git-sync          LIBGIT2::LIBGIT2)
target_link_libraries(git-pull          LIBGIT2::LIBGIT2)
target_link_libraries(git-fetch         LIBGIT2::LIBGIT2)
target_link_libraries(git-clone         LIBGIT2::LIBGIT2)
target_link_libraries(git-rev-parse     LIBGIT2::LIBGIT2)
target_link_libraries(git-clone-simple  LIBGIT2::LIBGIT2)
target_link_libraries(git-status-list   LIBGIT2::LIBGIT2)
target_link_libraries(git-remote-list   LIBGIT2::LIBGIT2)
target_link_libraries(git-branch-list   LIBGIT2::LIBGIT2)
target_link_libraries(git-config-list   LIBGIT2::LIBGIT2)
target_link_libraries(git-tag-name-list LIBGIT2::LIBGIT2)

########################################################################################

include(GNUInstallDirs)

install(TARGETS git-open git-pull git-sync git-fetch git-clone git-rev-parse git-clone-simple git-status-list git-remote-list git-branch-list git-config-list git-tag-name-list RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
