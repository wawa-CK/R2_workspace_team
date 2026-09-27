// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from super_lio:msg/CloudPose.idl
// generated code does not contain a copyright notice

#ifndef SUPER_LIO__MSG__DETAIL__CLOUD_POSE__STRUCT_HPP_
#define SUPER_LIO__MSG__DETAIL__CLOUD_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.hpp"
// Member 'cloud'
#include "sensor_msgs/msg/detail/point_cloud2__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__super_lio__msg__CloudPose __attribute__((deprecated))
#else
# define DEPRECATED__super_lio__msg__CloudPose __declspec(deprecated)
#endif

namespace super_lio
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CloudPose_
{
  using Type = CloudPose_<ContainerAllocator>;

  explicit CloudPose_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_init),
    cloud(_init)
  {
    (void)_init;
  }

  explicit CloudPose_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_alloc, _init),
    cloud(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _pose_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _pose_type pose;
  using _cloud_type =
    sensor_msgs::msg::PointCloud2_<ContainerAllocator>;
  _cloud_type cloud;

  // setters for named parameter idiom
  Type & set__pose(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__cloud(
    const sensor_msgs::msg::PointCloud2_<ContainerAllocator> & _arg)
  {
    this->cloud = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    super_lio::msg::CloudPose_<ContainerAllocator> *;
  using ConstRawPtr =
    const super_lio::msg::CloudPose_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<super_lio::msg::CloudPose_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<super_lio::msg::CloudPose_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      super_lio::msg::CloudPose_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<super_lio::msg::CloudPose_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      super_lio::msg::CloudPose_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<super_lio::msg::CloudPose_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<super_lio::msg::CloudPose_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<super_lio::msg::CloudPose_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__super_lio__msg__CloudPose
    std::shared_ptr<super_lio::msg::CloudPose_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__super_lio__msg__CloudPose
    std::shared_ptr<super_lio::msg::CloudPose_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CloudPose_ & other) const
  {
    if (this->pose != other.pose) {
      return false;
    }
    if (this->cloud != other.cloud) {
      return false;
    }
    return true;
  }
  bool operator!=(const CloudPose_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CloudPose_

// alias to use template instance with default allocator
using CloudPose =
  super_lio::msg::CloudPose_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace super_lio

#endif  // SUPER_LIO__MSG__DETAIL__CLOUD_POSE__STRUCT_HPP_
