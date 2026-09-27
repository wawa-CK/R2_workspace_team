// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from odin_ros_driver:srv/ResetAlgo.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__RESET_ALGO__BUILDER_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__RESET_ALGO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "odin_ros_driver/srv/detail/reset_algo__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace odin_ros_driver
{

namespace srv
{

namespace builder
{

class Init_ResetAlgo_Request_value
{
public:
  Init_ResetAlgo_Request_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::odin_ros_driver::srv::ResetAlgo_Request value(::odin_ros_driver::srv::ResetAlgo_Request::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::odin_ros_driver::srv::ResetAlgo_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::odin_ros_driver::srv::ResetAlgo_Request>()
{
  return odin_ros_driver::srv::builder::Init_ResetAlgo_Request_value();
}

}  // namespace odin_ros_driver


namespace odin_ros_driver
{

namespace srv
{

namespace builder
{

class Init_ResetAlgo_Response_rc
{
public:
  explicit Init_ResetAlgo_Response_rc(::odin_ros_driver::srv::ResetAlgo_Response & msg)
  : msg_(msg)
  {}
  ::odin_ros_driver::srv::ResetAlgo_Response rc(::odin_ros_driver::srv::ResetAlgo_Response::_rc_type arg)
  {
    msg_.rc = std::move(arg);
    return std::move(msg_);
  }

private:
  ::odin_ros_driver::srv::ResetAlgo_Response msg_;
};

class Init_ResetAlgo_Response_success
{
public:
  Init_ResetAlgo_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ResetAlgo_Response_rc success(::odin_ros_driver::srv::ResetAlgo_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ResetAlgo_Response_rc(msg_);
  }

private:
  ::odin_ros_driver::srv::ResetAlgo_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::odin_ros_driver::srv::ResetAlgo_Response>()
{
  return odin_ros_driver::srv::builder::Init_ResetAlgo_Response_success();
}

}  // namespace odin_ros_driver

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__RESET_ALGO__BUILDER_HPP_
