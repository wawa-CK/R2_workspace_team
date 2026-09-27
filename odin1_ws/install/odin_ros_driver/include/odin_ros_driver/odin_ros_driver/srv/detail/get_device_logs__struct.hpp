// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from odin_ros_driver:srv/GetDeviceLogs.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__GET_DEVICE_LOGS__STRUCT_HPP_
#define ODIN_ROS_DRIVER__SRV__DETAIL__GET_DEVICE_LOGS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__odin_ros_driver__srv__GetDeviceLogs_Request __attribute__((deprecated))
#else
# define DEPRECATED__odin_ros_driver__srv__GetDeviceLogs_Request __declspec(deprecated)
#endif

namespace odin_ros_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetDeviceLogs_Request_
{
  using Type = GetDeviceLogs_Request_<ContainerAllocator>;

  explicit GetDeviceLogs_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->dest_dir = "";
    }
  }

  explicit GetDeviceLogs_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : dest_dir(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->dest_dir = "";
    }
  }

  // field types and members
  using _dest_dir_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _dest_dir_type dest_dir;

  // setters for named parameter idiom
  Type & set__dest_dir(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->dest_dir = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__odin_ros_driver__srv__GetDeviceLogs_Request
    std::shared_ptr<odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__odin_ros_driver__srv__GetDeviceLogs_Request
    std::shared_ptr<odin_ros_driver::srv::GetDeviceLogs_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetDeviceLogs_Request_ & other) const
  {
    if (this->dest_dir != other.dest_dir) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetDeviceLogs_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetDeviceLogs_Request_

// alias to use template instance with default allocator
using GetDeviceLogs_Request =
  odin_ros_driver::srv::GetDeviceLogs_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace odin_ros_driver


#ifndef _WIN32
# define DEPRECATED__odin_ros_driver__srv__GetDeviceLogs_Response __attribute__((deprecated))
#else
# define DEPRECATED__odin_ros_driver__srv__GetDeviceLogs_Response __declspec(deprecated)
#endif

namespace odin_ros_driver
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetDeviceLogs_Response_
{
  using Type = GetDeviceLogs_Response_<ContainerAllocator>;

  explicit GetDeviceLogs_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->rc = 0l;
    }
  }

  explicit GetDeviceLogs_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__odin_ros_driver__srv__GetDeviceLogs_Response
    std::shared_ptr<odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__odin_ros_driver__srv__GetDeviceLogs_Response
    std::shared_ptr<odin_ros_driver::srv::GetDeviceLogs_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetDeviceLogs_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->rc != other.rc) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetDeviceLogs_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetDeviceLogs_Response_

// alias to use template instance with default allocator
using GetDeviceLogs_Response =
  odin_ros_driver::srv::GetDeviceLogs_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace odin_ros_driver

namespace odin_ros_driver
{

namespace srv
{

struct GetDeviceLogs
{
  using Request = odin_ros_driver::srv::GetDeviceLogs_Request;
  using Response = odin_ros_driver::srv::GetDeviceLogs_Response;
};

}  // namespace srv

}  // namespace odin_ros_driver

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__GET_DEVICE_LOGS__STRUCT_HPP_
