# try to find Qrencode library, once done following variables will be defined
#
# LIBQRENCODE_FOUND       - system has Qrencode library
# LIBQRENCODE_VERSION     - the version of Qrencode library
# LIBQRENCODE_INCLUDE_DIR - the Qrencode library include directory
# LIBQRENCODE_LIBRARY     - the filepath of libqrencode.a|so|dylib


if (LIBQRENCODE_INCLUDE_DIR AND LIBQRENCODE_LIBRARY)
    set(LIBQRENCODE_FOUND TRUE)
else()
    if (ENABLE_STATIC)
        set(LIBQRENCODE_LIBRARY_NAMES libqrencode.a)
    else()
        set(LIBQRENCODE_LIBRARY_NAMES qrencode)
    endif()
    
    include(FindPkgConfig)
    if (PKG_CONFIG_FOUND)
        pkg_check_modules(PKG_CONFIG_LIBQRENCODE QUIET libqrencode)
        
        #message("PKG_CONFIG_LIBQRENCODE_FOUND=${PKG_CONFIG_LIBQRENCODE_FOUND}")
        #message("PKG_CONFIG_LIBQRENCODE_INCLUDE_DIRS=${PKG_CONFIG_LIBQRENCODE_INCLUDE_DIRS}")
        #message("PKG_CONFIG_LIBQRENCODE_LIBRARY_DIRS=${PKG_CONFIG_LIBQRENCODE_LIBRARY_DIRS}")
        #message("PKG_CONFIG_LIBQRENCODE_INCLUDEDIR=${PKG_CONFIG_LIBQRENCODE_INCLUDEDIR}")
        #message("PKG_CONFIG_LIBQRENCODE_LIBDIR=${PKG_CONFIG_LIBQRENCODE_LIBDIR}")
        #message("PKG_CONFIG_LIBQRENCODE_VERSION=${PKG_CONFIG_LIBQRENCODE_VERSION}")

        if (PKG_CONFIG_LIBQRENCODE_FOUND)
            find_path(   LIBQRENCODE_INCLUDE_DIR   qrencode.h                   HINTS ${PKG_CONFIG_LIBQRENCODE_INCLUDE_DIRS})
            find_library(LIBQRENCODE_LIBRARY NAMES ${LIBQRENCODE_LIBRARY_NAMES} HINTS ${PKG_CONFIG_LIBQRENCODE_LIBRARY_DIRS})
            if (LIBQRENCODE_INCLUDE_DIR AND LIBQRENCODE_LIBRARY)
                if (PKG_CONFIG_LIBQRENCODE_VERSION)
                    set(LIBQRENCODE_VERSION ${PKG_CONFIG_LIBQRENCODE_VERSION})
                endif()
            endif()
        else()
            find_path(   LIBQRENCODE_INCLUDE_DIR   qrencode.h)
            find_library(LIBQRENCODE_LIBRARY NAMES ${LIBQRENCODE_LIBRARY_NAMES})
        endif()
    else()
        find_path(   LIBQRENCODE_INCLUDE_DIR   qrencode.h)
        find_library(LIBQRENCODE_LIBRARY NAMES ${LIBQRENCODE_LIBRARY_NAMES})
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    LibQrencode
    FOUND_VAR LIBQRENCODE_FOUND
    REQUIRED_VARS LIBQRENCODE_LIBRARY LIBQRENCODE_INCLUDE_DIR
    VERSION_VAR LIBQRENCODE_VERSION
)

mark_as_advanced(LIBQRENCODE_INCLUDE_DIR LIBQRENCODE_LIBRARY)
