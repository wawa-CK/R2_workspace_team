# generated from rosidl_generator_py/resource/_idl.py.em
# with input from odin_ros_driver:srv/GetAe.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetAe_Request(type):
    """Metaclass of message 'GetAe_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('odin_ros_driver')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'odin_ros_driver.srv.GetAe_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_ae__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_ae__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_ae__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_ae__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_ae__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetAe_Request(metaclass=Metaclass_GetAe_Request):
    """Message class 'GetAe_Request'."""

    __slots__ = [
    ]

    _fields_and_field_types = {
    }

    SLOT_TYPES = (
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# already imported above
# import rosidl_parser.definition


class Metaclass_GetAe_Response(type):
    """Metaclass of message 'GetAe_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('odin_ros_driver')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'odin_ros_driver.srv.GetAe_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_ae__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_ae__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_ae__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_ae__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_ae__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetAe_Response(metaclass=Metaclass_GetAe_Response):
    """Message class 'GetAe_Response'."""

    __slots__ = [
        '_success',
        '_rc',
        '_exposure_time',
        '_gain',
        '_iso',
        '_brightness',
        '_is_converged',
        '_env_lv',
        '_fps',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'rc': 'int32',
        'exposure_time': 'float',
        'gain': 'float',
        'iso': 'int32',
        'brightness': 'float',
        'is_converged': 'uint8',
        'env_lv': 'float',
        'fps': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.rc = kwargs.get('rc', int())
        self.exposure_time = kwargs.get('exposure_time', float())
        self.gain = kwargs.get('gain', float())
        self.iso = kwargs.get('iso', int())
        self.brightness = kwargs.get('brightness', float())
        self.is_converged = kwargs.get('is_converged', int())
        self.env_lv = kwargs.get('env_lv', float())
        self.fps = kwargs.get('fps', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.success != other.success:
            return False
        if self.rc != other.rc:
            return False
        if self.exposure_time != other.exposure_time:
            return False
        if self.gain != other.gain:
            return False
        if self.iso != other.iso:
            return False
        if self.brightness != other.brightness:
            return False
        if self.is_converged != other.is_converged:
            return False
        if self.env_lv != other.env_lv:
            return False
        if self.fps != other.fps:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

    @builtins.property
    def rc(self):
        """Message field 'rc'."""
        return self._rc

    @rc.setter
    def rc(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'rc' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'rc' field must be an integer in [-2147483648, 2147483647]"
        self._rc = value

    @builtins.property
    def exposure_time(self):
        """Message field 'exposure_time'."""
        return self._exposure_time

    @exposure_time.setter
    def exposure_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'exposure_time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'exposure_time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._exposure_time = value

    @builtins.property
    def gain(self):
        """Message field 'gain'."""
        return self._gain

    @gain.setter
    def gain(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'gain' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'gain' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._gain = value

    @builtins.property
    def iso(self):
        """Message field 'iso'."""
        return self._iso

    @iso.setter
    def iso(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'iso' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'iso' field must be an integer in [-2147483648, 2147483647]"
        self._iso = value

    @builtins.property
    def brightness(self):
        """Message field 'brightness'."""
        return self._brightness

    @brightness.setter
    def brightness(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'brightness' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'brightness' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._brightness = value

    @builtins.property
    def is_converged(self):
        """Message field 'is_converged'."""
        return self._is_converged

    @is_converged.setter
    def is_converged(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'is_converged' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'is_converged' field must be an unsigned integer in [0, 255]"
        self._is_converged = value

    @builtins.property
    def env_lv(self):
        """Message field 'env_lv'."""
        return self._env_lv

    @env_lv.setter
    def env_lv(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'env_lv' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'env_lv' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._env_lv = value

    @builtins.property
    def fps(self):
        """Message field 'fps'."""
        return self._fps

    @fps.setter
    def fps(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'fps' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'fps' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._fps = value


class Metaclass_GetAe(type):
    """Metaclass of service 'GetAe'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('odin_ros_driver')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'odin_ros_driver.srv.GetAe')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_ae

            from odin_ros_driver.srv import _get_ae
            if _get_ae.Metaclass_GetAe_Request._TYPE_SUPPORT is None:
                _get_ae.Metaclass_GetAe_Request.__import_type_support__()
            if _get_ae.Metaclass_GetAe_Response._TYPE_SUPPORT is None:
                _get_ae.Metaclass_GetAe_Response.__import_type_support__()


class GetAe(metaclass=Metaclass_GetAe):
    from odin_ros_driver.srv._get_ae import GetAe_Request as Request
    from odin_ros_driver.srv._get_ae import GetAe_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
