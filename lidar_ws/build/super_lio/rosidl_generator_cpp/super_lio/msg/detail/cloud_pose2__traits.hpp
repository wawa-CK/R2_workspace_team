// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from super_lio:msg/CloudPose2.idl
// generated code does not contain a copyright notice

#ifndef SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__TRAITS_HPP_
#define SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "super_lio/msg/detail/cloud_pose2__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace super_lio
{

namespace msg
{

inline void to_flow_style_yaml(
  const CloudPose2 & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: pose
  {
    if (msg.pose.size() == 0) {
      out << "pose: []";
    } else {
      out << "pose: [";
      size_t pending_items = msg.pose.size();
      for (auto item : msg.pose) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: cloud_lidar
  {
    if (msg.cloud_lidar.size() == 0) {
      out << "cloud_lidar: []";
    } else {
      out << "cloud_lidar: [";
      size_t pending_items = msg.cloud_lidar.size();
      for (auto item : msg.cloud_lidar) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CloudPose2 & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.pose.size() == 0) {
      out << "pose: []\n";
    } else {
      out << "pose:\n";
      for (auto item : msg.pose) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: cloud_lidar
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.cloud_lidar.size() == 0) {
      out << "cloud_lidar: []\n";
    } else {
      out << "cloud_lidar:\n";
      for (auto item : msg.cloud_lidar) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CloudPose2 & msg, bool use_flow_style = false)
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
  const super_lio::msg::CloudPose2 & msg,
  std::ostream & out, size_t indentation = 0)
{
  super_lio::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use super_lio::msg::to_yaml() instead")]]
inline std::string to_yaml(const super_lio::msg::CloudPose2 & msg)
{
  return super_lio::msg::to_yaml(msg);
}

template<>
inline const char * data_type<super_lio::msg::CloudPose2>()
{
  return "super_lio::msg::CloudPose2";
}

template<>
inline const char * name<super_lio::msg::CloudPose2>()
{
  return "super_lio/msg/CloudPose2";
}

template<>
struct has_fixed_size<super_lio::msg::CloudPose2>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<super_lio::msg::CloudPose2>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<super_lio::msg::CloudPose2>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__TRAITS_HPP_
