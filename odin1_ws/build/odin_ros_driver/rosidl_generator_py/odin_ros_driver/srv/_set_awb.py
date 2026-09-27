# generated from rosidl_generator_py/resource/_idl.py.em
# with input from odin_ros_driver:srv/SetAwb.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SetAwb_Request(type):
    """Metaclass of message 'SetAwb_Request'."""

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
                'odin_ros_driver.srv.SetAwb_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_awb__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_awb__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_awb__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_awb__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_awb__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetAwb_Request(metaclass=Metaclass_SetAwb_Request):
    """Message class 'SetAwb_Request'."""

    __slots__ = [
        '_mode',
        '_rgain',
        '_bgain',
    ]

    _fields_and_field_types = {
        'mode': 'uint8',
        'rgain': 'float',
        'bgain': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.mode = kwargs.get('mode', int())
        self.rgain = kwargs.get('rgain', float())
        self.bgain = kwargs.get('bgain', float())

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
        if self.mode != other.mode:
            return False
        if self.rgain != other.rgain:
            return False
        if self.bgain != other.bgain:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def mode(self):
        """Message field 'mode'."""
        return self._mode

    @mode.setter
    def mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mode' field must be an unsigned integer in [0, 255]"
        self._mode = value

    @builtins.property
    def rgain(self):
        """Message field 'rgain'."""
        return self._rgain

    @rgain.setter
    def rgain(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'rgain' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'rgain' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._rgain = value

    @builtins.property
    def bgain(self):
        """Message field 'bgain'."""
        return self._bgain

    @bgain.setter
    def bgain(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bgain' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'bgain' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._bgain = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SetAwb_Response(type):
    """Metaclass of message 'SetAwb_Response'."""

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
                'odin_ros_driver.srv.SetAwb_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_awb__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_awb__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_awb__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_awb__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_awb__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetAwb_Response(metaclass=Metaclass_SetAwb_Response):
    """Message class 'SetAwb_Response'."""

    __slots__ = [
        '_success',
        '_rc',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'rc': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.rc = kwargs.get('rc', int())

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


class Metaclass_SetAwb(type):
    """Metaclass of service 'SetAwb'."""

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
                'odin_ros_driver.srv.SetAwb')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__set_awb

            from odin_ros_driver.srv import _set_awb
            if _set_awb.Metaclass_SetAwb_Request._TYPE_SUPPORT is None:
                _set_awb.Metaclass_SetAwb_Request.__import_type_support__()
            if _set_awb.Metaclass_SetAwb_Response._TYPE_SUPPORT is None:
                _set_awb.Metaclass_SetAwb_Response.__import_type_support__()


class SetAwb(metaclass=Metaclass_SetAwb):
    from odin_ros_driver.srv._set_awb import SetAwb_Request as Request
    from odin_ros_driver.srv._set_awb import SetAwb_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
