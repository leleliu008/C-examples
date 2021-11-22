cmake_minimum_required(VERSION 3.0.0)

project(C C)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(algorithm/base16)
add_subdirectory(algorithm/bcc)
add_subdirectory(algorithm/url)
add_subdirectory(algorithm/chinese-calendar)

#add_subdirectory(library/qrencode)
