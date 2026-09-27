// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from odin_ros_driver:srv/GetAwb.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__STRUCT_H_
#define ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetAwb in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__GetAwb_Request
{
  uint8_t structure_needs_at_least_one_member;
} odin_ros_driver__srv__GetAwb_Request;

// Struct for a sequence of odin_ros_driver__srv__GetAwb_Request.
typedef struct odin_ros_driver__srv__GetAwb_Request__Sequence
{
  odin_ros_driver__srv__GetAwb_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__GetAwb_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/GetAwb in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__GetAwb_Response
{
  /// true if rc == 0
  bool success;
  /// 0=ok, >0=device error (400..405 or 0xFF), <0=SDK error
  int32_t rc;
  float rgain;
  float grgain;
  float gbgain;
  float bgain;
  /// color temperature in Kelvin
  float cct;
  /// color temperature deviation
  float ccri;
  /// 1=converged, 0=not converged
  uint8_t is_converged;
} odin_ros_driver__srv__GetAwb_Response;

// Struct for a sequence of odin_ros_driver__srv__GetAwb_Response.
typedef struct odin_ros_driver__srv__GetAwb_Response__Sequence
{
  odin_ros_driver__srv__GetAwb_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__GetAwb_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__STRUCT_H_
