#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "base16::shared" for configuration "Release"
set_property(TARGET base16::shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(base16::shared PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libbase16.so"
  IMPORTED_SONAME_RELEASE "libbase16.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS base16::shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_base16::shared "${_IMPORT_PREFIX}/lib/libbase16.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
