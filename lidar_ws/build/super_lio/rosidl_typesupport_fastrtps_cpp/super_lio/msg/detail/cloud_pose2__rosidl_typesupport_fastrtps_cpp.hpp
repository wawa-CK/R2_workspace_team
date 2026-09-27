// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from super_lio:msg/CloudPose2.idl
// generated code does not contain a copyright notice

#ifndef SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "super_lio/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "super_lio/msg/detail/cloud_pose2__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace super_lio
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_super_lio
cdr_serialize(
  const super_lio::msg::CloudPose2 & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_super_lio
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  super_lio::msg::CloudPose2 & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_super_lio
get_serialized_size(
  const super_lio::msg::CloudPose2 & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_super_lio
max_serialized_size_CloudPose2(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace super_lio

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_super_lio
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, super_lio, msg, CloudPose2)();

#ifdef __cplusplus
}
#endif

#endif  // SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
