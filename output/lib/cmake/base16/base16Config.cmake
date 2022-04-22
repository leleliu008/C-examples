
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was base16Config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(BASE16_VERSION       "1.0.0")
set(BASE16_VERSION_MAJOR "1")
set(BASE16_VERSION_MINOR "0")
set(BASE16_VERSION_PATCH "0")

set_and_check(BASE16_INSTALL_DIR "${PACKAGE_PREFIX_DIR}")
set_and_check(BASE16_INCLUDE_DIR "${PACKAGE_PREFIX_DIR}/include")
set_and_check(BASE16_LIBRARY_DIR "${PACKAGE_PREFIX_DIR}/lib")

include("${CMAKE_CURRENT_LIST_DIR}/base16-sharedTargets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/base16-staticTargets.cmake")

set(BASE16_LIBRARY_SHARED base16::shared)
set(BASE16_LIBRARY_STATIC base16::static)
set(BASE16_LIBRARY        base16::static)
