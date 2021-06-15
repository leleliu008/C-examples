# try to find chinese-calendar library, once done following variables will be defined
#
# CHINESE_CALENDAR_FOUND       - system has chinese-calendar library
# CHINESE_CALENDAR_VERSION     - the version of chinese-calendar library
# CHINESE_CALENDAR_INCLUDE_DIR - the chinese-calendar library include directory
# CHINESE_CALENDAR_LIBRARY     - the filepath of libchinese-calendar.a|so|dylib


if (CHINESE_CALENDAR_INCLUDE_DIR AND CHINESE_CALENDAR_LIBRARY)
    set(CHINESE_CALENDAR_FOUND TRUE)
else()
    if (ENABLE_STATIC)
        set(CHINESE_CALENDAR_LIBRARY_NAMES libchinese-calendar.a)
    else()
        set(CHINESE_CALENDAR_LIBRARY_NAMES chinese-calendar)
    endif()

    include(FindPkgConfig)
    if (PKG_CONFIG_FOUND)
        pkg_check_modules(PKG_CONFIG_CHINESE_CALENDAR QUIET chinese-calendar)

        #message("PKG_CONFIG_CHINESE_CALENDAR_FOUND=${PKG_CONFIG_CHINESE_CALENDAR_FOUND}")
        #message("PKG_CONFIG_CHINESE_CALENDAR_INCLUDE_DIRS=${PKG_CONFIG_CHINESE_CALENDAR_INCLUDE_DIRS}")
        #message("PKG_CONFIG_CHINESE_CALENDAR_LIBRARY_DIRS=${PKG_CONFIG_CHINESE_CALENDAR_LIBRARY_DIRS}")
        #message("PKG_CONFIG_CHINESE_CALENDAR_INCLUDEDIR=${PKG_CONFIG_CHINESE_CALENDAR_INCLUDEDIR}")
        #message("PKG_CONFIG_CHINESE_CALENDAR_LIBDIR=${PKG_CONFIG_CHINESE_CALENDAR_LIBDIR}")
        #message("PKG_CONFIG_CHINESE_CALENDAR_VERSION=${PKG_CONFIG_CHINESE_CALENDAR_VERSION}")

        if (PKG_CONFIG_CHINESE_CALENDAR_FOUND)
            find_path(   CHINESE_CALENDAR_INCLUDE_DIR   chinese-calendar.h                HINTS ${PKG_CONFIG_CHINESE_CALENDAR_INCLUDE_DIRS})
            find_library(CHINESE_CALENDAR_LIBRARY NAMES ${CHINESE_CALENDAR_LIBRARY_NAMES} HINTS ${PKG_CONFIG_CHINESE_CALENDAR_LIBRARY_DIRS})
            if (CHINESE_CALENDAR_INCLUDE_DIR AND CHINESE_CALENDAR_LIBRARY)
                if (PKG_CONFIG_CHINESE_CALENDAR_VERSION)
                    set(CHINESE_CALENDAR_VERSION ${PKG_CONFIG_CHINESE_CALENDAR_VERSION})
                endif()
            endif()
        else()
            find_path(   CHINESE_CALENDAR_INCLUDE_DIR   chinese-calendar.h)
            find_library(CHINESE_CALENDAR_LIBRARY NAMES ${CHINESE_CALENDAR_LIBRARY_NAMES})
        endif()
    else()
        find_path(   CHINESE_CALENDAR_INCLUDE_DIR   chinese-calendar.h)
        find_library(CHINESE_CALENDAR_LIBRARY NAMES ${CHINESE_CALENDAR_LIBRARY_NAMES})
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    chinese-calendar
    FOUND_VAR CHINESE_CALENDAR_FOUND
    REQUIRED_VARS CHINESE_CALENDAR_LIBRARY CHINESE_CALENDAR_INCLUDE_DIR
    VERSION_VAR CHINESE_CALENDAR_VERSION
)

mark_as_advanced(CHINESE_CALENDAR_INCLUDE_DIR CHINESE_CALENDAR_LIBRARY)
