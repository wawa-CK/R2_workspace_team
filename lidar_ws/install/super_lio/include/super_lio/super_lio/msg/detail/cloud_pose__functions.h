// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from super_lio:msg/CloudPose.idl
// generated code does not contain a copyright notice

#ifndef SUPER_LIO__MSG__DETAIL__CLOUD_POSE__FUNCTIONS_H_
#define SUPER_LIO__MSG__DETAIL__CLOUD_POSE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "super_lio/msg/rosidl_generator_c__visibility_control.h"

#include "super_lio/msg/detail/cloud_pose__struct.h"

/// Initialize msg/CloudPose message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * super_lio__msg__CloudPose
 * )) before or use
 * super_lio__msg__CloudPose__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
bool
super_lio__msg__CloudPose__init(super_lio__msg__CloudPose * msg);

/// Finalize msg/CloudPose message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
void
super_lio__msg__CloudPose__fini(super_lio__msg__CloudPose * msg);

/// Create msg/CloudPose message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * super_lio__msg__CloudPose__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
super_lio__msg__CloudPose *
super_lio__msg__CloudPose__create();

/// Destroy msg/CloudPose message.
/**
 * It calls
 * super_lio__msg__CloudPose__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
void
super_lio__msg__CloudPose__destroy(super_lio__msg__CloudPose * msg);

/// Check for msg/CloudPose message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
bool
super_lio__msg__CloudPose__are_equal(const super_lio__msg__CloudPose * lhs, const super_lio__msg__CloudPose * rhs);

/// Copy a msg/CloudPose message.
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
super_lio__msg__CloudPose__copy(
  const super_lio__msg__CloudPose * input,
  super_lio__msg__CloudPose * output);

/// Initialize array of msg/CloudPose messages.
/**
 * It allocates the memory for the number of elements and calls
 * super_lio__msg__CloudPose__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
bool
super_lio__msg__CloudPose__Sequence__init(super_lio__msg__CloudPose__Sequence * array, size_t size);

/// Finalize array of msg/CloudPose messages.
/**
 * It calls
 * super_lio__msg__CloudPose__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
void
super_lio__msg__CloudPose__Sequence__fini(super_lio__msg__CloudPose__Sequence * array);

/// Create array of msg/CloudPose messages.
/**
 * It allocates the memory for the array and calls
 * super_lio__msg__CloudPose__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
super_lio__msg__CloudPose__Sequence *
super_lio__msg__CloudPose__Sequence__create(size_t size);

/// Destroy array of msg/CloudPose messages.
/**
 * It calls
 * super_lio__msg__CloudPose__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
void
super_lio__msg__CloudPose__Sequence__destroy(super_lio__msg__CloudPose__Sequence * array);

/// Check for msg/CloudPose message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_super_lio
bool
super_lio__msg__CloudPose__Sequence__are_equal(const super_lio__msg__CloudPose__Sequence * lhs, const super_lio__msg__CloudPose__Sequence * rhs);

/// Copy an array of msg/CloudPose messages.
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
super_lio__msg__CloudPose__Sequence__copy(
  const super_lio__msg__CloudPose__Sequence * input,
  super_lio__msg__CloudPose__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SUPER_LIO__MSG__DETAIL__CLOUD_POSE__FUNCTIONS_H_
