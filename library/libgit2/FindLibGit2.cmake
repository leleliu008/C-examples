# try to find git2.h and libgit2.a|so|dylib, once done following variables will be defined
#
# LIBGIT2_FOUND         - libgit2.a|so|dylib have been found
# LIBGIT2_VERSION       - the version of libgit2
# LIBGIT2_INCLUDE_DIRS  - the libgit2 and dependencies include directory
# LIBGIT2_LIBRARIES     - the filepath of libgit2.a|so|dylib and it's dependencies


if (LIBGIT2_INCLUDE_DIRS AND LIBGIT2_LIBRARIES)
    set(LIBGIT2_FOUND TRUE)
else()
    pkg_check_modules(PKG_CONFIG_LIBGIT2 QUIET libgit2)

    message("PKG_CONFIG_LIBGIT2_FOUND=${PKG_CONFIG_LIBGIT2_FOUND}")
    message("PKG_CONFIG_LIBGIT2_INCLUDE_DIRS=${PKG_CONFIG_LIBGIT2_INCLUDE_DIRS}")
    message("PKG_CONFIG_LIBGIT2_LIBRARY_DIRS=${PKG_CONFIG_LIBGIT2_LIBRARY_DIRS}")
    message("PKG_CONFIG_LIBGIT2_INCLUDEDIR=${PKG_CONFIG_LIBGIT2_INCLUDEDIR}")
    message("PKG_CONFIG_LIBGIT2_LIBDIR=${PKG_CONFIG_LIBGIT2_LIBDIR}")
    message("PKG_CONFIG_LIBGIT2_VERSION=${PKG_CONFIG_LIBGIT2_VERSION}")
    message("PKG_CONFIG_LIBGIT2_LIBRARIES=${PKG_CONFIG_LIBGIT2_LIBRARIES}")
    message("PKG_CONFIG_LIBGIT2_LINK_LIBRARIES=${PKG_CONFIG_LIBGIT2_LINK_LIBRARIES}")

    if (PKG_CONFIG_LIBGIT2_FOUND)
        if (PKG_CONFIG_LIBGIT2_INCLUDE_DIRS)
        	set(LIBGIT2_INCLUDE_DIRS "${PKG_CONFIG_LIBGIT2_INCLUDE_DIRS}")
	    elseif (PKG_CONFIG_LIBGIT2_INCLUDEDIR)
        	set(LIBGIT2_INCLUDE_DIRS "${PKG_CONFIG_LIBGIT2_INCLUDEDIR}")
	    else()
		    find_path(LIBGIT2_INCLUDE_DIRS git2.h)
	    endif()

        # https://sourceware.org/bugzilla/show_bug.cgi?id=21264

        set(LIBGIT2_LIBRARIES )

        foreach(item ${PKG_CONFIG_LIBGIT2_LINK_LIBRARIES})
                if(item MATCHES ".*libm\\.(a|so|dylib)")
                list(APPEND LIBGIT2_LIBRARIES "-lm")
            elseif(item MATCHES ".*libdl\\.(a|so|dylib)")
                list(APPEND LIBGIT2_LIBRARIES "-ldl")
            elseif(item MATCHES ".*librt\\.(a|so|dylib)")
                list(APPEND LIBGIT2_LIBRARIES "-lrt")
            elseif(item MATCHES ".*libpthread\\.(a|so|dylib)")
                list(APPEND LIBGIT2_LIBRARIES "-lpthread")
            elseif(item MATCHES "/.*\\.framework")
                get_filename_component(LIBRARY_FILENAME_PREFIX ${item} NAME_WLE)
                message(STATUS "${LIBRARY_FILENAME_PREFIX}")
                list(APPEND LIBGIT2_LIBRARIES "-framework ${LIBRARY_FILENAME_PREFIX}")
            elseif(item MATCHES "-framework .*")
                list(APPEND LIBGIT2_LIBRARIES "${item}")
            elseif(item MATCHES "/.*")
                get_filename_component(LIBRARY_FILENAME ${item} NAME)

                message(STATUS "${LIBRARY_FILENAME}")

                if (NOT TARGET  LIBGIT2::${LIBRARY_FILENAME})
                    add_library(LIBGIT2::${LIBRARY_FILENAME} UNKNOWN IMPORTED)
                    set_target_properties(LIBGIT2::${LIBRARY_FILENAME} PROPERTIES IMPORTED_LOCATION "${item}")
                endif()

                list(APPEND LIBGIT2_LIBRARIES LIBGIT2::${LIBRARY_FILENAME})
            endif()
        endforeach()

        if (NOT TARGET  LIBGIT2::LIBGIT2)
            add_library(LIBGIT2::LIBGIT2 INTERFACE IMPORTED)
            set_target_properties(LIBGIT2::LIBGIT2 PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${LIBGIT2_INCLUDE_DIRS}"
                INTERFACE_LINK_LIBRARIES      "${LIBGIT2_LIBRARIES}"
            )
        endif()

        if (PKG_CONFIG_LIBGIT2_VERSION)
            set(LIBGIT2_VERSION ${PKG_CONFIG_LIBGIT2_VERSION})
        endif()
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibGit2 REQUIRED_VARS LIBGIT2_LIBRARIES LIBGIT2_INCLUDE_DIRS VERSION_VAR LIBGIT2_VERSION)

mark_as_advanced(LIBGIT2_INCLUDE_DIRS LIBGIT2_LIBRARIES)
