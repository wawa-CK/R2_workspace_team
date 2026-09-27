// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from super_lio:msg/CloudPose.idl
// generated code does not contain a copyright notice

#ifndef SUPER_LIO__MSG__DETAIL__CLOUD_POSE__STRUCT_H_
#define SUPER_LIO__MSG__DETAIL__CLOUD_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.h"
// Member 'cloud'
#include "sensor_msgs/msg/detail/point_cloud2__struct.h"

/// Struct defined in msg/CloudPose in the package super_lio.
/**
  * CloudPose.msg
 */
typedef struct super_lio__msg__CloudPose
{
  geometry_msgs__msg__Pose pose;
  sensor_msgs__msg__PointCloud2 cloud;
} super_lio__msg__CloudPose;

// Struct for a sequence of super_lio__msg__CloudPose.
typedef struct super_lio__msg__CloudPose__Sequence
{
  super_lio__msg__CloudPose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} super_lio__msg__CloudPose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SUPER_LIO__MSG__DETAIL__CLOUD_POSE__STRUCT_H_
