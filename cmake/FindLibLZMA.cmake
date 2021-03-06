# Try to find LibLZMA library and include path.
# Once done this will define
#
# LIBLZMA_INCLUDE_DIRS - where to find lzma/version.h, etc.
# LIBLZMA_LIBRARIES - List of libraries when using liblzma.
# LIBLZMA_FOUND - True if liblzma found.

if(WIN32)
  find_path(LIBLZMA_INCLUDE_DIR lzma/version.h $ENV{PROGRAMFILES}/xz/include DOC "The directory where lzma/version.h resides")
  find_library(LIBLZMA_LIBRARY NAMES lzma liblzma PATHS $ENV{PROGRAMFILES}/xz/lib DOC "The liblzma library")

else(WIN32)
  find_path(LIBLZMA_INCLUDE_DIR lzma/version.h DOC "The directory where lzma/version.h resides")
  find_library(LIBLZMA_LIBRARY NAMES lzma liblzma DOC "The liblzma library")

endif(WIN32)

if(LIBLZMA_INCLUDE_DIR AND LIBLZMA_LIBRARY)
  set(LIBLZMA_FOUND 1)
  set(LIBLZMA_LIBRARIES ${LIBLZMA_LIBRARY})
  set(LIBLZMA_INCLUDE_DIRS ${LIBLZMA_INCLUDE_DIR})
else(LIBLZMA_INCLUDE_DIR AND LIBLZMA_LIBRARY)
    set(LIBLZMA_FOUND 0)
    set(LIBLZMA_LIBRARIES)
    set(LIBLZMA_INCLUDE_DIRS)
endif(LIBLZMA_INCLUDE_DIR AND LIBLZMA_LIBRARY)

mark_as_advanced(LIBLZMA_INCLUDE_DIR)
mark_as_advanced(LIBLZMA_LIBRARY)
mark_as_advanced(LIBLZMA_FOUND)

if(NOT LIBLZMA_FOUND)
  set(LIBLZMA_DIR_MESSAGE "liblzma was not found. Make sure LIBLZMA_LIBRARY and LIBLZMA_INCLUDE_DIR are set.")
  if(NOT LIBLZMA_FIND_QUIETLY)
    message(STATUS "${LIBLZMA_DIR_MESSAGE}")
  else(NOT LIBLZMA_FIND_QUIETLY)
    if(LIBLZMA_FIND_REQUIRED)
      message(FATAL_ERROR "${LIBLZMA_DIR_MESSAGE}")
    endif(LIBLZMA_FIND_REQUIRED)
  endif(NOT LIBLZMA_FIND_QUIETLY)
endif(NOT LIBLZMA_FOUND)
