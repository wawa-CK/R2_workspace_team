# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target super_lio::super_lio
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${super_lio_TARGETS}.
if(super_lio_TARGETS AND NOT TARGET super_lio::super_lio)
  add_library(super_lio::super_lio INTERFACE IMPORTED)
  set_target_properties(super_lio::super_lio PROPERTIES
    INTERFACE_LINK_LIBRARIES "${super_lio_TARGETS}")
endif()
