#.rst:
# FindFuse
# --------
#
# Find libfuse, and its headers.
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines `IMPORTED` targets
#   ``Fuse::LibFuse``
#

# Look for the header file.
find_path(FUSE_INCLUDE_DIR NAMES fuse/fuse.h)
mark_as_advanced(FUSE_INCLUDE_DIR)

find_library(FUSE_LIBRARY NAMES fuse)
mark_as_advanced(FUSE_LIBRARY)

if(NOT FUSE_LIBRARY_NOTFOUND)
  add_library(Fuse::LibFuse UNKNOWN IMPORTED)
  set_target_properties(Fuse::LibFuse PROPERTIES
	  INTERFACE_INCLUDE_DIRECTORIES "${FUSE_INCLUDE_DIR}"
	  IMPORTED_LOCATION "${FUSE_LIBRARY}")
endif()

