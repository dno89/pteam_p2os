; Auto-generated. Do not edit!


(cl:in-package pteam_p2os-msg)


;//! \htmlinclude ProcessedLS.msg.html

(cl:defclass <ProcessedLS> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (data
    :reader data
    :initarg :data
    :type sensor_msgs-msg:LaserScan
    :initform (cl:make-instance 'sensor_msgs-msg:LaserScan)))
)

(cl:defclass ProcessedLS (<ProcessedLS>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ProcessedLS>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ProcessedLS)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pteam_p2os-msg:<ProcessedLS> is deprecated: use pteam_p2os-msg:ProcessedLS instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <ProcessedLS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-msg:header-val is deprecated.  Use pteam_p2os-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <ProcessedLS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-msg:data-val is deprecated.  Use pteam_p2os-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ProcessedLS>) ostream)
  "Serializes a message object of type '<ProcessedLS>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'data) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ProcessedLS>) istream)
  "Deserializes a message object of type '<ProcessedLS>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'data) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ProcessedLS>)))
  "Returns string type for a message object of type '<ProcessedLS>"
  "pteam_p2os/ProcessedLS")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ProcessedLS)))
  "Returns string type for a message object of type 'ProcessedLS"
  "pteam_p2os/ProcessedLS")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ProcessedLS>)))
  "Returns md5sum for a message object of type '<ProcessedLS>"
  "2061fba751b50e7a91d1c4c774250599")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ProcessedLS)))
  "Returns md5sum for a message object of type 'ProcessedLS"
  "2061fba751b50e7a91d1c4c774250599")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ProcessedLS>)))
  "Returns full string definition for message of type '<ProcessedLS>"
  (cl:format cl:nil "Header header~%sensor_msgs/LaserScan data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/LaserScan~%# Single scan from a planar laser range-finder~%#~%# If you have another ranging device with different behavior (e.g. a sonar~%# array), please find or create a different message, since applications~%# will make fairly laser-specific assumptions about this data~%~%Header header            # timestamp in the header is the acquisition time of ~%                         # the first ray in the scan.~%                         #~%                         # in frame frame_id, angles are measured around ~%                         # the positive Z axis (counterclockwise, if Z is up)~%                         # with zero angle being forward along the x axis~%                         ~%float32 angle_min        # start angle of the scan [rad]~%float32 angle_max        # end angle of the scan [rad]~%float32 angle_increment  # angular distance between measurements [rad]~%~%float32 time_increment   # time between measurements [seconds] - if your scanner~%                         # is moving, this will be used in interpolating position~%                         # of 3d points~%float32 scan_time        # time between scans [seconds]~%~%float32 range_min        # minimum range value [m]~%float32 range_max        # maximum range value [m]~%~%float32[] ranges         # range data [m] (Note: values < range_min or > range_max should be discarded)~%float32[] intensities    # intensity data [device-specific units].  If your~%                         # device does not provide intensities, please leave~%                         # the array empty.~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ProcessedLS)))
  "Returns full string definition for message of type 'ProcessedLS"
  (cl:format cl:nil "Header header~%sensor_msgs/LaserScan data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/LaserScan~%# Single scan from a planar laser range-finder~%#~%# If you have another ranging device with different behavior (e.g. a sonar~%# array), please find or create a different message, since applications~%# will make fairly laser-specific assumptions about this data~%~%Header header            # timestamp in the header is the acquisition time of ~%                         # the first ray in the scan.~%                         #~%                         # in frame frame_id, angles are measured around ~%                         # the positive Z axis (counterclockwise, if Z is up)~%                         # with zero angle being forward along the x axis~%                         ~%float32 angle_min        # start angle of the scan [rad]~%float32 angle_max        # end angle of the scan [rad]~%float32 angle_increment  # angular distance between measurements [rad]~%~%float32 time_increment   # time between measurements [seconds] - if your scanner~%                         # is moving, this will be used in interpolating position~%                         # of 3d points~%float32 scan_time        # time between scans [seconds]~%~%float32 range_min        # minimum range value [m]~%float32 range_max        # maximum range value [m]~%~%float32[] ranges         # range data [m] (Note: values < range_min or > range_max should be discarded)~%float32[] intensities    # intensity data [device-specific units].  If your~%                         # device does not provide intensities, please leave~%                         # the array empty.~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ProcessedLS>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'data))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ProcessedLS>))
  "Converts a ROS message object to a list"
  (cl:list 'ProcessedLS
    (cl:cons ':header (header msg))
    (cl:cons ':data (data msg))
))
