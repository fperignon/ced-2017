# - Try to find FFTW
# Once done, this will define
#
#  FFTW_FOUND - system has FFTW
#  FFTW_INCLUDE_DIRS - the FFTW include directories
#  FFTW_LIBRARIES - link these to use FFTW
#
# Set fftw_DIR=where_fftw_is_installed if it's not in a "classic" place or if you want a specific version
#
# Written by F. Pérignon, nov/2009 
# inspired from http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(FFTW_PKGCONF fftw3)

# Include dir
# -- user-defined
find_path(
  FFTW_INCLUDE_DIR
  NAMES fftw3.h 
  #NO_CMAKE_ENVIRONMENT_PATH
  PATHS ${fftw_DIR} PATHS ENV INCLUDE ENV PATH ${FFTW_PKGCONF_INCLUDE_DIRS}
  PATH_SUFFIXES include
  NO_DEFAULT_PATH
  )
# -- default 
find_path(FFTW_INCLUDE_DIR NAMES fftw3.h)

# Finally the library itself
find_library(
  FFTW_LIBRARY
  NAMES fftw3
  PATHS ${fftw_DIR} ${FFTW_INCLUDE_DIR}/.. ENV LIBRARY_PATH ENV LD_LIBRARY_PATH  ${FFTW_PKGCONF_LIBRARY_DIRS} 
  PATH_SUFFIXES lib
  NO_DEFAULT_PATH
)

find_library(FFTW_LIBRARY 
  NAMES fftw3
  )

set(FFTW_PROCESS_INCLUDES FFTW_INCLUDE_DIR)
set(FFTW_PROCESS_LIBS FFTW_LIBRARY)
libfind_process(FFTW)
