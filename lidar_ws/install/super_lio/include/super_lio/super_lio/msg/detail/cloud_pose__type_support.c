// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from super_lio:msg/CloudPose.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "super_lio/msg/detail/cloud_pose__rosidl_typesupport_introspection_c.h"
#include "super_lio/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "super_lio/msg/detail/cloud_pose__functions.h"
#include "super_lio/msg/detail/cloud_pose__struct.h"


// Include directives for member types
// Member `pose`
#include "geometry_msgs/msg/pose.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__rosidl_typesupport_introspection_c.h"
// Member `cloud`
#include "sensor_msgs/msg/point_cloud2.h"
// Member `cloud`
#include "sensor_msgs/msg/detail/point_cloud2__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  super_lio__msg__CloudPose__init(message_memory);
}

void super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_fini_function(void * message_memory)
{
  super_lio__msg__CloudPose__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_message_member_array[2] = {
  {
    "pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(super_lio__msg__CloudPose, pose),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "cloud",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(super_lio__msg__CloudPose, cloud),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_message_members = {
  "super_lio__msg",  // message namespace
  "CloudPose",  // message name
  2,  // number of fields
  sizeof(super_lio__msg__CloudPose),
  super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_message_member_array,  // message members
  super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_init_function,  // function to initialize message memory (memory has to be allocated)
  super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_message_type_support_handle = {
  0,
  &super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_super_lio
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, super_lio, msg, CloudPose)() {
  super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Pose)();
  super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sensor_msgs, msg, PointCloud2)();
  if (!super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_message_type_support_handle.typesupport_identifier) {
    super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &super_lio__msg__CloudPose__rosidl_typesupport_introspection_c__CloudPose_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
