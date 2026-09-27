// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from super_lio:msg/CloudPose2.idl
// generated code does not contain a copyright notice

#ifndef SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__STRUCT_HPP_
#define SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__super_lio__msg__CloudPose2 __attribute__((deprecated))
#else
# define DEPRECATED__super_lio__msg__CloudPose2 __declspec(deprecated)
#endif

namespace super_lio
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CloudPose2_
{
  using Type = CloudPose2_<ContainerAllocator>;

  explicit CloudPose2_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit CloudPose2_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _pose_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _pose_type pose;
  using _cloud_lidar_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _cloud_lidar_type cloud_lidar;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__pose(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__cloud_lidar(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->cloud_lidar = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    super_lio::msg::CloudPose2_<ContainerAllocator> *;
  using ConstRawPtr =
    const super_lio::msg::CloudPose2_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<super_lio::msg::CloudPose2_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<super_lio::msg::CloudPose2_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      super_lio::msg::CloudPose2_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<super_lio::msg::CloudPose2_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      super_lio::msg::CloudPose2_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<super_lio::msg::CloudPose2_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<super_lio::msg::CloudPose2_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<super_lio::msg::CloudPose2_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__super_lio__msg__CloudPose2
    std::shared_ptr<super_lio::msg::CloudPose2_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__super_lio__msg__CloudPose2
    std::shared_ptr<super_lio::msg::CloudPose2_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CloudPose2_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    if (this->cloud_lidar != other.cloud_lidar) {
      return false;
    }
    return true;
  }
  bool operator!=(const CloudPose2_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CloudPose2_

// alias to use template instance with default allocator
using CloudPose2 =
  super_lio::msg::CloudPose2_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace super_lio

#endif  // SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__STRUCT_HPP_
