// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from odin_ros_driver:srv/ResetAlgo.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__RESET_ALGO__STRUCT_H_
#define ODIN_ROS_DRIVER__SRV__DETAIL__RESET_ALGO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/ResetAlgo in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__ResetAlgo_Request
{
  int32_t value;
} odin_ros_driver__srv__ResetAlgo_Request;

// Struct for a sequence of odin_ros_driver__srv__ResetAlgo_Request.
typedef struct odin_ros_driver__srv__ResetAlgo_Request__Sequence
{
  odin_ros_driver__srv__ResetAlgo_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__ResetAlgo_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/ResetAlgo in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__ResetAlgo_Response
{
  /// true if rc == 0
  bool success;
  /// 0=ok, see lidar_set_custom_parameter error codes
  int32_t rc;
} odin_ros_driver__srv__ResetAlgo_Response;

// Struct for a sequence of odin_ros_driver__srv__ResetAlgo_Response.
typedef struct odin_ros_driver__srv__ResetAlgo_Response__Sequence
{
  odin_ros_driver__srv__ResetAlgo_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__ResetAlgo_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__RESET_ALGO__STRUCT_H_
