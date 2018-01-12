# Install script for directory: E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "E:/Charles/minimal_checkout/openbr/build_vs2010_32/install")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/asm.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/basedesc.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/classicdesc.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/convshape.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/err.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/eyedet.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/eyedist.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/faceroi.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/hat.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/hatdesc.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/landmarks.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/misc.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/pinstart.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/print.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/shape17.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/shapehacks.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/shapemod.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/startshape.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/stasm.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/stasmcascadeclassifier.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/stasmhash.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/stasm_landmarks.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/stasm_lib.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/stasm_lib_ext.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/MOD_1/facedet.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/MOD_1/initasm.h"
    "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/stasm/MOD_1/yaw00.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/build/Debug/stasm.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/build/Release/stasm.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/build/MinSizeRel/stasm.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/build/RelWithDebInfo/stasm.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("E:/Charles/minimal_checkout/openbr/3rdparty/stasm4.0.0/build/stasm/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

