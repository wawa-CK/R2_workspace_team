// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from odin_ros_driver:srv/GetAe.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__GET_AE__BUILDER_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__GET_AE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "odin_ros_driver/srv/detail/get_ae__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace odin_ros_driver
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::odin_ros_driver::srv::GetAe_Request>()
{
  return ::odin_ros_driver::srv::GetAe_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace odin_ros_driver


namespace odin_ros_driver
{

namespace srv
{

namespace builder
{

class Init_GetAe_Response_fps
{
public:
  explicit Init_GetAe_Response_fps(::odin_ros_driver::srv::GetAe_Response & msg)
  : msg_(msg)
  {}
  ::odin_ros_driver::srv::GetAe_Response fps(::odin_ros_driver::srv::GetAe_Response::_fps_type arg)
  {
    msg_.fps = std::move(arg);
    return std::move(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAe_Response msg_;
};

class Init_GetAe_Response_env_lv
{
public:
  explicit Init_GetAe_Response_env_lv(::odin_ros_driver::srv::GetAe_Response & msg)
  : msg_(msg)
  {}
  Init_GetAe_Response_fps env_lv(::odin_ros_driver::srv::GetAe_Response::_env_lv_type arg)
  {
    msg_.env_lv = std::move(arg);
    return Init_GetAe_Response_fps(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAe_Response msg_;
};

class Init_GetAe_Response_is_converged
{
public:
  explicit Init_GetAe_Response_is_converged(::odin_ros_driver::srv::GetAe_Response & msg)
  : msg_(msg)
  {}
  Init_GetAe_Response_env_lv is_converged(::odin_ros_driver::srv::GetAe_Response::_is_converged_type arg)
  {
    msg_.is_converged = std::move(arg);
    return Init_GetAe_Response_env_lv(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAe_Response msg_;
};

class Init_GetAe_Response_brightness
{
public:
  explicit Init_GetAe_Response_brightness(::odin_ros_driver::srv::GetAe_Response & msg)
  : msg_(msg)
  {}
  Init_GetAe_Response_is_converged brightness(::odin_ros_driver::srv::GetAe_Response::_brightness_type arg)
  {
    msg_.brightness = std::move(arg);
    return Init_GetAe_Response_is_converged(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAe_Response msg_;
};

class Init_GetAe_Response_iso
{
public:
  explicit Init_GetAe_Response_iso(::odin_ros_driver::srv::GetAe_Response & msg)
  : msg_(msg)
  {}
  Init_GetAe_Response_brightness iso(::odin_ros_driver::srv::GetAe_Response::_iso_type arg)
  {
    msg_.iso = std::move(arg);
    return Init_GetAe_Response_brightness(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAe_Response msg_;
};

class Init_GetAe_Response_gain
{
public:
  explicit Init_GetAe_Response_gain(::odin_ros_driver::srv::GetAe_Response & msg)
  : msg_(msg)
  {}
  Init_GetAe_Response_iso gain(::odin_ros_driver::srv::GetAe_Response::_gain_type arg)
  {
    msg_.gain = std::move(arg);
    return Init_GetAe_Response_iso(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAe_Response msg_;
};

class Init_GetAe_Response_exposure_time
{
public:
  explicit Init_GetAe_Response_exposure_time(::odin_ros_driver::srv::GetAe_Response & msg)
  : msg_(msg)
  {}
  Init_GetAe_Response_gain exposure_time(::odin_ros_driver::srv::GetAe_Response::_exposure_time_type arg)
  {
    msg_.exposure_time = std::move(arg);
    return Init_GetAe_Response_gain(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAe_Response msg_;
};

class Init_GetAe_Response_rc
{
public:
  explicit Init_GetAe_Response_rc(::odin_ros_driver::srv::GetAe_Response & msg)
  : msg_(msg)
  {}
  Init_GetAe_Response_exposure_time rc(::odin_ros_driver::srv::GetAe_Response::_rc_type arg)
  {
    msg_.rc = std::move(arg);
    return Init_GetAe_Response_exposure_time(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAe_Response msg_;
};

class Init_GetAe_Response_success
{
public:
  Init_GetAe_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetAe_Response_rc success(::odin_ros_driver::srv::GetAe_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GetAe_Response_rc(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAe_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::odin_ros_driver::srv::GetAe_Response>()
{
  return odin_ros_driver::srv::builder::Init_GetAe_Response_success();
}

}  // namespace odin_ros_driver

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__GET_AE__BUILDER_HPP_
