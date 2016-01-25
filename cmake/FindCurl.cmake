#.rst:
# FindCurl
# --------
#
# Find curl, libcurl, and its headers.
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines `IMPORTED` targets
#   ``Curl::Curl``
#   ``Curl::LibCurl``
#
# Hints
# ^^^^^
#
# A user may set ``Curl_ROOT`` to a Curl installation root to tell this
# module where to look.

if(NOT Curl_ROOT)
  set(Curl_ROOT "")
endif()

# Look for the header file.
find_path(CURL_INCLUDE_DIR NAMES curl/curl.h PATHS ${Curl_ROOT} PATH_SUFFIXES "include")
mark_as_advanced(CURL_INCLUDE_DIR)

find_library(CURL_LIBRARY NAMES curl PATHS ${Curl_ROOT} PATH_SUFFIXES "lib")
mark_as_advanced(CURL_LIBRARY)

find_program(CURL_PROGRAM NAMES curl PATHS ${Curl_ROOT} PATH_SUFFIXES "bin")
mark_as_advanced(CURL_PROGRAM)

if(NOT CURL_LIBRARY_NOTFOUND)
  add_library(Curl::LibCurl UNKNOWN IMPORTED)
  set_target_properties(Curl::LibCurl PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CURL_INCLUDE_DIR}"
    IMPORTED_LOCATION "${CURL_LIBRARY}")
endif()

if(NOT CURL_PROGRAM_NOTFOUND)
  add_executable(Curl::Curl IMPORTED GLOBAL)
endif()

