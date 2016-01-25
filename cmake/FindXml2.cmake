#.rst:
# FindXml2
# --------
#
# Find libxml2, and its headers.
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines `IMPORTED` targets
#   ``Xml2::LibXml2``
#

# Look for the header file.
find_path(XML2_INCLUDE_DIR NAMES "libxml/xpath.h" PATH_SUFFIXES "libxml2")
mark_as_advanced(XML2_INCLUDE_DIR)

find_library(XML2_LIBRARY NAMES xml2)
mark_as_advanced(XML2_LIBRARY)

if(NOT XML2_LIBRARY_NOTFOUND)
  add_library(Xml2::LibXml2 UNKNOWN IMPORTED)
  set_target_properties(Xml2::LibXml2 PROPERTIES
	  INTERFACE_INCLUDE_DIRECTORIES "${XML2_INCLUDE_DIR}"
	  IMPORTED_LOCATION "${XML2_LIBRARY}")
endif()

