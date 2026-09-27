// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from odin_ros_driver:srv/GetAwb.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__TRAITS_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "odin_ros_driver/srv/detail/get_awb__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace odin_ros_driver
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetAwb_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetAwb_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetAwb_Request & msg, bool use_flow_style = false)
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
  const odin_ros_driver::srv::GetAwb_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  odin_ros_driver::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use odin_ros_driver::srv::to_yaml() instead")]]
inline std::string to_yaml(const odin_ros_driver::srv::GetAwb_Request & msg)
{
  return odin_ros_driver::srv::to_yaml(msg);
}

template<>
inline const char * data_type<odin_ros_driver::srv::GetAwb_Request>()
{
  return "odin_ros_driver::srv::GetAwb_Request";
}

template<>
inline const char * name<odin_ros_driver::srv::GetAwb_Request>()
{
  return "odin_ros_driver/srv/GetAwb_Request";
}

template<>
struct has_fixed_size<odin_ros_driver::srv::GetAwb_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<odin_ros_driver::srv::GetAwb_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<odin_ros_driver::srv::GetAwb_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace odin_ros_driver
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetAwb_Response & msg,
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
    out << ", ";
  }

  // member: rgain
  {
    out << "rgain: ";
    rosidl_generator_traits::value_to_yaml(msg.rgain, out);
    out << ", ";
  }

  // member: grgain
  {
    out << "grgain: ";
    rosidl_generator_traits::value_to_yaml(msg.grgain, out);
    out << ", ";
  }

  // member: gbgain
  {
    out << "gbgain: ";
    rosidl_generator_traits::value_to_yaml(msg.gbgain, out);
    out << ", ";
  }

  // member: bgain
  {
    out << "bgain: ";
    rosidl_generator_traits::value_to_yaml(msg.bgain, out);
    out << ", ";
  }

  // member: cct
  {
    out << "cct: ";
    rosidl_generator_traits::value_to_yaml(msg.cct, out);
    out << ", ";
  }

  // member: ccri
  {
    out << "ccri: ";
    rosidl_generator_traits::value_to_yaml(msg.ccri, out);
    out << ", ";
  }

  // member: is_converged
  {
    out << "is_converged: ";
    rosidl_generator_traits::value_to_yaml(msg.is_converged, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetAwb_Response & msg,
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

  // member: rgain
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rgain: ";
    rosidl_generator_traits::value_to_yaml(msg.rgain, out);
    out << "\n";
  }

  // member: grgain
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "grgain: ";
    rosidl_generator_traits::value_to_yaml(msg.grgain, out);
    out << "\n";
  }

  // member: gbgain
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gbgain: ";
    rosidl_generator_traits::value_to_yaml(msg.gbgain, out);
    out << "\n";
  }

  // member: bgain
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bgain: ";
    rosidl_generator_traits::value_to_yaml(msg.bgain, out);
    out << "\n";
  }

  // member: cct
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cct: ";
    rosidl_generator_traits::value_to_yaml(msg.cct, out);
    out << "\n";
  }

  // member: ccri
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ccri: ";
    rosidl_generator_traits::value_to_yaml(msg.ccri, out);
    out << "\n";
  }

  // member: is_converged
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_converged: ";
    rosidl_generator_traits::value_to_yaml(msg.is_converged, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetAwb_Response & msg, bool use_flow_style = false)
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
  const odin_ros_driver::srv::GetAwb_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  odin_ros_driver::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use odin_ros_driver::srv::to_yaml() instead")]]
inline std::string to_yaml(const odin_ros_driver::srv::GetAwb_Response & msg)
{
  return odin_ros_driver::srv::to_yaml(msg);
}

template<>
inline const char * data_type<odin_ros_driver::srv::GetAwb_Response>()
{
  return "odin_ros_driver::srv::GetAwb_Response";
}

template<>
inline const char * name<odin_ros_driver::srv::GetAwb_Response>()
{
  return "odin_ros_driver/srv/GetAwb_Response";
}

template<>
struct has_fixed_size<odin_ros_driver::srv::GetAwb_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<odin_ros_driver::srv::GetAwb_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<odin_ros_driver::srv::GetAwb_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<odin_ros_driver::srv::GetAwb>()
{
  return "odin_ros_driver::srv::GetAwb";
}

template<>
inline const char * name<odin_ros_driver::srv::GetAwb>()
{
  return "odin_ros_driver/srv/GetAwb";
}

template<>
struct has_fixed_size<odin_ros_driver::srv::GetAwb>
  : std::integral_constant<
    bool,
    has_fixed_size<odin_ros_driver::srv::GetAwb_Request>::value &&
    has_fixed_size<odin_ros_driver::srv::GetAwb_Response>::value
  >
{
};

template<>
struct has_bounded_size<odin_ros_driver::srv::GetAwb>
  : std::integral_constant<
    bool,
    has_bounded_size<odin_ros_driver::srv::GetAwb_Request>::value &&
    has_bounded_size<odin_ros_driver::srv::GetAwb_Response>::value
  >
{
};

template<>
struct is_service<odin_ros_driver::srv::GetAwb>
  : std::true_type
{
};

template<>
struct is_service_request<odin_ros_driver::srv::GetAwb_Request>
  : std::true_type
{
};

template<>
struct is_service_response<odin_ros_driver::srv::GetAwb_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__TRAITS_HPP_
