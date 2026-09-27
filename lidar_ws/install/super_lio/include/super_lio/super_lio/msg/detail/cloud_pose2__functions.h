// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from super_lio:msg/CloudPose2.idl
// generated code does not contain a copyright notice

#ifndef SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__FUNCTIONS_H_
#define SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "super_lio/msg/rosidl_generator_c__visibility_control.h"

#include "super_lio/msg/detail/cloud_pose2__struct.h"

/// Initialize msg/CloudPose2 message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * super_lio__msg__CloudPose2
 * )) before or use
 * super_lio__msg__CloudPose2__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
bool
super_lio__msg__CloudPose2__init(super_lio__msg__CloudPose2 * msg);

/// Finalize msg/CloudPose2 message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
void
super_lio__msg__CloudPose2__fini(super_lio__msg__CloudPose2 * msg);

/// Create msg/CloudPose2 message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * super_lio__msg__CloudPose2__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
super_lio__msg__CloudPose2 *
super_lio__msg__CloudPose2__create();

/// Destroy msg/CloudPose2 message.
/**
 * It calls
 * super_lio__msg__CloudPose2__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
void
super_lio__msg__CloudPose2__destroy(super_lio__msg__CloudPose2 * msg);

/// Check for msg/CloudPose2 message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
bool
super_lio__msg__CloudPose2__are_equal(const super_lio__msg__CloudPose2 * lhs, const super_lio__msg__CloudPose2 * rhs);

/// Copy a msg/CloudPose2 message.
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
ROSIDL_GENERATOR_C_PUBLIC_super_lio
bool
super_lio__msg__CloudPose2__copy(
  const super_lio__msg__CloudPose2 * input,
  super_lio__msg__CloudPose2 * output);

/// Initialize array of msg/CloudPose2 messages.
/**
 * It allocates the memory for the number of elements and calls
 * super_lio__msg__CloudPose2__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
bool
super_lio__msg__CloudPose2__Sequence__init(super_lio__msg__CloudPose2__Sequence * array, size_t size);

/// Finalize array of msg/CloudPose2 messages.
/**
 * It calls
 * super_lio__msg__CloudPose2__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
void
super_lio__msg__CloudPose2__Sequence__fini(super_lio__msg__CloudPose2__Sequence * array);

/// Create array of msg/CloudPose2 messages.
/**
 * It allocates the memory for the array and calls
 * super_lio__msg__CloudPose2__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
super_lio__msg__CloudPose2__Sequence *
super_lio__msg__CloudPose2__Sequence__create(size_t size);

/// Destroy array of msg/CloudPose2 messages.
/**
 * It calls
 * super_lio__msg__CloudPose2__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
void
super_lio__msg__CloudPose2__Sequence__destroy(super_lio__msg__CloudPose2__Sequence * array);

/// Check for msg/CloudPose2 message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
bool
super_lio__msg__CloudPose2__Sequence__are_equal(const super_lio__msg__CloudPose2__Sequence * lhs, const super_lio__msg__CloudPose2__Sequence * rhs);

/// Copy an array of msg/CloudPose2 messages.
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
ROSIDL_GENERATOR_C_PUBLIC_super_lio
bool
super_lio__msg__CloudPose2__Sequence__copy(
  const super_lio__msg__CloudPose2__Sequence * input,
  super_lio__msg__CloudPose2__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SUPER_LIO__MSG__DETAIL__CLOUD_POSE2__FUNCTIONS_H_
