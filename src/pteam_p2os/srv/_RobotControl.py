"""autogenerated by genpy from pteam_p2os/RobotControlRequest.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class RobotControlRequest(genpy.Message):
  _md5sum = "9c51bfb4ee117f894f2c7dfa4bb16bb8"
  _type = "pteam_p2os/RobotControlRequest"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float32 affinity
float32 angular_speed
bool angular_speed_set
float32 linear_speed
bool linear_speed_set
bool gripper_move_down
bool gripper_move_set
string behavior_name

"""
  __slots__ = ['affinity','angular_speed','angular_speed_set','linear_speed','linear_speed_set','gripper_move_down','gripper_move_set','behavior_name']
  _slot_types = ['float32','float32','bool','float32','bool','bool','bool','string']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       affinity,angular_speed,angular_speed_set,linear_speed,linear_speed_set,gripper_move_down,gripper_move_set,behavior_name

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(RobotControlRequest, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.affinity is None:
        self.affinity = 0.
      if self.angular_speed is None:
        self.angular_speed = 0.
      if self.angular_speed_set is None:
        self.angular_speed_set = False
      if self.linear_speed is None:
        self.linear_speed = 0.
      if self.linear_speed_set is None:
        self.linear_speed_set = False
      if self.gripper_move_down is None:
        self.gripper_move_down = False
      if self.gripper_move_set is None:
        self.gripper_move_set = False
      if self.behavior_name is None:
        self.behavior_name = ''
    else:
      self.affinity = 0.
      self.angular_speed = 0.
      self.angular_speed_set = False
      self.linear_speed = 0.
      self.linear_speed_set = False
      self.gripper_move_down = False
      self.gripper_move_set = False
      self.behavior_name = ''

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_2fBf3B.pack(_x.affinity, _x.angular_speed, _x.angular_speed_set, _x.linear_speed, _x.linear_speed_set, _x.gripper_move_down, _x.gripper_move_set))
      _x = self.behavior_name
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 16
      (_x.affinity, _x.angular_speed, _x.angular_speed_set, _x.linear_speed, _x.linear_speed_set, _x.gripper_move_down, _x.gripper_move_set,) = _struct_2fBf3B.unpack(str[start:end])
      self.angular_speed_set = bool(self.angular_speed_set)
      self.linear_speed_set = bool(self.linear_speed_set)
      self.gripper_move_down = bool(self.gripper_move_down)
      self.gripper_move_set = bool(self.gripper_move_set)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.behavior_name = str[start:end].decode('utf-8')
      else:
        self.behavior_name = str[start:end]
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_2fBf3B.pack(_x.affinity, _x.angular_speed, _x.angular_speed_set, _x.linear_speed, _x.linear_speed_set, _x.gripper_move_down, _x.gripper_move_set))
      _x = self.behavior_name
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 16
      (_x.affinity, _x.angular_speed, _x.angular_speed_set, _x.linear_speed, _x.linear_speed_set, _x.gripper_move_down, _x.gripper_move_set,) = _struct_2fBf3B.unpack(str[start:end])
      self.angular_speed_set = bool(self.angular_speed_set)
      self.linear_speed_set = bool(self.linear_speed_set)
      self.gripper_move_down = bool(self.gripper_move_down)
      self.gripper_move_set = bool(self.gripper_move_set)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.behavior_name = str[start:end].decode('utf-8')
      else:
        self.behavior_name = str[start:end]
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_2fBf3B = struct.Struct("<2fBf3B")
"""autogenerated by genpy from pteam_p2os/RobotControlResponse.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class RobotControlResponse(genpy.Message):
  _md5sum = "d41d8cd98f00b204e9800998ecf8427e"
  _type = "pteam_p2os/RobotControlResponse"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """

"""
  __slots__ = []
  _slot_types = []

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(RobotControlResponse, self).__init__(*args, **kwds)

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      pass
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      pass
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
class RobotControl(object):
  _type          = 'pteam_p2os/RobotControl'
  _md5sum = '9c51bfb4ee117f894f2c7dfa4bb16bb8'
  _request_class  = RobotControlRequest
  _response_class = RobotControlResponse
