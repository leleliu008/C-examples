# try to find base64 library, once done following variables will be defined
#
# BASE64_FOUND       - system has base64 library
# BASE64_VERSION     - the version of base64 library
# BASE64_INCLUDE_DIR - the base64 library include directory
# BASE64_LIBRARY     - the filepath of libbase64.a|so|dylib


if (BASE64_INCLUDE_DIR AND BASE64_LIBRARY)
    set(BASE64_FOUND TRUE)
else()
    if (ENABLE_STATIC)
        set(BASE64_LIBRARY_NAMES libbase64.a)
    else()
        set(BASE64_LIBRARY_NAMES base64)
    endif()

    include(FindPkgConfig)
    if (PKG_CONFIG_FOUND)
        pkg_check_modules(PKG_CONFIG_BASE64 QUIET base64)

        #message("PKG_CONFIG_BASE64_FOUND=${PKG_CONFIG_BASE64_FOUND}")
        #message("PKG_CONFIG_BASE64_INCLUDE_DIRS=${PKG_CONFIG_BASE64_INCLUDE_DIRS}")
        #message("PKG_CONFIG_BASE64_LIBRARY_DIRS=${PKG_CONFIG_BASE64_LIBRARY_DIRS}")
        #message("PKG_CONFIG_BASE64_INCLUDEDIR=${PKG_CONFIG_BASE64_INCLUDEDIR}")
        #message("PKG_CONFIG_BASE64_LIBDIR=${PKG_CONFIG_BASE64_LIBDIR}")
        #message("PKG_CONFIG_BASE64_VERSION=${PKG_CONFIG_BASE64_VERSION}")

        if (PKG_CONFIG_BASE64_FOUND)
            find_path(   BASE64_INCLUDE_DIR   base64.h                HINTS ${PKG_CONFIG_BASE64_INCLUDE_DIRS})
            find_library(BASE64_LIBRARY NAMES ${BASE64_LIBRARY_NAMES} HINTS ${PKG_CONFIG_BASE64_LIBRARY_DIRS})
            if (BASE64_INCLUDE_DIR AND BASE64_LIBRARY)
                if (PKG_CONFIG_BASE64_VERSION)
                    set(BASE64_VERSION ${PKG_CONFIG_BASE64_VERSION})
                endif()
            endif()
        else()
            find_path(   BASE64_INCLUDE_DIR   base64.h)
            find_library(BASE64_LIBRARY NAMES ${BASE64_LIBRARY_NAMES})
        endif()
    else()
        find_path(   BASE64_INCLUDE_DIR   base64.h)
        find_library(BASE64_LIBRARY NAMES ${BASE64_LIBRARY_NAMES})
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    BASE64
    FOUND_VAR BASE64_FOUND
    REQUIRED_VARS BASE64_LIBRARY BASE64_INCLUDE_DIR
    VERSION_VAR BASE64_VERSION
)

mark_as_advanced(BASE64_INCLUDE_DIR BASE64_LIBRARY)
