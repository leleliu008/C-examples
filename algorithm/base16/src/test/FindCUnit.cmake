# try to find CUnit library, once done following variables will be defined
#
# CUNIT_FOUND       - system has CUnit library
# CUNIT_VERSION     - the version of CUnit library
# CUNIT_INCLUDE_DIR - the CUnit library include directory
# CUNIT_LIBRARY     - the filepath of libcunit.a|so|dylib


if (CUNIT_INCLUDE_DIR AND CUNIT_LIBRARY)
    set(CUNIT_FOUND TRUE)
else()
    if (ENABLE_STATIC)
        set(CUNIT_LIBRARY_NAMES libcunit.a)
    else()
        set(CUNIT_LIBRARY_NAMES cunit)
    endif()
    
    include(FindPkgConfig)
    if (PKG_CONFIG_FOUND)
        pkg_check_modules(PKG_CONFIG_CUNIT QUIET cunit)
        
        #message("PKG_CONFIG_CUNIT_FOUND=${PKG_CONFIG_CUNIT_FOUND}")
        #message("PKG_CONFIG_CUNIT_INCLUDE_DIRS=${PKG_CONFIG_CUNIT_INCLUDE_DIRS}")
        #message("PKG_CONFIG_CUNIT_LIBRARY_DIRS=${PKG_CONFIG_CUNIT_LIBRARY_DIRS}")
        #message("PKG_CONFIG_CUNIT_INCLUDEDIR=${PKG_CONFIG_CUNIT_INCLUDEDIR}")
        #message("PKG_CONFIG_CUNIT_LIBDIR=${PKG_CONFIG_CUNIT_LIBDIR}")
        #message("PKG_CONFIG_CUNIT_VERSION=${PKG_CONFIG_CUNIT_VERSION}")

        if (PKG_CONFIG_CUNIT_FOUND)
            find_path(   CUNIT_INCLUDE_DIR   CUnit/CUnit.h          HINTS ${PKG_CONFIG_CUNIT_INCLUDE_DIRS})
            find_library(CUNIT_LIBRARY NAMES ${CUNIT_LIBRARY_NAMES} HINTS ${PKG_CONFIG_CUNIT_LIBRARY_DIRS})
            if (CUNIT_INCLUDE_DIR AND CUNIT_LIBRARY)
                if (PKG_CONFIG_CUNIT_VERSION)
                    set(CUNIT_VERSION ${PKG_CONFIG_CUNIT_VERSION})
                endif()
            endif()
        else()
            find_path(   CUNIT_INCLUDE_DIR   CUnit/CUnit.h)
            find_library(CUNIT_LIBRARY NAMES ${CUNIT_LIBRARY_NAMES})
        endif()
    else()
        find_path(   CUNIT_INCLUDE_DIR   CUnit/CUnit.h)
        find_library(CUNIT_LIBRARY NAMES ${CUNIT_LIBRARY_NAMES})
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    CUnit
    FOUND_VAR CUNIT_FOUND
    REQUIRED_VARS CUNIT_LIBRARY CUNIT_INCLUDE_DIR
    VERSION_VAR CUNIT_VERSION
)

mark_as_advanced(CUNIT_INCLUDE_DIR CUNIT_LIBRARY)
