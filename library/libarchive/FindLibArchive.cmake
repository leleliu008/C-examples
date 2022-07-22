# try to find archive.h and libarchive.a|so|dylib, once done following variables will be defined
#
# LIBARCHIVE_FOUND       - archive.h and libarchive.a|so|dylib have been found
# LIBARCHIVE_VERSION     - the version of libarchive
# LIBARCHIVE_INCLUDE_DIR - the libarchive include directory
# LIBARCHIVE_LIBRARY     - the filepath of libarchive.a|so|dylib


if (LIBARCHIVE_INCLUDE_DIR AND LIBARCHIVE_LIBRARY)
    set(LIBARCHIVE_FOUND TRUE)
else()
    pkg_check_modules(PKG_CONFIG_LIBARCHIVE QUIET libarchive)

    #message("PKG_CONFIG_LIBARCHIVE_FOUND=${PKG_CONFIG_LIBARCHIVE_FOUND}")
    #message("PKG_CONFIG_LIBARCHIVE_INCLUDE_DIRS=${PKG_CONFIG_LIBARCHIVE_INCLUDE_DIRS}")
    #message("PKG_CONFIG_LIBARCHIVE_LIBRARY_DIRS=${PKG_CONFIG_LIBARCHIVE_LIBRARY_DIRS}")
    #message("PKG_CONFIG_LIBARCHIVE_INCLUDEDIR=${PKG_CONFIG_LIBARCHIVE_INCLUDEDIR}")
    #message("PKG_CONFIG_LIBARCHIVE_LIBDIR=${PKG_CONFIG_LIBARCHIVE_LIBDIR}")
    #message("PKG_CONFIG_LIBARCHIVE_VERSION=${PKG_CONFIG_LIBARCHIVE_VERSION}")

    if (ENABLE_STATIC)
        set(LIBARCHIVE_LIBRARY_NAMES libarchive.a)
    else()
        set(LIBARCHIVE_LIBRARY_NAMES archive)
    endif()

    if (PKG_CONFIG_LIBARCHIVE_FOUND)
        find_path   (LIBARCHIVE_INCLUDE_DIR archive.h                   HINTS ${PKG_CONFIG_LIBARCHIVE_INCLUDE_DIRS})
        find_library(LIBARCHIVE_LIBRARY     ${LIBARCHIVE_LIBRARY_NAMES} HINTS ${PKG_CONFIG_LIBARCHIVE_LIBRARY_DIRS})
    else()
        find_path   (LIBARCHIVE_INCLUDE_DIR archive.h)
        find_library(LIBARCHIVE_LIBRARY     ${LIBARCHIVE_LIBRARY_NAMES})
    endif()
    
    if (PKG_CONFIG_LIBARCHIVE_VERSION)
        set(LIBARCHIVE_VERSION ${PKG_CONFIG_LIBARCHIVE_VERSION})
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibArchive REQUIRED_VARS LIBARCHIVE_LIBRARY LIBARCHIVE_INCLUDE_DIR VERSION_VAR LIBARCHIVE_VERSION)

mark_as_advanced(LIBARCHIVE_INCLUDE_DIR LIBARCHIVE_LIBRARY)
