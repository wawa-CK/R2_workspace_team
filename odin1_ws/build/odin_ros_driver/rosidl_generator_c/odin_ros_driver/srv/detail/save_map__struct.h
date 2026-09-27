// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from odin_ros_driver:srv/SaveMap.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__SAVE_MAP__STRUCT_H_
#define ODIN_ROS_DRIVER__SRV__DETAIL__SAVE_MAP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SaveMap in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__SaveMap_Request
{
  int32_t value;
} odin_ros_driver__srv__SaveMap_Request;

// Struct for a sequence of odin_ros_driver__srv__SaveMap_Request.
typedef struct odin_ros_driver__srv__SaveMap_Request__Sequence
{
  odin_ros_driver__srv__SaveMap_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__SaveMap_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/SaveMap in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__SaveMap_Response
{
  /// true if the request was accepted (or rc == 0)
  bool success;
  /// 0=ok, -2=another map transfer already in progress
  int32_t rc;
} odin_ros_driver__srv__SaveMap_Response;

// Struct for a sequence of odin_ros_driver__srv__SaveMap_Response.
typedef struct odin_ros_driver__srv__SaveMap_Response__Sequence
{
  odin_ros_driver__srv__SaveMap_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__SaveMap_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__SAVE_MAP__STRUCT_H_
