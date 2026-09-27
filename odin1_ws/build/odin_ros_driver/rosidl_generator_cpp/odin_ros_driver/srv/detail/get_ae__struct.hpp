// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from odin_ros_driver:srv/GetAe.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__GET_AE__STRUCT_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__GET_AE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__odin_ros_driver__srv__GetAe_Request __attribute__((deprecated))
#else
# define DEPRECATED__odin_ros_driver__srv__GetAe_Request __declspec(deprecated)
#endif

namespace odin_ros_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetAe_Request_
{
  using Type = GetAe_Request_<ContainerAllocator>;

  explicit GetAe_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit GetAe_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    odin_ros_driver::srv::GetAe_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const odin_ros_driver::srv::GetAe_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetAe_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetAe_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetAe_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetAe_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetAe_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetAe_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetAe_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetAe_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__odin_ros_driver__srv__GetAe_Request
    std::shared_ptr<odin_ros_driver::srv::GetAe_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__odin_ros_driver__srv__GetAe_Request
    std::shared_ptr<odin_ros_driver::srv::GetAe_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetAe_Request_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetAe_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetAe_Request_

// alias to use template instance with default allocator
using GetAe_Request =
  odin_ros_driver::srv::GetAe_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace odin_ros_driver


#ifndef _WIN32
# define DEPRECATED__odin_ros_driver__srv__GetAe_Response __attribute__((deprecated))
#else
# define DEPRECATED__odin_ros_driver__srv__GetAe_Response __declspec(deprecated)
#endif

namespace odin_ros_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetAe_Response_
{
  using Type = GetAe_Response_<ContainerAllocator>;

  explicit GetAe_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->rc = 0l;
      this->exposure_time = 0.0f;
      this->gain = 0.0f;
      this->iso = 0l;
      this->brightness = 0.0f;
      this->is_converged = 0;
      this->env_lv = 0.0f;
      this->fps = 0.0f;
    }
  }

  explicit GetAe_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->rc = 0l;
      this->exposure_time = 0.0f;
      this->gain = 0.0f;
      this->iso = 0l;
      this->brightness = 0.0f;
      this->is_converged = 0;
      this->env_lv = 0.0f;
      this->fps = 0.0f;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _rc_type =
    int32_t;
  _rc_type rc;
  using _exposure_time_type =
    float;
  _exposure_time_type exposure_time;
  using _gain_type =
    float;
  _gain_type gain;
  using _iso_type =
    int32_t;
  _iso_type iso;
  using _brightness_type =
    float;
  _brightness_type brightness;
  using _is_converged_type =
    uint8_t;
  _is_converged_type is_converged;
  using _env_lv_type =
    float;
  _env_lv_type env_lv;
  using _fps_type =
    float;
  _fps_type fps;

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
  Type & set__iso(
    const int32_t & _arg)
  {
    this->iso = _arg;
    return *this;
  }
  Type & set__brightness(
    const float & _arg)
  {
    this->brightness = _arg;
    return *this;
  }
  Type & set__is_converged(
    const uint8_t & _arg)
  {
    this->is_converged = _arg;
    return *this;
  }
  Type & set__env_lv(
    const float & _arg)
  {
    this->env_lv = _arg;
    return *this;
  }
  Type & set__fps(
    const float & _arg)
  {
    this->fps = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    odin_ros_driver::srv::GetAe_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const odin_ros_driver::srv::GetAe_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetAe_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetAe_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetAe_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetAe_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetAe_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetAe_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetAe_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetAe_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__odin_ros_driver__srv__GetAe_Response
    std::shared_ptr<odin_ros_driver::srv::GetAe_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__odin_ros_driver__srv__GetAe_Response
    std::shared_ptr<odin_ros_driver::srv::GetAe_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetAe_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->rc != other.rc) {
      return false;
    }
    if (this->exposure_time != other.exposure_time) {
      return false;
    }
    if (this->gain != other.gain) {
      return false;
    }
    if (this->iso != other.iso) {
      return false;
    }
    if (this->brightness != other.brightness) {
      return false;
    }
    if (this->is_converged != other.is_converged) {
      return false;
    }
    if (this->env_lv != other.env_lv) {
      return false;
    }
    if (this->fps != other.fps) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetAe_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetAe_Response_

// alias to use template instance with default allocator
using GetAe_Response =
  odin_ros_driver::srv::GetAe_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace odin_ros_driver

namespace odin_ros_driver
{

namespace srv
{

struct GetAe
{
  using Request = odin_ros_driver::srv::GetAe_Request;
  using Response = odin_ros_driver::srv::GetAe_Response;
};

}  // namespace srv

}  // namespace odin_ros_driver

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__GET_AE__STRUCT_HPP_
