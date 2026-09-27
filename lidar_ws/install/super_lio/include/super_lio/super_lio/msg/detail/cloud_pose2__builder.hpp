// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from super_lio:msg/CloudPose2.idl
// generated code does not contain a copyright notice

#ifndef SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__BUILDER_HPP_
#define SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "super_lio/msg/detail/cloud_pose2__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace super_lio
{

namespace msg
{

namespace builder
{

class Init_CloudPose2_cloud_lidar
{
public:
  explicit Init_CloudPose2_cloud_lidar(::super_lio::msg::CloudPose2 & msg)
  : msg_(msg)
  {}
  ::super_lio::msg::CloudPose2 cloud_lidar(::super_lio::msg::CloudPose2::_cloud_lidar_type arg)
  {
    msg_.cloud_lidar = std::move(arg);
    return std::move(msg_);
  }

private:
  ::super_lio::msg::CloudPose2 msg_;
};

class Init_CloudPose2_pose
{
public:
  explicit Init_CloudPose2_pose(::super_lio::msg::CloudPose2 & msg)
  : msg_(msg)
  {}
  Init_CloudPose2_cloud_lidar pose(::super_lio::msg::CloudPose2::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_CloudPose2_cloud_lidar(msg_);
  }

private:
  ::super_lio::msg::CloudPose2 msg_;
};

class Init_CloudPose2_header
{
public:
  Init_CloudPose2_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CloudPose2_pose header(::super_lio::msg::CloudPose2::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_CloudPose2_pose(msg_);
  }

private:
  ::super_lio::msg::CloudPose2 msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::super_lio::msg::CloudPose2>()
{
  return super_lio::msg::builder::Init_CloudPose2_header();
}

}  // namespace super_lio

#endif  // SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__BUILDER_HPP_
