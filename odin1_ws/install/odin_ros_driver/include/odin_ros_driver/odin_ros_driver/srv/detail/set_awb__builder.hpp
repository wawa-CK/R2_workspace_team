// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from odin_ros_driver:srv/SetAwb.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__SET_AWB__BUILDER_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__SET_AWB__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "odin_ros_driver/srv/detail/set_awb__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace odin_ros_driver
{

namespace srv
{

namespace builder
{

class Init_SetAwb_Request_bgain
{
public:
  explicit Init_SetAwb_Request_bgain(::odin_ros_driver::srv::SetAwb_Request & msg)
  : msg_(msg)
  {}
  ::odin_ros_driver::srv::SetAwb_Request bgain(::odin_ros_driver::srv::SetAwb_Request::_bgain_type arg)
  {
    msg_.bgain = std::move(arg);
    return std::move(msg_);
  }

private:
  ::odin_ros_driver::srv::SetAwb_Request msg_;
};

class Init_SetAwb_Request_rgain
{
public:
  explicit Init_SetAwb_Request_rgain(::odin_ros_driver::srv::SetAwb_Request & msg)
  : msg_(msg)
  {}
  Init_SetAwb_Request_bgain rgain(::odin_ros_driver::srv::SetAwb_Request::_rgain_type arg)
  {
    msg_.rgain = std::move(arg);
    return Init_SetAwb_Request_bgain(msg_);
  }

private:
  ::odin_ros_driver::srv::SetAwb_Request msg_;
};

class Init_SetAwb_Request_mode
{
public:
  Init_SetAwb_Request_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetAwb_Request_rgain mode(::odin_ros_driver::srv::SetAwb_Request::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_SetAwb_Request_rgain(msg_);
  }

private:
  ::odin_ros_driver::srv::SetAwb_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::odin_ros_driver::srv::SetAwb_Request>()
{
  return odin_ros_driver::srv::builder::Init_SetAwb_Request_mode();
}

}  // namespace odin_ros_driver


namespace odin_ros_driver
{

namespace srv
{

namespace builder
{

class Init_SetAwb_Response_rc
{
public:
  explicit Init_SetAwb_Response_rc(::odin_ros_driver::srv::SetAwb_Response & msg)
  : msg_(msg)
  {}
  ::odin_ros_driver::srv::SetAwb_Response rc(::odin_ros_driver::srv::SetAwb_Response::_rc_type arg)
  {
    msg_.rc = std::move(arg);
    return std::move(msg_);
  }

private:
  ::odin_ros_driver::srv::SetAwb_Response msg_;
};

class Init_SetAwb_Response_success
{
public:
  Init_SetAwb_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetAwb_Response_rc success(::odin_ros_driver::srv::SetAwb_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetAwb_Response_rc(msg_);
  }

private:
  ::odin_ros_driver::srv::SetAwb_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::odin_ros_driver::srv::SetAwb_Response>()
{
  return odin_ros_driver::srv::builder::Init_SetAwb_Response_success();
}

}  // namespace odin_ros_driver

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__SET_AWB__BUILDER_HPP_
