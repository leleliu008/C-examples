# try to find git2.h and libgit2.a|so|dylib, once done following variables will be defined
#
# LIBGIT2_FOUND       - libgit2.a|so|dylib have been found
# LIBGIT2_VERSION     - the version of libgit2
# LIBGIT2_INCLUDE_DIR - the libgit2 include directory
# LIBGIT2_LIBRARY_DIR - the libgit2 lib     directory
# LIBGIT2_LIBRARY     - the filepath of libgit2.a|so|dylib


if (LIBGIT2_INCLUDE_DIR AND LIBGIT2_LIBRARY)
    set(LIBGIT2_FOUND TRUE)
else()
    pkg_check_modules(PKG_CONFIG_LIBGIT2 QUIET libgit2)

    #message("PKG_CONFIG_LIBGIT2_FOUND=${PKG_CONFIG_LIBGIT2_FOUND}")
    #message("PKG_CONFIG_LIBGIT2_INCLUDE_DIRS=${PKG_CONFIG_LIBGIT2_INCLUDE_DIRS}")
    #message("PKG_CONFIG_LIBGIT2_LIBRARY_DIRS=${PKG_CONFIG_LIBGIT2_LIBRARY_DIRS}")
    #message("PKG_CONFIG_LIBGIT2_INCLUDEDIR=${PKG_CONFIG_LIBGIT2_INCLUDEDIR}")
    #message("PKG_CONFIG_LIBGIT2_LIBDIR=${PKG_CONFIG_LIBGIT2_LIBDIR}")
    #message("PKG_CONFIG_LIBGIT2_VERSION=${PKG_CONFIG_LIBGIT2_VERSION}")

    if(ENABLE_STATIC)
        set(LIBGIT2_LIBRARY_NAMES libgit2.a)
    else()
        set(LIBGIT2_LIBRARY_NAMES git2)
    endif()

    if (PKG_CONFIG_LIBGIT2_FOUND)
        find_path   (LIBGIT2_INCLUDE_DIR git2.h                   HINTS ${PKG_CONFIG_LIBGIT2_INCLUDE_DIRS})
        find_library(LIBGIT2_LIBRARY     ${LIBGIT2_LIBRARY_NAMES} HINTS ${PKG_CONFIG_LIBGIT2_LIBRARY_DIRS})
    else()
        find_path   (LIBGIT2_INCLUDE_DIR git2.h)
        find_library(LIBGIT2_LIBRARY     ${LIBGIT2_LIBRARY_NAMES})
    endif()
    
    if (PKG_CONFIG_LIBGIT2_VERSION)
        set(LIBGIT2_VERSION ${PKG_CONFIG_LIBGIT2_VERSION})
    endif()
endif()

get_filename_component(LIBGIT2_LIBRARY_DIR ${LIBGIT2_LIBRARY} DIRECTORY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibGit2 REQUIRED_VARS LIBGIT2_LIBRARY LIBGIT2_INCLUDE_DIR VERSION_VAR LIBGIT2_VERSION)

mark_as_advanced(LIBGIT2_INCLUDE_DIR LIBGIT2_LIBRARY)
