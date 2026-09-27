// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from odin_ros_driver:srv/SetAe.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__SET_AE__TRAITS_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__SET_AE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "odin_ros_driver/srv/detail/set_ae__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace odin_ros_driver
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetAe_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: exposure_time
  {
    out << "exposure_time: ";
    rosidl_generator_traits::value_to_yaml(msg.exposure_time, out);
    out << ", ";
  }

  // member: gain
  {
    out << "gain: ";
    rosidl_generator_traits::value_to_yaml(msg.gain, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetAe_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: exposure_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "exposure_time: ";
    rosidl_generator_traits::value_to_yaml(msg.exposure_time, out);
    out << "\n";
  }

  // member: gain
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gain: ";
    rosidl_generator_traits::value_to_yaml(msg.gain, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetAe_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace odin_ros_driver

namespace rosidl_generator_traits
{

[[deprecated("use odin_ros_driver::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const odin_ros_driver::srv::SetAe_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  odin_ros_driver::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use odin_ros_driver::srv::to_yaml() instead")]]
inline std::string to_yaml(const odin_ros_driver::srv::SetAe_Request & msg)
{
  return odin_ros_driver::srv::to_yaml(msg);
}

template<>
inline const char * data_type<odin_ros_driver::srv::SetAe_Request>()
{
  return "odin_ros_driver::srv::SetAe_Request";
}

template<>
inline const char * name<odin_ros_driver::srv::SetAe_Request>()
{
  return "odin_ros_driver/srv/SetAe_Request";
}

template<>
struct has_fixed_size<odin_ros_driver::srv::SetAe_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<odin_ros_driver::srv::SetAe_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<odin_ros_driver::srv::SetAe_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace odin_ros_driver
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetAe_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: rc
  {
    out << "rc: ";
    rosidl_generator_traits::value_to_yaml(msg.rc, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetAe_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: rc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rc: ";
    rosidl_generator_traits::value_to_yaml(msg.rc, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetAe_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace odin_ros_driver

namespace rosidl_generator_traits
{

[[deprecated("use odin_ros_driver::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const odin_ros_driver::srv::SetAe_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  odin_ros_driver::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use odin_ros_driver::srv::to_yaml() instead")]]
inline std::string to_yaml(const odin_ros_driver::srv::SetAe_Response & msg)
{
  return odin_ros_driver::srv::to_yaml(msg);
}

template<>
inline const char * data_type<odin_ros_driver::srv::SetAe_Response>()
{
  return "odin_ros_driver::srv::SetAe_Response";
}

template<>
inline const char * name<odin_ros_driver::srv::SetAe_Response>()
{
  return "odin_ros_driver/srv/SetAe_Response";
}

template<>
struct has_fixed_size<odin_ros_driver::srv::SetAe_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<odin_ros_driver::srv::SetAe_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<odin_ros_driver::srv::SetAe_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<odin_ros_driver::srv::SetAe>()
{
  return "odin_ros_driver::srv::SetAe";
}

template<>
inline const char * name<odin_ros_driver::srv::SetAe>()
{
  return "odin_ros_driver/srv/SetAe";
}

template<>
struct has_fixed_size<odin_ros_driver::srv::SetAe>
  : std::integral_constant<
    bool,
    has_fixed_size<odin_ros_driver::srv::SetAe_Request>::value &&
    has_fixed_size<odin_ros_driver::srv::SetAe_Response>::value
  >
{
};

template<>
struct has_bounded_size<odin_ros_driver::srv::SetAe>
  : std::integral_constant<
    bool,
    has_bounded_size<odin_ros_driver::srv::SetAe_Request>::value &&
    has_bounded_size<odin_ros_driver::srv::SetAe_Response>::value
  >
{
};

template<>
struct is_service<odin_ros_driver::srv::SetAe>
  : std::true_type
{
};

template<>
struct is_service_request<odin_ros_driver::srv::SetAe_Request>
  : std::true_type
{
};

template<>
struct is_service_response<odin_ros_driver::srv::SetAe_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__SET_AE__TRAITS_HPP_
