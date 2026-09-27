// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from odin_ros_driver:srv/SaveMap.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "odin_ros_driver/srv/detail/save_map__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace odin_ros_driver
{

namespace srv
{

namespace builder
{

class Init_SaveMap_Request_value
{
public:
  Init_SaveMap_Request_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::odin_ros_driver::srv::SaveMap_Request value(::odin_ros_driver::srv::SaveMap_Request::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::odin_ros_driver::srv::SaveMap_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::odin_ros_driver::srv::SaveMap_Request>()
{
  return odin_ros_driver::srv::builder::Init_SaveMap_Request_value();
}

}  // namespace odin_ros_driver


namespace odin_ros_driver
{

namespace srv
{

namespace builder
{

class Init_SaveMap_Response_rc
{
public:
  explicit Init_SaveMap_Response_rc(::odin_ros_driver::srv::SaveMap_Response & msg)
  : msg_(msg)
  {}
  ::odin_ros_driver::srv::SaveMap_Response rc(::odin_ros_driver::srv::SaveMap_Response::_rc_type arg)
  {
    msg_.rc = std::move(arg);
    return std::move(msg_);
  }

private:
  ::odin_ros_driver::srv::SaveMap_Response msg_;
};

class Init_SaveMap_Response_success
{
public:
  Init_SaveMap_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SaveMap_Response_rc success(::odin_ros_driver::srv::SaveMap_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SaveMap_Response_rc(msg_);
  }

private:
  ::odin_ros_driver::srv::SaveMap_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::odin_ros_driver::srv::SaveMap_Response>()
{
  return odin_ros_driver::srv::builder::Init_SaveMap_Response_success();
}

}  // namespace odin_ros_driver

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_
