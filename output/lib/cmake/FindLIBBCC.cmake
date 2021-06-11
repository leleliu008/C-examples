# try to find libbcc, once done following variables will be defined
#
# LIBBCC_FOUND       - system has libbcc
# LIBBCC_VERSION     - the version of libbcc
# LIBBCC_INCLUDE_DIR - the libbcc include directory
# LIBBCC_LIBRARY     - the filepath of libbcc.a|so|dylib


if (LIBBCC_INCLUDE_DIR AND LIBBCC_LIBRARY)
    set(LIBBCC_FOUND TRUE)
else()
    pkg_check_modules(PKG_CONFIG_LIBBCC QUIET libbcc)

    #message("PKG_CONFIG_LIBBCC_FOUND=${PKG_CONFIG_LIBBCC_FOUND}")
    #message("PKG_CONFIG_LIBBCC_INCLUDE_DIRS=${PKG_CONFIG_LIBBCC_INCLUDE_DIRS}")
    #message("PKG_CONFIG_LIBBCC_LIBRARY_DIRS=${PKG_CONFIG_LIBBCC_LIBRARY_DIRS}")
    #message("PKG_CONFIG_LIBBCC_INCLUDEDIR=${PKG_CONFIG_LIBBCC_INCLUDEDIR}")
    #message("PKG_CONFIG_LIBBCC_LIBDIR=${PKG_CONFIG_LIBBCC_LIBDIR}")
    #message("PKG_CONFIG_LIBBCC_VERSION=${PKG_CONFIG_LIBBCC_VERSION}")
     
    if (ENABLE_STATIC)
        set(LIBBCC_LIBRARY_NAMES libbcc.a)
    else()
        set(LIBBCC_LIBRARY_NAMES bcc)
    endif()

    if (PKG_CONFIG_LIBBCC_FOUND)
        find_path(   LIBBCC_INCLUDE_DIR   bcc.h                   HINTS ${PKG_CONFIG_LIBBCC_INCLUDE_DIRS})
        find_library(LIBBCC_LIBRARY NAMES ${LIBBCC_LIBRARY_NAMES} HINTS ${PKG_CONFIG_LIBBCC_LIBRARY_DIRS})
    else()
        find_path(   LIBBCC_INCLUDE_DIR   bcc.h)
        find_library(LIBBCC_LIBRARY NAMES ${LIBBCC_LIBRARY_NAMES})
    endif()

    if (LIBBCC_INCLUDE_DIR AND LIBBCC_LIBRARY)
        if (PKG_CONFIG_LIBBCC_VERSION)
            set(LIBBCC_VERSION ${PKG_CONFIG_LIBBCC_VERSION})
        endif()
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    LIBBCC
    FOUND_VAR LIBBCC_FOUND
    REQUIRED_VARS LIBBCC_LIBRARY LIBBCC_INCLUDE_DIR
    VERSION_VAR LIBBCC_VERSION
)

mark_as_advanced(LIBBCC_INCLUDE_DIR LIBBCC_LIBRARY)
