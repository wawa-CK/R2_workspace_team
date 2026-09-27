// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from odin_ros_driver:srv/GetAwb.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__BUILDER_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "odin_ros_driver/srv/detail/get_awb__struct.hpp"
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
auto build<::odin_ros_driver::srv::GetAwb_Request>()
{
  return ::odin_ros_driver::srv::GetAwb_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace odin_ros_driver


namespace odin_ros_driver
{

namespace srv
{

namespace builder
{

class Init_GetAwb_Response_is_converged
{
public:
  explicit Init_GetAwb_Response_is_converged(::odin_ros_driver::srv::GetAwb_Response & msg)
  : msg_(msg)
  {}
  ::odin_ros_driver::srv::GetAwb_Response is_converged(::odin_ros_driver::srv::GetAwb_Response::_is_converged_type arg)
  {
    msg_.is_converged = std::move(arg);
    return std::move(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAwb_Response msg_;
};

class Init_GetAwb_Response_ccri
{
public:
  explicit Init_GetAwb_Response_ccri(::odin_ros_driver::srv::GetAwb_Response & msg)
  : msg_(msg)
  {}
  Init_GetAwb_Response_is_converged ccri(::odin_ros_driver::srv::GetAwb_Response::_ccri_type arg)
  {
    msg_.ccri = std::move(arg);
    return Init_GetAwb_Response_is_converged(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAwb_Response msg_;
};

class Init_GetAwb_Response_cct
{
public:
  explicit Init_GetAwb_Response_cct(::odin_ros_driver::srv::GetAwb_Response & msg)
  : msg_(msg)
  {}
  Init_GetAwb_Response_ccri cct(::odin_ros_driver::srv::GetAwb_Response::_cct_type arg)
  {
    msg_.cct = std::move(arg);
    return Init_GetAwb_Response_ccri(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAwb_Response msg_;
};

class Init_GetAwb_Response_bgain
{
public:
  explicit Init_GetAwb_Response_bgain(::odin_ros_driver::srv::GetAwb_Response & msg)
  : msg_(msg)
  {}
  Init_GetAwb_Response_cct bgain(::odin_ros_driver::srv::GetAwb_Response::_bgain_type arg)
  {
    msg_.bgain = std::move(arg);
    return Init_GetAwb_Response_cct(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAwb_Response msg_;
};

class Init_GetAwb_Response_gbgain
{
public:
  explicit Init_GetAwb_Response_gbgain(::odin_ros_driver::srv::GetAwb_Response & msg)
  : msg_(msg)
  {}
  Init_GetAwb_Response_bgain gbgain(::odin_ros_driver::srv::GetAwb_Response::_gbgain_type arg)
  {
    msg_.gbgain = std::move(arg);
    return Init_GetAwb_Response_bgain(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAwb_Response msg_;
};

class Init_GetAwb_Response_grgain
{
public:
  explicit Init_GetAwb_Response_grgain(::odin_ros_driver::srv::GetAwb_Response & msg)
  : msg_(msg)
  {}
  Init_GetAwb_Response_gbgain grgain(::odin_ros_driver::srv::GetAwb_Response::_grgain_type arg)
  {
    msg_.grgain = std::move(arg);
    return Init_GetAwb_Response_gbgain(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAwb_Response msg_;
};

class Init_GetAwb_Response_rgain
{
public:
  explicit Init_GetAwb_Response_rgain(::odin_ros_driver::srv::GetAwb_Response & msg)
  : msg_(msg)
  {}
  Init_GetAwb_Response_grgain rgain(::odin_ros_driver::srv::GetAwb_Response::_rgain_type arg)
  {
    msg_.rgain = std::move(arg);
    return Init_GetAwb_Response_grgain(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAwb_Response msg_;
};

class Init_GetAwb_Response_rc
{
public:
  explicit Init_GetAwb_Response_rc(::odin_ros_driver::srv::GetAwb_Response & msg)
  : msg_(msg)
  {}
  Init_GetAwb_Response_rgain rc(::odin_ros_driver::srv::GetAwb_Response::_rc_type arg)
  {
    msg_.rc = std::move(arg);
    return Init_GetAwb_Response_rgain(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAwb_Response msg_;
};

class Init_GetAwb_Response_success
{
public:
  Init_GetAwb_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetAwb_Response_rc success(::odin_ros_driver::srv::GetAwb_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GetAwb_Response_rc(msg_);
  }

private:
  ::odin_ros_driver::srv::GetAwb_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::odin_ros_driver::srv::GetAwb_Response>()
{
  return odin_ros_driver::srv::builder::Init_GetAwb_Response_success();
}

}  // namespace odin_ros_driver

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__BUILDER_HPP_
