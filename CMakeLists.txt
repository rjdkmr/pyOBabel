cmake_minimum_required(VERSION 2.6)

# Cmake modules/macros are in a subdirectory to keep this file cleaner
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#set(OBABEL_PYTHON_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/pyOBabel")
set(OBABEL_PYTHON_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/pyOBabel")

set(OBabel_PythonDir "${CMAKE_SOURCE_DIR}/pyOBabel")

#
#set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
#include(ExternalProject)
#ExternalProject_Add(openbabel
#  GIT_REPOSITORY https://github.com/openbabel/openbabel.git
#  CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}/openbabel"
#)



# Check for c++0x, c++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "C++11 complier not found. Please use a newer compiler, or a newer standard library.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")

# Add python
#-------
# pull in python:
set(Python_ADDITIONAL_VERSIONS 3.0 3.1 3.2 3.3 3.4 3.5 3.6 3.7)
find_package(PythonInterp)
if (NOT PYTHONINTERP_FOUND)
    message(FATAL_ERROR "Python3 not found... Please install python3. ")
endif(NOT PYTHONINTERP_FOUND)

find_package(PythonLibs)
if (NOT PythonLibs_FOUND)
    message(FATAL_ERROR "Python developement library not found. On Ubuntu-like OS install python3-dev. On fedora/centos/RHEL install python3-devel.")
endif(NOT PythonLibs_FOUND)
include_directories(${PYTHON_INCLUDE_DIR})


if (NOT PYTHON_INSTDIR)
    # Determine correct installation directory for Python bindings
    # From http://plplot.svn.sourceforge.net/viewvc/plplot/trunk/cmake/modules/python.cmake?revision=11014
    execute_process(
        COMMAND
        ${PYTHON_EXECUTABLE} -c "from __future__ import print_function; from distutils import sysconfig; print(sysconfig.get_python_lib(1,0,prefix='${CMAKE_INSTALL_PREFIX}'))"
        OUTPUT_VARIABLE PYTHON_INSTDIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
      )
endif (NOT PYTHON_INSTDIR)
message("Python Install directory ${PYTHON_INSTDIR}")
install(DIRECTORY pyOBabel DESTINATION ${PYTHON_INSTDIR}
COMPONENT python
PATTERN ".svn" EXCLUDE
PATTERN "test_data" EXCLUDE
PATTERN "testData" EXCLUDE
PATTERN "test_list*" EXCLUDE
PATTERN "CMake*" EXCLUDE
PATTERN "Basement" EXCLUDE
PATTERN "UnitTest*" EXCLUDE
)
set(OBabel_PythonDir "${PYTHON_INSTDIR}/pyOpenBabel")

# find and setup openbabel
find_package(OpenBabel2 REQUIRED)
include_directories(${OPENBABEL2_INCLUDE_DIR})

## Problem in TRAVIS
find_package(ZLIB)
if(ZLIB_FOUND)
  add_definitions(-DHAVE_LIBZ)
  include_directories(${ZLIB_INCLUDE_DIR})
  # Longstanding unsolved problem with compression under Windows
  if(WIN32)
    add_definitions(-DDISABLE_WRITE_COMPRESSION)
  endif()
endif()

# Add pybind11
set(PYBIND11_CPP_STANDARD -std=c++11)
add_subdirectory(pybind11)

add_subdirectory(src)
