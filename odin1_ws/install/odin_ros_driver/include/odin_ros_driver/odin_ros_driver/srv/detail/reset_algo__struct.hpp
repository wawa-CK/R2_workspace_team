// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from odin_ros_driver:srv/ResetAlgo.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__RESET_ALGO__STRUCT_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__RESET_ALGO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__odin_ros_driver__srv__ResetAlgo_Request __attribute__((deprecated))
#else
# define DEPRECATED__odin_ros_driver__srv__ResetAlgo_Request __declspec(deprecated)
#endif

namespace odin_ros_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ResetAlgo_Request_
{
  using Type = ResetAlgo_Request_<ContainerAllocator>;

  explicit ResetAlgo_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0l;
    }
  }

  explicit ResetAlgo_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0l;
    }
  }

  // field types and members
  using _value_type =
    int32_t;
  _value_type value;

  // setters for named parameter idiom
  Type & set__value(
    const int32_t & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__odin_ros_driver__srv__ResetAlgo_Request
    std::shared_ptr<odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__odin_ros_driver__srv__ResetAlgo_Request
    std::shared_ptr<odin_ros_driver::srv::ResetAlgo_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ResetAlgo_Request_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const ResetAlgo_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ResetAlgo_Request_

// alias to use template instance with default allocator
using ResetAlgo_Request =
  odin_ros_driver::srv::ResetAlgo_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace odin_ros_driver


#ifndef _WIN32
# define DEPRECATED__odin_ros_driver__srv__ResetAlgo_Response __attribute__((deprecated))
#else
# define DEPRECATED__odin_ros_driver__srv__ResetAlgo_Response __declspec(deprecated)
#endif

namespace odin_ros_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ResetAlgo_Response_
{
  using Type = ResetAlgo_Response_<ContainerAllocator>;

  explicit ResetAlgo_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->rc = 0l;
    }
  }

  explicit ResetAlgo_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->rc = 0l;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _rc_type =
    int32_t;
  _rc_type rc;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__rc(
    const int32_t & _arg)
  {
    this->rc = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__odin_ros_driver__srv__ResetAlgo_Response
    std::shared_ptr<odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__odin_ros_driver__srv__ResetAlgo_Response
    std::shared_ptr<odin_ros_driver::srv::ResetAlgo_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ResetAlgo_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->rc != other.rc) {
      return false;
    }
    return true;
  }
  bool operator!=(const ResetAlgo_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ResetAlgo_Response_

// alias to use template instance with default allocator
using ResetAlgo_Response =
  odin_ros_driver::srv::ResetAlgo_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace odin_ros_driver

namespace odin_ros_driver
{

namespace srv
{

struct ResetAlgo
{
  using Request = odin_ros_driver::srv::ResetAlgo_Request;
  using Response = odin_ros_driver::srv::ResetAlgo_Response;
};

}  // namespace srv

}  // namespace odin_ros_driver

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__RESET_ALGO__STRUCT_HPP_
