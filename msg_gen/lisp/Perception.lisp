; Auto-generated. Do not edit!


(cl:in-package pteam_p2os-msg)


;//! \htmlinclude Perception.msg.html

(cl:defclass <Perception> (roslisp-msg-protocol:ros-message)
  ((laser
    :reader laser
    :initarg :laser
    :type pteam_p2os-msg:ProcessedLS
    :initform (cl:make-instance 'pteam_p2os-msg:ProcessedLS))
   (odometry
    :reader odometry
    :initarg :odometry
    :type nav_msgs-msg:Odometry
    :initform (cl:make-instance 'nav_msgs-msg:Odometry)))
)

(cl:defclass Perception (<Perception>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Perception>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Perception)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pteam_p2os-msg:<Perception> is deprecated: use pteam_p2os-msg:Perception instead.")))

(cl:ensure-generic-function 'laser-val :lambda-list '(m))
(cl:defmethod laser-val ((m <Perception>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-msg:laser-val is deprecated.  Use pteam_p2os-msg:laser instead.")
  (laser m))

(cl:ensure-generic-function 'odometry-val :lambda-list '(m))
(cl:defmethod odometry-val ((m <Perception>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-msg:odometry-val is deprecated.  Use pteam_p2os-msg:odometry instead.")
  (odometry m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Perception>) ostream)
  "Serializes a message object of type '<Perception>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'laser) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'odometry) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Perception>) istream)
  "Deserializes a message object of type '<Perception>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'laser) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'odometry) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Perception>)))
  "Returns string type for a message object of type '<Perception>"
  "pteam_p2os/Perception")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Perception)))
  "Returns string type for a message object of type 'Perception"
  "pteam_p2os/Perception")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Perception>)))
  "Returns md5sum for a message object of type '<Perception>"
  "dd39913e347f9f33272c03167679aa77")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Perception)))
  "Returns md5sum for a message object of type 'Perception"
  "dd39913e347f9f33272c03167679aa77")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Perception>)))
  "Returns full string definition for message of type '<Perception>"
  (cl:format cl:nil "ProcessedLS laser~%nav_msgs/Odometry odometry~%~%================================================================================~%MSG: pteam_p2os/ProcessedLS~%Header header~%sensor_msgs/LaserScan data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/LaserScan~%# Single scan from a planar laser range-finder~%#~%# If you have another ranging device with different behavior (e.g. a sonar~%# array), please find or create a different message, since applications~%# will make fairly laser-specific assumptions about this data~%~%Header header            # timestamp in the header is the acquisition time of ~%                         # the first ray in the scan.~%                         #~%                         # in frame frame_id, angles are measured around ~%                         # the positive Z axis (counterclockwise, if Z is up)~%                         # with zero angle being forward along the x axis~%                         ~%float32 angle_min        # start angle of the scan [rad]~%float32 angle_max        # end angle of the scan [rad]~%float32 angle_increment  # angular distance between measurements [rad]~%~%float32 time_increment   # time between measurements [seconds] - if your scanner~%                         # is moving, this will be used in interpolating position~%                         # of 3d points~%float32 scan_time        # time between scans [seconds]~%~%float32 range_min        # minimum range value [m]~%float32 range_max        # maximum range value [m]~%~%float32[] ranges         # range data [m] (Note: values < range_min or > range_max should be discarded)~%float32[] intensities    # intensity data [device-specific units].  If your~%                         # device does not provide intensities, please leave~%                         # the array empty.~%~%================================================================================~%MSG: nav_msgs/Odometry~%# This represents an estimate of a position and velocity in free space.  ~%# The pose in this message should be specified in the coordinate frame given by header.frame_id.~%# The twist in this message should be specified in the coordinate frame given by the child_frame_id~%Header header~%string child_frame_id~%geometry_msgs/PoseWithCovariance pose~%geometry_msgs/TwistWithCovariance twist~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/TwistWithCovariance~%# This expresses velocity in free space with uncertianty.~%~%Twist twist~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into it's linear and angular parts. ~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Perception)))
  "Returns full string definition for message of type 'Perception"
  (cl:format cl:nil "ProcessedLS laser~%nav_msgs/Odometry odometry~%~%================================================================================~%MSG: pteam_p2os/ProcessedLS~%Header header~%sensor_msgs/LaserScan data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/LaserScan~%# Single scan from a planar laser range-finder~%#~%# If you have another ranging device with different behavior (e.g. a sonar~%# array), please find or create a different message, since applications~%# will make fairly laser-specific assumptions about this data~%~%Header header            # timestamp in the header is the acquisition time of ~%                         # the first ray in the scan.~%                         #~%                         # in frame frame_id, angles are measured around ~%                         # the positive Z axis (counterclockwise, if Z is up)~%                         # with zero angle being forward along the x axis~%                         ~%float32 angle_min        # start angle of the scan [rad]~%float32 angle_max        # end angle of the scan [rad]~%float32 angle_increment  # angular distance between measurements [rad]~%~%float32 time_increment   # time between measurements [seconds] - if your scanner~%                         # is moving, this will be used in interpolating position~%                         # of 3d points~%float32 scan_time        # time between scans [seconds]~%~%float32 range_min        # minimum range value [m]~%float32 range_max        # maximum range value [m]~%~%float32[] ranges         # range data [m] (Note: values < range_min or > range_max should be discarded)~%float32[] intensities    # intensity data [device-specific units].  If your~%                         # device does not provide intensities, please leave~%                         # the array empty.~%~%================================================================================~%MSG: nav_msgs/Odometry~%# This represents an estimate of a position and velocity in free space.  ~%# The pose in this message should be specified in the coordinate frame given by header.frame_id.~%# The twist in this message should be specified in the coordinate frame given by the child_frame_id~%Header header~%string child_frame_id~%geometry_msgs/PoseWithCovariance pose~%geometry_msgs/TwistWithCovariance twist~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/TwistWithCovariance~%# This expresses velocity in free space with uncertianty.~%~%Twist twist~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into it's linear and angular parts. ~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Perception>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'laser))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'odometry))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Perception>))
  "Converts a ROS message object to a list"
  (cl:list 'Perception
    (cl:cons ':laser (laser msg))
    (cl:cons ':odometry (odometry msg))
))
