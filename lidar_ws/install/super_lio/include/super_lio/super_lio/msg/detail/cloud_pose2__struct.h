// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from super_lio:msg/CloudPose2.idl
// generated code does not contain a copyright notice

#ifndef SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__STRUCT_H_
#define SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'pose'
// Member 'cloud_lidar'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/CloudPose2 in the package super_lio.
/**
  * CloudPose2.msg
 */
typedef struct super_lio__msg__CloudPose2
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__float__Sequence pose;
  /// dense point cloud
  rosidl_runtime_c__float__Sequence cloud_lidar;
} super_lio__msg__CloudPose2;

// Struct for a sequence of super_lio__msg__CloudPose2.
typedef struct super_lio__msg__CloudPose2__Sequence
{
  super_lio__msg__CloudPose2 * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} super_lio__msg__CloudPose2__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__STRUCT_H_
