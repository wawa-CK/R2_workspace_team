// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from super_lio:msg/CloudPose.idl
// generated code does not contain a copyright notice
#include "super_lio/msg/detail/cloud_pose__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `pose`
#include "geometry_msgs/msg/detail/pose__functions.h"
// Member `cloud`
#include "sensor_msgs/msg/detail/point_cloud2__functions.h"

bool
super_lio__msg__CloudPose__init(super_lio__msg__CloudPose * msg)
{
  if (!msg) {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__init(&msg->pose)) {
    super_lio__msg__CloudPose__fini(msg);
    return false;
  }
  // cloud
  if (!sensor_msgs__msg__PointCloud2__init(&msg->cloud)) {
    super_lio__msg__CloudPose__fini(msg);
    return false;
  }
  return true;
}

void
super_lio__msg__CloudPose__fini(super_lio__msg__CloudPose * msg)
{
  if (!msg) {
    return;
  }
  // pose
  geometry_msgs__msg__Pose__fini(&msg->pose);
  // cloud
  sensor_msgs__msg__PointCloud2__fini(&msg->cloud);
}

bool
super_lio__msg__CloudPose__are_equal(const super_lio__msg__CloudPose * lhs, const super_lio__msg__CloudPose * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  // cloud
  if (!sensor_msgs__msg__PointCloud2__are_equal(
      &(lhs->cloud), &(rhs->cloud)))
  {
    return false;
  }
  return true;
}

bool
super_lio__msg__CloudPose__copy(
  const super_lio__msg__CloudPose * input,
  super_lio__msg__CloudPose * output)
{
  if (!input || !output) {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  // cloud
  if (!sensor_msgs__msg__PointCloud2__copy(
      &(input->cloud), &(output->cloud)))
  {
    return false;
  }
  return true;
}

super_lio__msg__CloudPose *
super_lio__msg__CloudPose__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  super_lio__msg__CloudPose * msg = (super_lio__msg__CloudPose *)allocator.allocate(sizeof(super_lio__msg__CloudPose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(super_lio__msg__CloudPose));
  bool success = super_lio__msg__CloudPose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
super_lio__msg__CloudPose__destroy(super_lio__msg__CloudPose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    super_lio__msg__CloudPose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
super_lio__msg__CloudPose__Sequence__init(super_lio__msg__CloudPose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  super_lio__msg__CloudPose * data = NULL;

  if (size) {
    data = (super_lio__msg__CloudPose *)allocator.zero_allocate(size, sizeof(super_lio__msg__CloudPose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = super_lio__msg__CloudPose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        super_lio__msg__CloudPose__fini(&data[i - 1]);
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
super_lio__msg__CloudPose__Sequence__fini(super_lio__msg__CloudPose__Sequence * array)
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
      super_lio__msg__CloudPose__fini(&array->data[i]);
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

super_lio__msg__CloudPose__Sequence *
super_lio__msg__CloudPose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  super_lio__msg__CloudPose__Sequence * array = (super_lio__msg__CloudPose__Sequence *)allocator.allocate(sizeof(super_lio__msg__CloudPose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = super_lio__msg__CloudPose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
super_lio__msg__CloudPose__Sequence__destroy(super_lio__msg__CloudPose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    super_lio__msg__CloudPose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
super_lio__msg__CloudPose__Sequence__are_equal(const super_lio__msg__CloudPose__Sequence * lhs, const super_lio__msg__CloudPose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!super_lio__msg__CloudPose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
super_lio__msg__CloudPose__Sequence__copy(
  const super_lio__msg__CloudPose__Sequence * input,
  super_lio__msg__CloudPose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(super_lio__msg__CloudPose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    super_lio__msg__CloudPose * data =
      (super_lio__msg__CloudPose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!super_lio__msg__CloudPose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          super_lio__msg__CloudPose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!super_lio__msg__CloudPose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
