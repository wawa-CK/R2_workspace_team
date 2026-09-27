// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from super_lio:msg/CloudPose2.idl
// generated code does not contain a copyright notice
#include "super_lio/msg/detail/cloud_pose2__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `pose`
// Member `cloud_lidar`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
super_lio__msg__CloudPose2__init(super_lio__msg__CloudPose2 * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    super_lio__msg__CloudPose2__fini(msg);
    return false;
  }
  // pose
  if (!rosidl_runtime_c__float__Sequence__init(&msg->pose, 0)) {
    super_lio__msg__CloudPose2__fini(msg);
    return false;
  }
  // cloud_lidar
  if (!rosidl_runtime_c__float__Sequence__init(&msg->cloud_lidar, 0)) {
    super_lio__msg__CloudPose2__fini(msg);
    return false;
  }
  return true;
}

void
super_lio__msg__CloudPose2__fini(super_lio__msg__CloudPose2 * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // pose
  rosidl_runtime_c__float__Sequence__fini(&msg->pose);
  // cloud_lidar
  rosidl_runtime_c__float__Sequence__fini(&msg->cloud_lidar);
}

bool
super_lio__msg__CloudPose2__are_equal(const super_lio__msg__CloudPose2 * lhs, const super_lio__msg__CloudPose2 * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // pose
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  // cloud_lidar
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->cloud_lidar), &(rhs->cloud_lidar)))
  {
    return false;
  }
  return true;
}

bool
super_lio__msg__CloudPose2__copy(
  const super_lio__msg__CloudPose2 * input,
  super_lio__msg__CloudPose2 * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // pose
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  // cloud_lidar
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->cloud_lidar), &(output->cloud_lidar)))
  {
    return false;
  }
  return true;
}

super_lio__msg__CloudPose2 *
super_lio__msg__CloudPose2__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  super_lio__msg__CloudPose2 * msg = (super_lio__msg__CloudPose2 *)allocator.allocate(sizeof(super_lio__msg__CloudPose2), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(super_lio__msg__CloudPose2));
  bool success = super_lio__msg__CloudPose2__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
super_lio__msg__CloudPose2__destroy(super_lio__msg__CloudPose2 * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    super_lio__msg__CloudPose2__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
super_lio__msg__CloudPose2__Sequence__init(super_lio__msg__CloudPose2__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  super_lio__msg__CloudPose2 * data = NULL;

  if (size) {
    data = (super_lio__msg__CloudPose2 *)allocator.zero_allocate(size, sizeof(super_lio__msg__CloudPose2), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = super_lio__msg__CloudPose2__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        super_lio__msg__CloudPose2__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
super_lio__msg__CloudPose2__Sequence__fini(super_lio__msg__CloudPose2__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      super_lio__msg__CloudPose2__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

super_lio__msg__CloudPose2__Sequence *
super_lio__msg__CloudPose2__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  super_lio__msg__CloudPose2__Sequence * array = (super_lio__msg__CloudPose2__Sequence *)allocator.allocate(sizeof(super_lio__msg__CloudPose2__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = super_lio__msg__CloudPose2__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
super_lio__msg__CloudPose2__Sequence__destroy(super_lio__msg__CloudPose2__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    super_lio__msg__CloudPose2__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
super_lio__msg__CloudPose2__Sequence__are_equal(const super_lio__msg__CloudPose2__Sequence * lhs, const super_lio__msg__CloudPose2__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!super_lio__msg__CloudPose2__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
super_lio__msg__CloudPose2__Sequence__copy(
  const super_lio__msg__CloudPose2__Sequence * input,
  super_lio__msg__CloudPose2__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(super_lio__msg__CloudPose2);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    super_lio__msg__CloudPose2 * data =
      (super_lio__msg__CloudPose2 *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!super_lio__msg__CloudPose2__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          super_lio__msg__CloudPose2__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!super_lio__msg__CloudPose2__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
