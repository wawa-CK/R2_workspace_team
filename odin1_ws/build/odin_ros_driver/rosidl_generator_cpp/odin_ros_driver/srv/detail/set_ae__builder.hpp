// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from odin_ros_driver:srv/SetAe.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__SET_AE__BUILDER_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__SET_AE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "odin_ros_driver/srv/detail/set_ae__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace odin_ros_driver
{

namespace srv
{

namespace builder
{

class Init_SetAe_Request_gain
{
public:
  explicit Init_SetAe_Request_gain(::odin_ros_driver::srv::SetAe_Request & msg)
  : msg_(msg)
  {}
  ::odin_ros_driver::srv::SetAe_Request gain(::odin_ros_driver::srv::SetAe_Request::_gain_type arg)
  {
    msg_.gain = std::move(arg);
    return std::move(msg_);
  }

private:
  ::odin_ros_driver::srv::SetAe_Request msg_;
};

class Init_SetAe_Request_exposure_time
{
public:
  explicit Init_SetAe_Request_exposure_time(::odin_ros_driver::srv::SetAe_Request & msg)
  : msg_(msg)
  {}
  Init_SetAe_Request_gain exposure_time(::odin_ros_driver::srv::SetAe_Request::_exposure_time_type arg)
  {
    msg_.exposure_time = std::move(arg);
    return Init_SetAe_Request_gain(msg_);
  }

private:
  ::odin_ros_driver::srv::SetAe_Request msg_;
};

class Init_SetAe_Request_mode
{
public:
  Init_SetAe_Request_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetAe_Request_exposure_time mode(::odin_ros_driver::srv::SetAe_Request::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_SetAe_Request_exposure_time(msg_);
  }

private:
  ::odin_ros_driver::srv::SetAe_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::odin_ros_driver::srv::SetAe_Request>()
{
  return odin_ros_driver::srv::builder::Init_SetAe_Request_mode();
}

}  // namespace odin_ros_driver


namespace odin_ros_driver
{

namespace srv
{

namespace builder
{

class Init_SetAe_Response_rc
{
public:
  explicit Init_SetAe_Response_rc(::odin_ros_driver::srv::SetAe_Response & msg)
  : msg_(msg)
  {}
  ::odin_ros_driver::srv::SetAe_Response rc(::odin_ros_driver::srv::SetAe_Response::_rc_type arg)
  {
    msg_.rc = std::move(arg);
    return std::move(msg_);
  }

private:
  ::odin_ros_driver::srv::SetAe_Response msg_;
};

class Init_SetAe_Response_success
{
public:
  Init_SetAe_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetAe_Response_rc success(::odin_ros_driver::srv::SetAe_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetAe_Response_rc(msg_);
  }

private:
  ::odin_ros_driver::srv::SetAe_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::odin_ros_driver::srv::SetAe_Response>()
{
  return odin_ros_driver::srv::builder::Init_SetAe_Response_success();
}

}  // namespace odin_ros_driver

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__SET_AE__BUILDER_HPP_
