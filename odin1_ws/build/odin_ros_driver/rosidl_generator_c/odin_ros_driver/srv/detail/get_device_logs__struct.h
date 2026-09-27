// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from odin_ros_driver:srv/GetDeviceLogs.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__GET_DEVICE_LOGS__STRUCT_H_
#define ODIN_ROS_DRIVER__SRV__DETAIL__GET_DEVICE_LOGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'dest_dir'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetDeviceLogs in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__GetDeviceLogs_Request
{
  rosidl_runtime_c__String dest_dir;
} odin_ros_driver__srv__GetDeviceLogs_Request;

// Struct for a sequence of odin_ros_driver__srv__GetDeviceLogs_Request.
typedef struct odin_ros_driver__srv__GetDeviceLogs_Request__Sequence
{
  odin_ros_driver__srv__GetDeviceLogs_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__GetDeviceLogs_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/GetDeviceLogs in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__GetDeviceLogs_Response
{
  /// true if rc == 0
  bool success;
  /// 0=ok, -1=invalid args, -2=transfer in progress, -3=timeout/stall
  int32_t rc;
} odin_ros_driver__srv__GetDeviceLogs_Response;

// Struct for a sequence of odin_ros_driver__srv__GetDeviceLogs_Response.
typedef struct odin_ros_driver__srv__GetDeviceLogs_Response__Sequence
{
  odin_ros_driver__srv__GetDeviceLogs_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__GetDeviceLogs_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__GET_DEVICE_LOGS__STRUCT_H_
