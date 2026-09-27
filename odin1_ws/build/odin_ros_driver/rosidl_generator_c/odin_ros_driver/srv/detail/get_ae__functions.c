// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from odin_ros_driver:srv/GetAe.idl
// generated code does not contain a copyright notice
#include "odin_ros_driver/srv/detail/get_ae__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
odin_ros_driver__srv__GetAe_Request__init(odin_ros_driver__srv__GetAe_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
odin_ros_driver__srv__GetAe_Request__fini(odin_ros_driver__srv__GetAe_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
odin_ros_driver__srv__GetAe_Request__are_equal(const odin_ros_driver__srv__GetAe_Request * lhs, const odin_ros_driver__srv__GetAe_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
odin_ros_driver__srv__GetAe_Request__copy(
  const odin_ros_driver__srv__GetAe_Request * input,
  odin_ros_driver__srv__GetAe_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

odin_ros_driver__srv__GetAe_Request *
odin_ros_driver__srv__GetAe_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  odin_ros_driver__srv__GetAe_Request * msg = (odin_ros_driver__srv__GetAe_Request *)allocator.allocate(sizeof(odin_ros_driver__srv__GetAe_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(odin_ros_driver__srv__GetAe_Request));
  bool success = odin_ros_driver__srv__GetAe_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
odin_ros_driver__srv__GetAe_Request__destroy(odin_ros_driver__srv__GetAe_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    odin_ros_driver__srv__GetAe_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
odin_ros_driver__srv__GetAe_Request__Sequence__init(odin_ros_driver__srv__GetAe_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  odin_ros_driver__srv__GetAe_Request * data = NULL;

  if (size) {
    data = (odin_ros_driver__srv__GetAe_Request *)allocator.zero_allocate(size, sizeof(odin_ros_driver__srv__GetAe_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = odin_ros_driver__srv__GetAe_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        odin_ros_driver__srv__GetAe_Request__fini(&data[i - 1]);
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
odin_ros_driver__srv__GetAe_Request__Sequence__fini(odin_ros_driver__srv__GetAe_Request__Sequence * array)
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
      odin_ros_driver__srv__GetAe_Request__fini(&array->data[i]);
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

odin_ros_driver__srv__GetAe_Request__Sequence *
odin_ros_driver__srv__GetAe_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  odin_ros_driver__srv__GetAe_Request__Sequence * array = (odin_ros_driver__srv__GetAe_Request__Sequence *)allocator.allocate(sizeof(odin_ros_driver__srv__GetAe_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = odin_ros_driver__srv__GetAe_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
odin_ros_driver__srv__GetAe_Request__Sequence__destroy(odin_ros_driver__srv__GetAe_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    odin_ros_driver__srv__GetAe_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
odin_ros_driver__srv__GetAe_Request__Sequence__are_equal(const odin_ros_driver__srv__GetAe_Request__Sequence * lhs, const odin_ros_driver__srv__GetAe_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!odin_ros_driver__srv__GetAe_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
odin_ros_driver__srv__GetAe_Request__Sequence__copy(
  const odin_ros_driver__srv__GetAe_Request__Sequence * input,
  odin_ros_driver__srv__GetAe_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(odin_ros_driver__srv__GetAe_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    odin_ros_driver__srv__GetAe_Request * data =
      (odin_ros_driver__srv__GetAe_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!odin_ros_driver__srv__GetAe_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          odin_ros_driver__srv__GetAe_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!odin_ros_driver__srv__GetAe_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
odin_ros_driver__srv__GetAe_Response__init(odin_ros_driver__srv__GetAe_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // rc
  // exposure_time
  // gain
  // iso
  // brightness
  // is_converged
  // env_lv
  // fps
  return true;
}

void
odin_ros_driver__srv__GetAe_Response__fini(odin_ros_driver__srv__GetAe_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // rc
  // exposure_time
  // gain
  // iso
  // brightness
  // is_converged
  // env_lv
  // fps
}

bool
odin_ros_driver__srv__GetAe_Response__are_equal(const odin_ros_driver__srv__GetAe_Response * lhs, const odin_ros_driver__srv__GetAe_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // rc
  if (lhs->rc != rhs->rc) {
    return false;
  }
  // exposure_time
  if (lhs->exposure_time != rhs->exposure_time) {
    return false;
  }
  // gain
  if (lhs->gain != rhs->gain) {
    return false;
  }
  // iso
  if (lhs->iso != rhs->iso) {
    return false;
  }
  // brightness
  if (lhs->brightness != rhs->brightness) {
    return false;
  }
  // is_converged
  if (lhs->is_converged != rhs->is_converged) {
    return false;
  }
  // env_lv
  if (lhs->env_lv != rhs->env_lv) {
    return false;
  }
  // fps
  if (lhs->fps != rhs->fps) {
    return false;
  }
  return true;
}

bool
odin_ros_driver__srv__GetAe_Response__copy(
  const odin_ros_driver__srv__GetAe_Response * input,
  odin_ros_driver__srv__GetAe_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // rc
  output->rc = input->rc;
  // exposure_time
  output->exposure_time = input->exposure_time;
  // gain
  output->gain = input->gain;
  // iso
  output->iso = input->iso;
  // brightness
  output->brightness = input->brightness;
  // is_converged
  output->is_converged = input->is_converged;
  // env_lv
  output->env_lv = input->env_lv;
  // fps
  output->fps = input->fps;
  return true;
}

odin_ros_driver__srv__GetAe_Response *
odin_ros_driver__srv__GetAe_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  odin_ros_driver__srv__GetAe_Response * msg = (odin_ros_driver__srv__GetAe_Response *)allocator.allocate(sizeof(odin_ros_driver__srv__GetAe_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(odin_ros_driver__srv__GetAe_Response));
  bool success = odin_ros_driver__srv__GetAe_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
odin_ros_driver__srv__GetAe_Response__destroy(odin_ros_driver__srv__GetAe_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    odin_ros_driver__srv__GetAe_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
odin_ros_driver__srv__GetAe_Response__Sequence__init(odin_ros_driver__srv__GetAe_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  odin_ros_driver__srv__GetAe_Response * data = NULL;

  if (size) {
    data = (odin_ros_driver__srv__GetAe_Response *)allocator.zero_allocate(size, sizeof(odin_ros_driver__srv__GetAe_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = odin_ros_driver__srv__GetAe_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        odin_ros_driver__srv__GetAe_Response__fini(&data[i - 1]);
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
odin_ros_driver__srv__GetAe_Response__Sequence__fini(odin_ros_driver__srv__GetAe_Response__Sequence * array)
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
      odin_ros_driver__srv__GetAe_Response__fini(&array->data[i]);
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

odin_ros_driver__srv__GetAe_Response__Sequence *
odin_ros_driver__srv__GetAe_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  odin_ros_driver__srv__GetAe_Response__Sequence * array = (odin_ros_driver__srv__GetAe_Response__Sequence *)allocator.allocate(sizeof(odin_ros_driver__srv__GetAe_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = odin_ros_driver__srv__GetAe_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
odin_ros_driver__srv__GetAe_Response__Sequence__destroy(odin_ros_driver__srv__GetAe_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    odin_ros_driver__srv__GetAe_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
odin_ros_driver__srv__GetAe_Response__Sequence__are_equal(const odin_ros_driver__srv__GetAe_Response__Sequence * lhs, const odin_ros_driver__srv__GetAe_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!odin_ros_driver__srv__GetAe_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
odin_ros_driver__srv__GetAe_Response__Sequence__copy(
  const odin_ros_driver__srv__GetAe_Response__Sequence * input,
  odin_ros_driver__srv__GetAe_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(odin_ros_driver__srv__GetAe_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    odin_ros_driver__srv__GetAe_Response * data =
      (odin_ros_driver__srv__GetAe_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!odin_ros_driver__srv__GetAe_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          odin_ros_driver__srv__GetAe_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!odin_ros_driver__srv__GetAe_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
