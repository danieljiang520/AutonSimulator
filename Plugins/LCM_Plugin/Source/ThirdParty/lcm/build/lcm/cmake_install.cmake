# Install script for directory: /home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/build/lcm/liblcm.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lcm" TYPE FILE FILES
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/eventlog.h"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/lcm.h"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/lcm_coretypes.h"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/lcm_version.h"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/lcm-cpp.hpp"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/lcm-cpp-impl.hpp"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/build/lcm/lcm_export.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblcm.so.1.4.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblcm.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblcm.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/build/lcm/liblcm.so.1.4.0"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/build/lcm/liblcm.so.1"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/build/lcm/liblcm.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblcm.so.1.4.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblcm.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblcm.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lcm" TYPE FILE FILES
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/eventlog.h"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/lcm.h"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/lcm_coretypes.h"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/lcm_version.h"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/lcm-cpp.hpp"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/lcm/lcm-cpp-impl.hpp"
    "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/build/lcm/lcm_export.h"
    )
endif()

