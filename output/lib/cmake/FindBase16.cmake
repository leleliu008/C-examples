# try to find base16 library, once done following variables will be defined
#
# BASE16_FOUND       - system has base16 library
# BASE16_VERSION     - the version of base16 library
# BASE16_INCLUDE_DIR - the base16 library include directory
# BASE16_LIBRARY     - the filepath of libbase16.a|so|dylib


if (BASE16_INCLUDE_DIR AND BASE16_LIBRARY)
    set(BASE16_FOUND TRUE)
else()
    if (ENABLE_STATIC)
        set(BASE16_LIBRARY_NAMES libbase16.a)
    else()
        set(BASE16_LIBRARY_NAMES base16)
    endif()

    include(FindPkgConfig)
    if (PKG_CONFIG_FOUND)
        pkg_check_modules(PKG_CONFIG_BASE16 QUIET base16)

        #message("PKG_CONFIG_BASE16_FOUND=${PKG_CONFIG_BASE16_FOUND}")
        #message("PKG_CONFIG_BASE16_INCLUDE_DIRS=${PKG_CONFIG_BASE16_INCLUDE_DIRS}")
        #message("PKG_CONFIG_BASE16_LIBRARY_DIRS=${PKG_CONFIG_BASE16_LIBRARY_DIRS}")
        #message("PKG_CONFIG_BASE16_INCLUDEDIR=${PKG_CONFIG_BASE16_INCLUDEDIR}")
        #message("PKG_CONFIG_BASE16_LIBDIR=${PKG_CONFIG_BASE16_LIBDIR}")
        #message("PKG_CONFIG_BASE16_VERSION=${PKG_CONFIG_BASE16_VERSION}")

        if (PKG_CONFIG_BASE16_FOUND)
            find_path(   BASE16_INCLUDE_DIR   base16.h                HINTS ${PKG_CONFIG_BASE16_INCLUDE_DIRS})
            find_library(BASE16_LIBRARY NAMES ${BASE16_LIBRARY_NAMES} HINTS ${PKG_CONFIG_BASE16_LIBRARY_DIRS})
            if (BASE16_INCLUDE_DIR AND BASE16_LIBRARY)
                if (PKG_CONFIG_BASE16_VERSION)
                    set(BASE16_VERSION ${PKG_CONFIG_BASE16_VERSION})
                endif()
            endif()
        else()
            find_path(   BASE16_INCLUDE_DIR   base16.h)
            find_library(BASE16_LIBRARY NAMES ${BASE16_LIBRARY_NAMES})
        endif()
    else()
        find_path(   BASE16_INCLUDE_DIR   base16.h)
        find_library(BASE16_LIBRARY NAMES ${BASE16_LIBRARY_NAMES})
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    BASE16
    FOUND_VAR BASE16_FOUND
    REQUIRED_VARS BASE16_LIBRARY BASE16_INCLUDE_DIR
    VERSION_VAR BASE16_VERSION
)

mark_as_advanced(BASE16_INCLUDE_DIR BASE16_LIBRARY)
