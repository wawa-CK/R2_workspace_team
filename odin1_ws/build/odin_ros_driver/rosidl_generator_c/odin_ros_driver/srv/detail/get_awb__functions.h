// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from odin_ros_driver:srv/GetAwb.idl
// generated code does not contain a copyright notice

#ifndef ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__FUNCTIONS_H_
#define ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "odin_ros_driver/msg/rosidl_generator_c__visibility_control.h"

#include "odin_ros_driver/srv/detail/get_awb__struct.h"

/// Initialize srv/GetAwb message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * odin_ros_driver__srv__GetAwb_Request
 * )) before or use
 * odin_ros_driver__srv__GetAwb_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Request__init(odin_ros_driver__srv__GetAwb_Request * msg);

/// Finalize srv/GetAwb message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
void
odin_ros_driver__srv__GetAwb_Request__fini(odin_ros_driver__srv__GetAwb_Request * msg);

/// Create srv/GetAwb message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * odin_ros_driver__srv__GetAwb_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
odin_ros_driver__srv__GetAwb_Request *
odin_ros_driver__srv__GetAwb_Request__create();

/// Destroy srv/GetAwb message.
/**
 * It calls
 * odin_ros_driver__srv__GetAwb_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
void
odin_ros_driver__srv__GetAwb_Request__destroy(odin_ros_driver__srv__GetAwb_Request * msg);

/// Check for srv/GetAwb message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Request__are_equal(const odin_ros_driver__srv__GetAwb_Request * lhs, const odin_ros_driver__srv__GetAwb_Request * rhs);

/// Copy a srv/GetAwb message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Request__copy(
  const odin_ros_driver__srv__GetAwb_Request * input,
  odin_ros_driver__srv__GetAwb_Request * output);

/// Initialize array of srv/GetAwb messages.
/**
 * It allocates the memory for the number of elements and calls
 * odin_ros_driver__srv__GetAwb_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Request__Sequence__init(odin_ros_driver__srv__GetAwb_Request__Sequence * array, size_t size);

/// Finalize array of srv/GetAwb messages.
/**
 * It calls
 * odin_ros_driver__srv__GetAwb_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
void
odin_ros_driver__srv__GetAwb_Request__Sequence__fini(odin_ros_driver__srv__GetAwb_Request__Sequence * array);

/// Create array of srv/GetAwb messages.
/**
 * It allocates the memory for the array and calls
 * odin_ros_driver__srv__GetAwb_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
odin_ros_driver__srv__GetAwb_Request__Sequence *
odin_ros_driver__srv__GetAwb_Request__Sequence__create(size_t size);

/// Destroy array of srv/GetAwb messages.
/**
 * It calls
 * odin_ros_driver__srv__GetAwb_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
void
odin_ros_driver__srv__GetAwb_Request__Sequence__destroy(odin_ros_driver__srv__GetAwb_Request__Sequence * array);

/// Check for srv/GetAwb message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Request__Sequence__are_equal(const odin_ros_driver__srv__GetAwb_Request__Sequence * lhs, const odin_ros_driver__srv__GetAwb_Request__Sequence * rhs);

/// Copy an array of srv/GetAwb messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Request__Sequence__copy(
  const odin_ros_driver__srv__GetAwb_Request__Sequence * input,
  odin_ros_driver__srv__GetAwb_Request__Sequence * output);

/// Initialize srv/GetAwb message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * odin_ros_driver__srv__GetAwb_Response
 * )) before or use
 * odin_ros_driver__srv__GetAwb_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Response__init(odin_ros_driver__srv__GetAwb_Response * msg);

/// Finalize srv/GetAwb message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
void
odin_ros_driver__srv__GetAwb_Response__fini(odin_ros_driver__srv__GetAwb_Response * msg);

/// Create srv/GetAwb message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * odin_ros_driver__srv__GetAwb_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
odin_ros_driver__srv__GetAwb_Response *
odin_ros_driver__srv__GetAwb_Response__create();

/// Destroy srv/GetAwb message.
/**
 * It calls
 * odin_ros_driver__srv__GetAwb_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
void
odin_ros_driver__srv__GetAwb_Response__destroy(odin_ros_driver__srv__GetAwb_Response * msg);

/// Check for srv/GetAwb message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Response__are_equal(const odin_ros_driver__srv__GetAwb_Response * lhs, const odin_ros_driver__srv__GetAwb_Response * rhs);

/// Copy a srv/GetAwb message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Response__copy(
  const odin_ros_driver__srv__GetAwb_Response * input,
  odin_ros_driver__srv__GetAwb_Response * output);

/// Initialize array of srv/GetAwb messages.
/**
 * It allocates the memory for the number of elements and calls
 * odin_ros_driver__srv__GetAwb_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Response__Sequence__init(odin_ros_driver__srv__GetAwb_Response__Sequence * array, size_t size);

/// Finalize array of srv/GetAwb messages.
/**
 * It calls
 * odin_ros_driver__srv__GetAwb_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
void
odin_ros_driver__srv__GetAwb_Response__Sequence__fini(odin_ros_driver__srv__GetAwb_Response__Sequence * array);

/// Create array of srv/GetAwb messages.
/**
 * It allocates the memory for the array and calls
 * odin_ros_driver__srv__GetAwb_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
odin_ros_driver__srv__GetAwb_Response__Sequence *
odin_ros_driver__srv__GetAwb_Response__Sequence__create(size_t size);

/// Destroy array of srv/GetAwb messages.
/**
 * It calls
 * odin_ros_driver__srv__GetAwb_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
void
odin_ros_driver__srv__GetAwb_Response__Sequence__destroy(odin_ros_driver__srv__GetAwb_Response__Sequence * array);

/// Check for srv/GetAwb message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Response__Sequence__are_equal(const odin_ros_driver__srv__GetAwb_Response__Sequence * lhs, const odin_ros_driver__srv__GetAwb_Response__Sequence * rhs);

/// Copy an array of srv/GetAwb messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_odin_ros_driver
bool
odin_ros_driver__srv__GetAwb_Response__Sequence__copy(
  const odin_ros_driver__srv__GetAwb_Response__Sequence * input,
  odin_ros_driver__srv__GetAwb_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ODIN_ROS_DRIVER__SRV__DETAIL__GET_AWB__FUNCTIONS_H_
