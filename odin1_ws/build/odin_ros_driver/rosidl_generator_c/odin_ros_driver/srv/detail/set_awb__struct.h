// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from odin_ros_driver:srv/SetAwb.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__SET_AWB__STRUCT_H_
#define ODIN_ROS_DRIVER__SRV__DETAIL__SET_AWB__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SetAwb in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__SetAwb_Request
{
  uint8_t mode;
  float rgain;
  float bgain;
} odin_ros_driver__srv__SetAwb_Request;

// Struct for a sequence of odin_ros_driver__srv__SetAwb_Request.
typedef struct odin_ros_driver__srv__SetAwb_Request__Sequence
{
  odin_ros_driver__srv__SetAwb_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__SetAwb_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/SetAwb in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__SetAwb_Response
{
  bool success;
  /// 0=ok, >0=device error (400..405 or 0xFF), <0=SDK error
  int32_t rc;
} odin_ros_driver__srv__SetAwb_Response;

// Struct for a sequence of odin_ros_driver__srv__SetAwb_Response.
typedef struct odin_ros_driver__srv__SetAwb_Response__Sequence
{
  odin_ros_driver__srv__SetAwb_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__SetAwb_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__SET_AWB__STRUCT_H_
