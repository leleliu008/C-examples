# https://cmake.org/cmake/help/latest/module/FindLibArchive.html
#
# try to find archive.h and libarchive.a|so|dylib, once done following variables will be defined
#
# LibArchive_FOUND         - libarchive.a|so|dylib have been found
# LibArchive_VERSION       - the version of libarchive
# LibArchive_INCLUDE_DIRS  - the libarchive and dependencies include directory
# LibArchive_LIBRARIES     - the filepath of libarchive.a|so|dylib and it's dependencies


if (LibArchive_INCLUDE_DIRS AND LibArchive_LIBRARIES)
    set(LibArchive_FOUND TRUE)
else()
    pkg_check_modules(PKG_CONFIG_LIBARCHIVE libarchive)

    message("PKG_CONFIG_LIBARCHIVE_FOUND=${PKG_CONFIG_LIBARCHIVE_FOUND}")
    message("PKG_CONFIG_LIBARCHIVE_INCLUDE_DIRS=${PKG_CONFIG_LIBARCHIVE_INCLUDE_DIRS}")
    message("PKG_CONFIG_LIBARCHIVE_LIBRARY_DIRS=${PKG_CONFIG_LIBARCHIVE_LIBRARY_DIRS}")
    message("PKG_CONFIG_LIBARCHIVE_INCLUDEDIR=${PKG_CONFIG_LIBARCHIVE_INCLUDEDIR}")
    message("PKG_CONFIG_LIBARCHIVE_LIBDIR=${PKG_CONFIG_LIBARCHIVE_LIBDIR}")
    message("PKG_CONFIG_LIBARCHIVE_VERSION=${PKG_CONFIG_LIBARCHIVE_VERSION}")
    message("PKG_CONFIG_LIBARCHIVE_LIBRARIES=${PKG_CONFIG_LIBARCHIVE_LIBRARIES}")
    message("PKG_CONFIG_LIBARCHIVE_LINK_LIBRARIES=${PKG_CONFIG_LIBARCHIVE_LINK_LIBRARIES}")
    message("PKG_CONFIG_LIBARCHIVE_STATIC_LIBRARIES=${PKG_CONFIG_LIBARCHIVE_STATIC_LIBRARIES}")
    message("PKG_CONFIG_LIBARCHIVE_STATIC_LINK_LIBRARIES=${PKG_CONFIG_LIBARCHIVE_STATIC_LINK_LIBRARIES}")

    if (PKG_CONFIG_LIBARCHIVE_FOUND)
        if (PKG_CONFIG_LIBARCHIVE_INCLUDE_DIRS)
        	set(LibArchive_INCLUDE_DIRS "${PKG_CONFIG_LIBARCHIVE_INCLUDE_DIRS}")
	    elseif (PKG_CONFIG_LIBARCHIVE_INCLUDEDIR)
        	set(LibArchive_INCLUDE_DIRS "${PKG_CONFIG_LIBARCHIVE_INCLUDEDIR}")
	    else()
		    find_path(LibArchive_INCLUDE_DIRS archive.h)
	    endif()

        # https://sourceware.org/bugzilla/show_bug.cgi?id=21264

        set(LibArchive_LIBRARIES )

        foreach(item ${PKG_CONFIG_LIBARCHIVE_LINK_LIBRARIES})
                if(item MATCHES ".*libm\\.(a|so|dylib)")
                list(APPEND LibArchive_LIBRARIES "-lm")
            elseif(item MATCHES ".*libdl\\.(a|so|dylib)")
                list(APPEND LibArchive_LIBRARIES "-ldl")
            elseif(item MATCHES ".*librt\\.(a|so|dylib)")
                list(APPEND LibArchive_LIBRARIES "-lrt")
            elseif(item MATCHES ".*libpthread\\.(a|so|dylib)")
                list(APPEND LibArchive_LIBRARIES "-lpthread")
            elseif(item MATCHES "/.*\\.framework")
                get_filename_component(LIBRARY_FILENAME_PREFIX ${item} NAME_WLE)
                message(STATUS "${LIBRARY_FILENAME_PREFIX}")
                list(APPEND LibArchive_LIBRARIES "-framework ${LIBRARY_FILENAME_PREFIX}")
            elseif(item MATCHES "-framework .*")
                list(APPEND LibArchive_LIBRARIES "${item}")
            elseif(item MATCHES "/.*")
                get_filename_component(LIBRARY_FILENAME ${item} NAME)

                message(STATUS "${LIBRARY_FILENAME}")

                if (NOT TARGET  LibArchive::${LIBRARY_FILENAME})
                    add_library(LibArchive::${LIBRARY_FILENAME} UNKNOWN IMPORTED)
                    set_target_properties(LibArchive::${LIBRARY_FILENAME} PROPERTIES IMPORTED_LOCATION "${item}")
                endif()

                list(APPEND LibArchive_LIBRARIES LibArchive::${LIBRARY_FILENAME})
            endif()
        endforeach()

        if (NOT TARGET  LibArchive::LibArchive)
            add_library(LibArchive::LibArchive INTERFACE IMPORTED)
            set_target_properties(LibArchive::LibArchive PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${LibArchive_INCLUDE_DIRS}"
                INTERFACE_LINK_LIBRARIES      "${LibArchive_LIBRARIES}"
            )
        endif()
    
        if (PKG_CONFIG_LIBARCHIVE_VERSION)
            set(LibArchive_VERSION ${PKG_CONFIG_LIBARCHIVE_VERSION})
        endif()
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibArchive REQUIRED_VARS LibArchive_LIBRARIES LibArchive_INCLUDE_DIRS VERSION_VAR LibArchive_VERSION)

mark_as_advanced(LibArchive_INCLUDE_DIRS LibArchive_LIBRARIES)
