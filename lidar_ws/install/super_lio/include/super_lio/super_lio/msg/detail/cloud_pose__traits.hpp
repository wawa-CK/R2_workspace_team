// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from super_lio:msg/CloudPose.idl
// generated code does not contain a copyright notice

#ifndef SUPER_LIO__MSG__DETAIL__CLOUD_POSE__TRAITS_HPP_
#define SUPER_LIO__MSG__DETAIL__CLOUD_POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "super_lio/msg/detail/cloud_pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"
// Member 'cloud'
#include "sensor_msgs/msg/detail/point_cloud2__traits.hpp"

namespace super_lio
{

namespace msg
{

inline void to_flow_style_yaml(
  const CloudPose & msg,
  std::ostream & out)
{
  out << "{";
  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
    out << ", ";
  }

  // member: cloud
  {
    out << "cloud: ";
    to_flow_style_yaml(msg.cloud, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CloudPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }

  // member: cloud
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cloud:\n";
    to_block_style_yaml(msg.cloud, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CloudPose & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace super_lio

namespace rosidl_generator_traits
{

[[deprecated("use super_lio::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const super_lio::msg::CloudPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  super_lio::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use super_lio::msg::to_yaml() instead")]]
inline std::string to_yaml(const super_lio::msg::CloudPose & msg)
{
  return super_lio::msg::to_yaml(msg);
}

template<>
inline const char * data_type<super_lio::msg::CloudPose>()
{
  return "super_lio::msg::CloudPose";
}

template<>
inline const char * name<super_lio::msg::CloudPose>()
{
  return "super_lio/msg/CloudPose";
}

template<>
struct has_fixed_size<super_lio::msg::CloudPose>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Pose>::value && has_fixed_size<sensor_msgs::msg::PointCloud2>::value> {};

template<>
struct has_bounded_size<super_lio::msg::CloudPose>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Pose>::value && has_bounded_size<sensor_msgs::msg::PointCloud2>::value> {};

template<>
struct is_message<super_lio::msg::CloudPose>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SUPER_LIO__MSG__DETAIL__CLOUD_POSE__TRAITS_HPP_
