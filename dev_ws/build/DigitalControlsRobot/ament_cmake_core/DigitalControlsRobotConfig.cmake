# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_DigitalControlsRobot_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED DigitalControlsRobot_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(DigitalControlsRobot_FOUND FALSE)
  elseif(NOT DigitalControlsRobot_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(DigitalControlsRobot_FOUND FALSE)
  endif()
  return()
endif()
set(_DigitalControlsRobot_CONFIG_INCLUDED TRUE)

# output package information
if(NOT DigitalControlsRobot_FIND_QUIETLY)
  message(STATUS "Found DigitalControlsRobot: 0.0.0 (${DigitalControlsRobot_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'DigitalControlsRobot' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${DigitalControlsRobot_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(DigitalControlsRobot_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${DigitalControlsRobot_DIR}/${_extra}")
endforeach()
