// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from super_lio:msg/CloudPose.idl
// generated code does not contain a copyright notice

#ifndef SUPER_LIO__MSG__DETAIL__CLOUD_POSE__BUILDER_HPP_
#define SUPER_LIO__MSG__DETAIL__CLOUD_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "super_lio/msg/detail/cloud_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace super_lio
{

namespace msg
{

namespace builder
{

class Init_CloudPose_cloud
{
public:
  explicit Init_CloudPose_cloud(::super_lio::msg::CloudPose & msg)
  : msg_(msg)
  {}
  ::super_lio::msg::CloudPose cloud(::super_lio::msg::CloudPose::_cloud_type arg)
  {
    msg_.cloud = std::move(arg);
    return std::move(msg_);
  }

private:
  ::super_lio::msg::CloudPose msg_;
};

class Init_CloudPose_pose
{
public:
  Init_CloudPose_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CloudPose_cloud pose(::super_lio::msg::CloudPose::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_CloudPose_cloud(msg_);
  }

private:
  ::super_lio::msg::CloudPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::super_lio::msg::CloudPose>()
{
  return super_lio::msg::builder::Init_CloudPose_pose();
}

}  // namespace super_lio

#endif  // SUPER_LIO__MSG__DETAIL__CLOUD_POSE__BUILDER_HPP_
