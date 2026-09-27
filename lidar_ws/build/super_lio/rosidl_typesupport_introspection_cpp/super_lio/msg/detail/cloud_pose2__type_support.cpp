// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from super_lio:msg/CloudPose2.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "super_lio/msg/detail/cloud_pose2__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace super_lio
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void CloudPose2_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) super_lio::msg::CloudPose2(_init);
}

void CloudPose2_fini_function(void * message_memory)
{
  auto typed_message = static_cast<super_lio::msg::CloudPose2 *>(message_memory);
  typed_message->~CloudPose2();
}

size_t size_function__CloudPose2__pose(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__CloudPose2__pose(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__CloudPose2__pose(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__CloudPose2__pose(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__CloudPose2__pose(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__CloudPose2__pose(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__CloudPose2__pose(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__CloudPose2__pose(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__CloudPose2__cloud_lidar(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__CloudPose2__cloud_lidar(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__CloudPose2__cloud_lidar(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__CloudPose2__cloud_lidar(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__CloudPose2__cloud_lidar(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__CloudPose2__cloud_lidar(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__CloudPose2__cloud_lidar(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__CloudPose2__cloud_lidar(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember CloudPose2_message_member_array[3] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(super_lio::msg::CloudPose2, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "pose",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(super_lio::msg::CloudPose2, pose),  // bytes offset in struct
    nullptr,  // default value
    size_function__CloudPose2__pose,  // size() function pointer
    get_const_function__CloudPose2__pose,  // get_const(index) function pointer
    get_function__CloudPose2__pose,  // get(index) function pointer
    fetch_function__CloudPose2__pose,  // fetch(index, &value) function pointer
    assign_function__CloudPose2__pose,  // assign(index, value) function pointer
    resize_function__CloudPose2__pose  // resize(index) function pointer
  },
  {
    "cloud_lidar",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(super_lio::msg::CloudPose2, cloud_lidar),  // bytes offset in struct
    nullptr,  // default value
    size_function__CloudPose2__cloud_lidar,  // size() function pointer
    get_const_function__CloudPose2__cloud_lidar,  // get_const(index) function pointer
    get_function__CloudPose2__cloud_lidar,  // get(index) function pointer
    fetch_function__CloudPose2__cloud_lidar,  // fetch(index, &value) function pointer
    assign_function__CloudPose2__cloud_lidar,  // assign(index, value) function pointer
    resize_function__CloudPose2__cloud_lidar  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers CloudPose2_message_members = {
  "super_lio::msg",  // message namespace
  "CloudPose2",  // message name
  3,  // number of fields
  sizeof(super_lio::msg::CloudPose2),
  CloudPose2_message_member_array,  // message members
  CloudPose2_init_function,  // function to initialize message memory (memory has to be allocated)
  CloudPose2_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t CloudPose2_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &CloudPose2_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace super_lio


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<super_lio::msg::CloudPose2>()
{
  return &::super_lio::msg::rosidl_typesupport_introspection_cpp::CloudPose2_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, super_lio, msg, CloudPose2)() {
  return &::super_lio::msg::rosidl_typesupport_introspection_cpp::CloudPose2_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
