// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from odin_ros_driver:srv/GetAe.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__GET_AE__STRUCT_H_
#define ODIN_ROS_DRIVER__SRV__DETAIL__GET_AE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetAe in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__GetAe_Request
{
  uint8_t structure_needs_at_least_one_member;
} odin_ros_driver__srv__GetAe_Request;

// Struct for a sequence of odin_ros_driver__srv__GetAe_Request.
typedef struct odin_ros_driver__srv__GetAe_Request__Sequence
{
  odin_ros_driver__srv__GetAe_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__GetAe_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/GetAe in the package odin_ros_driver.
typedef struct odin_ros_driver__srv__GetAe_Response
{
  /// true if rc == 0
  bool success;
  /// 0=ok, >0=device error (400..405 or 0xFF), <0=SDK error
  int32_t rc;
  /// seconds (manual range 0.0001 .. 0.033)
  float exposure_time;
  /// analog gain
  float gain;
  /// equivalent ISO
  int32_t iso;
  /// average frame brightness
  float brightness;
  /// 1=converged, 0=not converged
  uint8_t is_converged;
  /// ambient luminance level
  float env_lv;
  /// current frame rate
  float fps;
} odin_ros_driver__srv__GetAe_Response;

// Struct for a sequence of odin_ros_driver__srv__GetAe_Response.
typedef struct odin_ros_driver__srv__GetAe_Response__Sequence
{
  odin_ros_driver__srv__GetAe_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} odin_ros_driver__srv__GetAe_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__GET_AE__STRUCT_H_
