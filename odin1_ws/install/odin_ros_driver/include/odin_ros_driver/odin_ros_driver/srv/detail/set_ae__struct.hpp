// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from odin_ros_driver:srv/SetAe.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__SET_AE__STRUCT_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__SET_AE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__odin_ros_driver__srv__SetAe_Request __attribute__((deprecated))
#else
# define DEPRECATED__odin_ros_driver__srv__SetAe_Request __declspec(deprecated)
#endif

namespace odin_ros_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetAe_Request_
{
  using Type = SetAe_Request_<ContainerAllocator>;

  explicit SetAe_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->exposure_time = 0.0f;
      this->gain = 0.0f;
    }
  }

  explicit SetAe_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->exposure_time = 0.0f;
      this->gain = 0.0f;
    }
  }

  // field types and members
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _exposure_time_type =
    float;
  _exposure_time_type exposure_time;
  using _gain_type =
    float;
  _gain_type gain;

  // setters for named parameter idiom
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__exposure_time(
    const float & _arg)
  {
    this->exposure_time = _arg;
    return *this;
  }
  Type & set__gain(
    const float & _arg)
  {
    this->gain = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    odin_ros_driver::srv::SetAe_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const odin_ros_driver::srv::SetAe_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<odin_ros_driver::srv::SetAe_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<odin_ros_driver::srv::SetAe_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::SetAe_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::SetAe_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::SetAe_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::SetAe_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<odin_ros_driver::srv::SetAe_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<odin_ros_driver::srv::SetAe_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__odin_ros_driver__srv__SetAe_Request
    std::shared_ptr<odin_ros_driver::srv::SetAe_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__odin_ros_driver__srv__SetAe_Request
    std::shared_ptr<odin_ros_driver::srv::SetAe_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetAe_Request_ & other) const
  {
    if (this->mode != other.mode) {
      return false;
    }
    if (this->exposure_time != other.exposure_time) {
      return false;
    }
    if (this->gain != other.gain) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetAe_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetAe_Request_

// alias to use template instance with default allocator
using SetAe_Request =
  odin_ros_driver::srv::SetAe_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace odin_ros_driver


#ifndef _WIN32
# define DEPRECATED__odin_ros_driver__srv__SetAe_Response __attribute__((deprecated))
#else
# define DEPRECATED__odin_ros_driver__srv__SetAe_Response __declspec(deprecated)
#endif

namespace odin_ros_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetAe_Response_
{
  using Type = SetAe_Response_<ContainerAllocator>;

  explicit SetAe_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->rc = 0l;
    }
  }

  explicit SetAe_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    odin_ros_driver::srv::SetAe_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const odin_ros_driver::srv::SetAe_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<odin_ros_driver::srv::SetAe_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<odin_ros_driver::srv::SetAe_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::SetAe_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::SetAe_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::SetAe_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::SetAe_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<odin_ros_driver::srv::SetAe_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<odin_ros_driver::srv::SetAe_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__odin_ros_driver__srv__SetAe_Response
    std::shared_ptr<odin_ros_driver::srv::SetAe_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__odin_ros_driver__srv__SetAe_Response
    std::shared_ptr<odin_ros_driver::srv::SetAe_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetAe_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->rc != other.rc) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetAe_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetAe_Response_

// alias to use template instance with default allocator
using SetAe_Response =
  odin_ros_driver::srv::SetAe_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace odin_ros_driver

namespace odin_ros_driver
{

namespace srv
{

struct SetAe
{
  using Request = odin_ros_driver::srv::SetAe_Request;
  using Response = odin_ros_driver::srv::SetAe_Response;
};

}  // namespace srv

}  // namespace odin_ros_driver

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__SET_AE__STRUCT_HPP_
