// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from super_lio:msg/CloudPose2.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "super_lio/msg/detail/cloud_pose2__rosidl_typesupport_introspection_c.h"
#include "super_lio/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "super_lio/msg/detail/cloud_pose2__functions.h"
#include "super_lio/msg/detail/cloud_pose2__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `pose`
// Member `cloud_lidar`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  super_lio__msg__CloudPose2__init(message_memory);
}

void super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_fini_function(void * message_memory)
{
  super_lio__msg__CloudPose2__fini(message_memory);
}

size_t super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__size_function__CloudPose2__pose(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_const_function__CloudPose2__pose(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_function__CloudPose2__pose(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__fetch_function__CloudPose2__pose(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_const_function__CloudPose2__pose(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__assign_function__CloudPose2__pose(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_function__CloudPose2__pose(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__resize_function__CloudPose2__pose(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__size_function__CloudPose2__cloud_lidar(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_const_function__CloudPose2__cloud_lidar(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_function__CloudPose2__cloud_lidar(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__fetch_function__CloudPose2__cloud_lidar(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_const_function__CloudPose2__cloud_lidar(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__assign_function__CloudPose2__cloud_lidar(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_function__CloudPose2__cloud_lidar(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__resize_function__CloudPose2__cloud_lidar(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_message_member_array[3] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(super_lio__msg__CloudPose2, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(super_lio__msg__CloudPose2, pose),  // bytes offset in struct
    NULL,  // default value
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__size_function__CloudPose2__pose,  // size() function pointer
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_const_function__CloudPose2__pose,  // get_const(index) function pointer
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_function__CloudPose2__pose,  // get(index) function pointer
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__fetch_function__CloudPose2__pose,  // fetch(index, &value) function pointer
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__assign_function__CloudPose2__pose,  // assign(index, value) function pointer
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__resize_function__CloudPose2__pose  // resize(index) function pointer
  },
  {
    "cloud_lidar",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(super_lio__msg__CloudPose2, cloud_lidar),  // bytes offset in struct
    NULL,  // default value
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__size_function__CloudPose2__cloud_lidar,  // size() function pointer
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_const_function__CloudPose2__cloud_lidar,  // get_const(index) function pointer
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__get_function__CloudPose2__cloud_lidar,  // get(index) function pointer
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__fetch_function__CloudPose2__cloud_lidar,  // fetch(index, &value) function pointer
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__assign_function__CloudPose2__cloud_lidar,  // assign(index, value) function pointer
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__resize_function__CloudPose2__cloud_lidar  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_message_members = {
  "super_lio__msg",  // message namespace
  "CloudPose2",  // message name
  3,  // number of fields
  sizeof(super_lio__msg__CloudPose2),
  super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_message_member_array,  // message members
  super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_init_function,  // function to initialize message memory (memory has to be allocated)
  super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_message_type_support_handle = {
  0,
  &super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_super_lio
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, super_lio, msg, CloudPose2)() {
  super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_message_type_support_handle.typesupport_identifier) {
    super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &super_lio__msg__CloudPose2__rosidl_typesupport_introspection_c__CloudPose2_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
