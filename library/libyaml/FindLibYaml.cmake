# try to find yaml.h and libyaml.a|so|dylib, once done following variables will be defined
#
# LIBYAML_FOUND       - libyaml.a|so|dylib have been found
# LIBYAML_VERSION     - the version of libyaml
# LIBYAML_INCLUDE_DIR - the libyaml include directory
# LIBYAML_LIBRARY     - the filepath of libyaml.a|so|dylib


if (LIBYAML_INCLUDE_DIR AND LIBYAML_LIBRARY)
    set(LIBYAML_FOUND TRUE)
else()
    pkg_check_modules(PKG_CONFIG_LIBYAML QUIET yaml-0.1)

    #message("PKG_CONFIG_LIBYAML_FOUND=${PKG_CONFIG_LIBYAML_FOUND}")
    #message("PKG_CONFIG_LIBYAML_INCLUDE_DIRS=${PKG_CONFIG_LIBYAML_INCLUDE_DIRS}")
    #message("PKG_CONFIG_LIBYAML_LIBRARY_DIRS=${PKG_CONFIG_LIBYAML_LIBRARY_DIRS}")
    #message("PKG_CONFIG_LIBYAML_INCLUDEDIR=${PKG_CONFIG_LIBYAML_INCLUDEDIR}")
    #message("PKG_CONFIG_LIBYAML_LIBDIR=${PKG_CONFIG_LIBYAML_LIBDIR}")
    #message("PKG_CONFIG_LIBYAML_VERSION=${PKG_CONFIG_LIBYAML_VERSION}")

    if(ENABLE_STATIC)
        set(LIBYAML_LIBRARY_NAMES libyaml.a)
    else()
        set(LIBYAML_LIBRARY_NAMES yaml)
    endif()

    if (PKG_CONFIG_LIBYAML_FOUND)
        find_path   (LIBYAML_INCLUDE_DIR yaml.h                   HINTS ${PKG_CONFIG_LIBYAML_INCLUDE_DIRS})
        find_library(LIBYAML_LIBRARY     ${LIBYAML_LIBRARY_NAMES} HINTS ${PKG_CONFIG_LIBYAML_LIBRARY_DIRS})
    else()
        find_path   (LIBYAML_INCLUDE_DIR yaml.h)
        find_library(LIBYAML_LIBRARY     ${LIBYAML_LIBRARY_NAMES})
    endif()
    
    if (PKG_CONFIG_LIBYAML_VERSION)
        set(LIBYAML_VERSION ${PKG_CONFIG_LIBYAML_VERSION})
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibYaml REQUIRED_VARS LIBYAML_LIBRARY LIBYAML_INCLUDE_DIR VERSION_VAR LIBYAML_VERSION)

mark_as_advanced(LIBYAML_INCLUDE_DIR LIBYAML_LIBRARY)
