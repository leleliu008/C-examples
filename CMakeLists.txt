cmake_minimum_required(VERSION 3.1)

project(C-examples C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(algorithm/base16)
add_subdirectory(algorithm/bcc)
add_subdirectory(algorithm/url)
add_subdirectory(algorithm/chinese-calendar)

add_subdirectory(library/openssl/SHA-256)
#add_subdirectory(library/qrencode)
