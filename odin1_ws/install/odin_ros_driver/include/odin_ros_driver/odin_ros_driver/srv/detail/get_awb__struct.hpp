// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from odin_ros_driver:srv/GetAwb.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__STRUCT_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__odin_ros_driver__srv__GetAwb_Request __attribute__((deprecated))
#else
# define DEPRECATED__odin_ros_driver__srv__GetAwb_Request __declspec(deprecated)
#endif

namespace odin_ros_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetAwb_Request_
{
  using Type = GetAwb_Request_<ContainerAllocator>;

  explicit GetAwb_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit GetAwb_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__odin_ros_driver__srv__GetAwb_Request
    std::shared_ptr<odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__odin_ros_driver__srv__GetAwb_Request
    std::shared_ptr<odin_ros_driver::srv::GetAwb_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetAwb_Request_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetAwb_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetAwb_Request_

// alias to use template instance with default allocator
using GetAwb_Request =
  odin_ros_driver::srv::GetAwb_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace odin_ros_driver


#ifndef _WIN32
# define DEPRECATED__odin_ros_driver__srv__GetAwb_Response __attribute__((deprecated))
#else
# define DEPRECATED__odin_ros_driver__srv__GetAwb_Response __declspec(deprecated)
#endif

namespace odin_ros_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetAwb_Response_
{
  using Type = GetAwb_Response_<ContainerAllocator>;

  explicit GetAwb_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->rc = 0l;
      this->rgain = 0.0f;
      this->grgain = 0.0f;
      this->gbgain = 0.0f;
      this->bgain = 0.0f;
      this->cct = 0.0f;
      this->ccri = 0.0f;
      this->is_converged = 0;
    }
  }

  explicit GetAwb_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->rc = 0l;
      this->rgain = 0.0f;
      this->grgain = 0.0f;
      this->gbgain = 0.0f;
      this->bgain = 0.0f;
      this->cct = 0.0f;
      this->ccri = 0.0f;
      this->is_converged = 0;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _rc_type =
    int32_t;
  _rc_type rc;
  using _rgain_type =
    float;
  _rgain_type rgain;
  using _grgain_type =
    float;
  _grgain_type grgain;
  using _gbgain_type =
    float;
  _gbgain_type gbgain;
  using _bgain_type =
    float;
  _bgain_type bgain;
  using _cct_type =
    float;
  _cct_type cct;
  using _ccri_type =
    float;
  _ccri_type ccri;
  using _is_converged_type =
    uint8_t;
  _is_converged_type is_converged;

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
  Type & set__rgain(
    const float & _arg)
  {
    this->rgain = _arg;
    return *this;
  }
  Type & set__grgain(
    const float & _arg)
  {
    this->grgain = _arg;
    return *this;
  }
  Type & set__gbgain(
    const float & _arg)
  {
    this->gbgain = _arg;
    return *this;
  }
  Type & set__bgain(
    const float & _arg)
  {
    this->bgain = _arg;
    return *this;
  }
  Type & set__cct(
    const float & _arg)
  {
    this->cct = _arg;
    return *this;
  }
  Type & set__ccri(
    const float & _arg)
  {
    this->ccri = _arg;
    return *this;
  }
  Type & set__is_converged(
    const uint8_t & _arg)
  {
    this->is_converged = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__odin_ros_driver__srv__GetAwb_Response
    std::shared_ptr<odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__odin_ros_driver__srv__GetAwb_Response
    std::shared_ptr<odin_ros_driver::srv::GetAwb_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetAwb_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->rc != other.rc) {
      return false;
    }
    if (this->rgain != other.rgain) {
      return false;
    }
    if (this->grgain != other.grgain) {
      return false;
    }
    if (this->gbgain != other.gbgain) {
      return false;
    }
    if (this->bgain != other.bgain) {
      return false;
    }
    if (this->cct != other.cct) {
      return false;
    }
    if (this->ccri != other.ccri) {
      return false;
    }
    if (this->is_converged != other.is_converged) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetAwb_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetAwb_Response_

// alias to use template instance with default allocator
using GetAwb_Response =
  odin_ros_driver::srv::GetAwb_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace odin_ros_driver

namespace odin_ros_driver
{

namespace srv
{

struct GetAwb
{
  using Request = odin_ros_driver::srv::GetAwb_Request;
  using Response = odin_ros_driver::srv::GetAwb_Response;
};

}  // namespace srv

}  // namespace odin_ros_driver

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__STRUCT_HPP_
