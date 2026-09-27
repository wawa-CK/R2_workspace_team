// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from odin_ros_driver:srv/GetAwb.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "odin_ros_driver/srv/detail/get_awb__struct.h"
#include "odin_ros_driver/srv/detail/get_awb__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool odin_ros_driver__srv__get_awb__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[44];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("odin_ros_driver.srv._get_awb.GetAwb_Request", full_classname_dest, 43) == 0);
  }
  odin_ros_driver__srv__GetAwb_Request * ros_message = _ros_message;
  ros_message->structure_needs_at_least_one_member = 0;

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * odin_ros_driver__srv__get_awb__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetAwb_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("odin_ros_driver.srv._get_awb");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetAwb_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  (void)raw_ros_message;

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
// already included above
// #include <Python.h>
// already included above
// #include <stdbool.h>
// already included above
// #include "numpy/ndarrayobject.h"
// already included above
// #include "rosidl_runtime_c/visibility_control.h"
// already included above
// #include "odin_ros_driver/srv/detail/get_awb__struct.h"
// already included above
// #include "odin_ros_driver/srv/detail/get_awb__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool odin_ros_driver__srv__get_awb__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[45];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("odin_ros_driver.srv._get_awb.GetAwb_Response", full_classname_dest, 44) == 0);
  }
  odin_ros_driver__srv__GetAwb_Response * ros_message = _ros_message;
  {  // success
    PyObject * field = PyObject_GetAttrString(_pymsg, "success");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->success = (Py_True == field);
    Py_DECREF(field);
  }
  {  // rc
    PyObject * field = PyObject_GetAttrString(_pymsg, "rc");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->rc = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // rgain
    PyObject * field = PyObject_GetAttrString(_pymsg, "rgain");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->rgain = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // grgain
    PyObject * field = PyObject_GetAttrString(_pymsg, "grgain");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->grgain = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // gbgain
    PyObject * field = PyObject_GetAttrString(_pymsg, "gbgain");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->gbgain = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // bgain
    PyObject * field = PyObject_GetAttrString(_pymsg, "bgain");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->bgain = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // cct
    PyObject * field = PyObject_GetAttrString(_pymsg, "cct");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->cct = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ccri
    PyObject * field = PyObject_GetAttrString(_pymsg, "ccri");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ccri = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // is_converged
    PyObject * field = PyObject_GetAttrString(_pymsg, "is_converged");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->is_converged = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * odin_ros_driver__srv__get_awb__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetAwb_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("odin_ros_driver.srv._get_awb");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetAwb_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  odin_ros_driver__srv__GetAwb_Response * ros_message = (odin_ros_driver__srv__GetAwb_Response *)raw_ros_message;
  {  // success
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->success ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "success", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rc
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->rc);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rc", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rgain
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->rgain);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rgain", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // grgain
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->grgain);
    {
      int rc = PyObject_SetAttrString(_pymessage, "grgain", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gbgain
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->gbgain);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gbgain", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bgain
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->bgain);
    {
      int rc = PyObject_SetAttrString(_pymessage, "bgain", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // cct
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->cct);
    {
      int rc = PyObject_SetAttrString(_pymessage, "cct", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ccri
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ccri);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ccri", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // is_converged
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->is_converged);
    {
      int rc = PyObject_SetAttrString(_pymessage, "is_converged", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
