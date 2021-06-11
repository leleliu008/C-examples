# try to find url library, once done following variables will be defined
#
# URL_FOUND       - system has url library
# URL_VERSION     - the version of url library
# URL_INCLUDE_DIR - the url library include directory
# URL_LIBRARY     - the filepath of liburl.a|so|dylib


if (URL_INCLUDE_DIR AND URL_LIBRARY)
    set(URL_FOUND TRUE)
else()
    if (ENABLE_STATIC)
        set(URL_LIBRARY_NAMES liburl.a)
    else()
        set(URL_LIBRARY_NAMES url)
    endif()

    include(FindPkgConfig)
    if (PKG_CONFIG_FOUND)
        pkg_check_modules(PKG_CONFIG_URL QUIET url)

        #message("PKG_CONFIG_URL_FOUND=${PKG_CONFIG_URL_FOUND}")
        #message("PKG_CONFIG_URL_INCLUDE_DIRS=${PKG_CONFIG_URL_INCLUDE_DIRS}")
        #message("PKG_CONFIG_URL_LIBRARY_DIRS=${PKG_CONFIG_URL_LIBRARY_DIRS}")
        #message("PKG_CONFIG_URL_INCLUDEDIR=${PKG_CONFIG_URL_INCLUDEDIR}")
        #message("PKG_CONFIG_URL_LIBDIR=${PKG_CONFIG_URL_LIBDIR}")
        #message("PKG_CONFIG_URL_VERSION=${PKG_CONFIG_URL_VERSION}")

        if (PKG_CONFIG_URL_FOUND)
            find_path(   URL_INCLUDE_DIR   url.h                HINTS ${PKG_CONFIG_URL_INCLUDE_DIRS})
            find_library(URL_LIBRARY NAMES ${URL_LIBRARY_NAMES} HINTS ${PKG_CONFIG_URL_LIBRARY_DIRS})
            if (URL_INCLUDE_DIR AND URL_LIBRARY)
                if (PKG_CONFIG_URL_VERSION)
                    set(URL_VERSION ${PKG_CONFIG_URL_VERSION})
                endif()
            endif()
        else()
            find_path(   URL_INCLUDE_DIR   url.h)
            find_library(URL_LIBRARY NAMES ${URL_LIBRARY_NAMES})
        endif()
    else()
        find_path(   URL_INCLUDE_DIR   url.h)
        find_library(URL_LIBRARY NAMES ${URL_LIBRARY_NAMES})
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    URL
    FOUND_VAR URL_FOUND
    REQUIRED_VARS URL_LIBRARY URL_INCLUDE_DIR
    VERSION_VAR URL_VERSION
)

mark_as_advanced(URL_INCLUDE_DIR URL_LIBRARY)
