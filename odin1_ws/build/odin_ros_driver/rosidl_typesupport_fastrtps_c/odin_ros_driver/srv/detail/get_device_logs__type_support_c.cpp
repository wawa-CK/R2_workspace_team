// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from odin_ros_driver:srv/GetDeviceLogs.idl
// generated code does not contain a copyright notice
#include "odin_ros_driver/srv/detail/get_device_logs__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "odin_ros_driver/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "odin_ros_driver/srv/detail/get_device_logs__struct.h"
#include "odin_ros_driver/srv/detail/get_device_logs__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // dest_dir
#include "rosidl_runtime_c/string_functions.h"  // dest_dir

// forward declare type support functions


using _GetDeviceLogs_Request__ros_msg_type = odin_ros_driver__srv__GetDeviceLogs_Request;

static bool _GetDeviceLogs_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetDeviceLogs_Request__ros_msg_type * ros_message = static_cast<const _GetDeviceLogs_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: dest_dir
  {
    const rosidl_runtime_c__String * str = &ros_message->dest_dir;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _GetDeviceLogs_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetDeviceLogs_Request__ros_msg_type * ros_message = static_cast<_GetDeviceLogs_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: dest_dir
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->dest_dir.data) {
      rosidl_runtime_c__String__init(&ros_message->dest_dir);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->dest_dir,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'dest_dir'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_odin_ros_driver
size_t get_serialized_size_odin_ros_driver__srv__GetDeviceLogs_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetDeviceLogs_Request__ros_msg_type * ros_message = static_cast<const _GetDeviceLogs_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name dest_dir
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->dest_dir.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _GetDeviceLogs_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_odin_ros_driver__srv__GetDeviceLogs_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_odin_ros_driver
size_t max_serialized_size_odin_ros_driver__srv__GetDeviceLogs_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: dest_dir
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = odin_ros_driver__srv__GetDeviceLogs_Request;
    is_plain =
      (
      offsetof(DataType, dest_dir) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _GetDeviceLogs_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_odin_ros_driver__srv__GetDeviceLogs_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_GetDeviceLogs_Request = {
  "odin_ros_driver::srv",
  "GetDeviceLogs_Request",
  _GetDeviceLogs_Request__cdr_serialize,
  _GetDeviceLogs_Request__cdr_deserialize,
  _GetDeviceLogs_Request__get_serialized_size,
  _GetDeviceLogs_Request__max_serialized_size
};

static rosidl_message_type_support_t _GetDeviceLogs_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetDeviceLogs_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, odin_ros_driver, srv, GetDeviceLogs_Request)() {
  return &_GetDeviceLogs_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "odin_ros_driver/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "odin_ros_driver/srv/detail/get_device_logs__struct.h"
// already included above
// #include "odin_ros_driver/srv/detail/get_device_logs__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _GetDeviceLogs_Response__ros_msg_type = odin_ros_driver__srv__GetDeviceLogs_Response;

static bool _GetDeviceLogs_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetDeviceLogs_Response__ros_msg_type * ros_message = static_cast<const _GetDeviceLogs_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: success
  {
    cdr << (ros_message->success ? true : false);
  }

  // Field name: rc
  {
    cdr << ros_message->rc;
  }

  return true;
}

static bool _GetDeviceLogs_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetDeviceLogs_Response__ros_msg_type * ros_message = static_cast<_GetDeviceLogs_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: success
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->success = tmp ? true : false;
  }

  // Field name: rc
  {
    cdr >> ros_message->rc;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_odin_ros_driver
size_t get_serialized_size_odin_ros_driver__srv__GetDeviceLogs_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetDeviceLogs_Response__ros_msg_type * ros_message = static_cast<const _GetDeviceLogs_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name success
  {
    size_t item_size = sizeof(ros_message->success);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name rc
  {
    size_t item_size = sizeof(ros_message->rc);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _GetDeviceLogs_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_odin_ros_driver__srv__GetDeviceLogs_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_odin_ros_driver
size_t max_serialized_size_odin_ros_driver__srv__GetDeviceLogs_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: success
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: rc
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = odin_ros_driver__srv__GetDeviceLogs_Response;
    is_plain =
      (
      offsetof(DataType, rc) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _GetDeviceLogs_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_odin_ros_driver__srv__GetDeviceLogs_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_GetDeviceLogs_Response = {
  "odin_ros_driver::srv",
  "GetDeviceLogs_Response",
  _GetDeviceLogs_Response__cdr_serialize,
  _GetDeviceLogs_Response__cdr_deserialize,
  _GetDeviceLogs_Response__get_serialized_size,
  _GetDeviceLogs_Response__max_serialized_size
};

static rosidl_message_type_support_t _GetDeviceLogs_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetDeviceLogs_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, odin_ros_driver, srv, GetDeviceLogs_Response)() {
  return &_GetDeviceLogs_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "odin_ros_driver/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "odin_ros_driver/srv/get_device_logs.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t GetDeviceLogs__callbacks = {
  "odin_ros_driver::srv",
  "GetDeviceLogs",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, odin_ros_driver, srv, GetDeviceLogs_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, odin_ros_driver, srv, GetDeviceLogs_Response)(),
};

static rosidl_service_type_support_t GetDeviceLogs__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &GetDeviceLogs__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, odin_ros_driver, srv, GetDeviceLogs)() {
  return &GetDeviceLogs__handle;
}

#if defined(__cplusplus)
}
#endif
