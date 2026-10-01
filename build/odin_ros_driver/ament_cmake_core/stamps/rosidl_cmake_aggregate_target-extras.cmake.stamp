# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target odin_ros_driver::odin_ros_driver
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${odin_ros_driver_TARGETS}.
if(odin_ros_driver_TARGETS AND NOT TARGET odin_ros_driver::odin_ros_driver)
  add_library(odin_ros_driver::odin_ros_driver INTERFACE IMPORTED)
  set_target_properties(odin_ros_driver::odin_ros_driver PROPERTIES
    INTERFACE_LINK_LIBRARIES "${odin_ros_driver_TARGETS}")
endif()
