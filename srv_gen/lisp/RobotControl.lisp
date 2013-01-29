; Auto-generated. Do not edit!


(cl:in-package pteam_p2os-srv)


;//! \htmlinclude RobotControl-request.msg.html

(cl:defclass <RobotControl-request> (roslisp-msg-protocol:ros-message)
  ((angular_speed
    :reader angular_speed
    :initarg :angular_speed
    :type cl:float
    :initform 0.0)
   (linear_speed
    :reader linear_speed
    :initarg :linear_speed
    :type cl:float
    :initform 0.0))
)

(cl:defclass RobotControl-request (<RobotControl-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RobotControl-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RobotControl-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pteam_p2os-srv:<RobotControl-request> is deprecated: use pteam_p2os-srv:RobotControl-request instead.")))

(cl:ensure-generic-function 'angular_speed-val :lambda-list '(m))
(cl:defmethod angular_speed-val ((m <RobotControl-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-srv:angular_speed-val is deprecated.  Use pteam_p2os-srv:angular_speed instead.")
  (angular_speed m))

(cl:ensure-generic-function 'linear_speed-val :lambda-list '(m))
(cl:defmethod linear_speed-val ((m <RobotControl-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-srv:linear_speed-val is deprecated.  Use pteam_p2os-srv:linear_speed instead.")
  (linear_speed m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RobotControl-request>) ostream)
  "Serializes a message object of type '<RobotControl-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angular_speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'linear_speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RobotControl-request>) istream)
  "Deserializes a message object of type '<RobotControl-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angular_speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'linear_speed) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RobotControl-request>)))
  "Returns string type for a service object of type '<RobotControl-request>"
  "pteam_p2os/RobotControlRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RobotControl-request)))
  "Returns string type for a service object of type 'RobotControl-request"
  "pteam_p2os/RobotControlRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RobotControl-request>)))
  "Returns md5sum for a message object of type '<RobotControl-request>"
  "2cc72ad6dc716a7d6153d5f2a1e7f7f3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RobotControl-request)))
  "Returns md5sum for a message object of type 'RobotControl-request"
  "2cc72ad6dc716a7d6153d5f2a1e7f7f3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RobotControl-request>)))
  "Returns full string definition for message of type '<RobotControl-request>"
  (cl:format cl:nil "float32 angular_speed~%float32 linear_speed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RobotControl-request)))
  "Returns full string definition for message of type 'RobotControl-request"
  (cl:format cl:nil "float32 angular_speed~%float32 linear_speed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RobotControl-request>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RobotControl-request>))
  "Converts a ROS message object to a list"
  (cl:list 'RobotControl-request
    (cl:cons ':angular_speed (angular_speed msg))
    (cl:cons ':linear_speed (linear_speed msg))
))
;//! \htmlinclude RobotControl-response.msg.html

(cl:defclass <RobotControl-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass RobotControl-response (<RobotControl-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RobotControl-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RobotControl-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pteam_p2os-srv:<RobotControl-response> is deprecated: use pteam_p2os-srv:RobotControl-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RobotControl-response>) ostream)
  "Serializes a message object of type '<RobotControl-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RobotControl-response>) istream)
  "Deserializes a message object of type '<RobotControl-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RobotControl-response>)))
  "Returns string type for a service object of type '<RobotControl-response>"
  "pteam_p2os/RobotControlResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RobotControl-response)))
  "Returns string type for a service object of type 'RobotControl-response"
  "pteam_p2os/RobotControlResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RobotControl-response>)))
  "Returns md5sum for a message object of type '<RobotControl-response>"
  "2cc72ad6dc716a7d6153d5f2a1e7f7f3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RobotControl-response)))
  "Returns md5sum for a message object of type 'RobotControl-response"
  "2cc72ad6dc716a7d6153d5f2a1e7f7f3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RobotControl-response>)))
  "Returns full string definition for message of type '<RobotControl-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RobotControl-response)))
  "Returns full string definition for message of type 'RobotControl-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RobotControl-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RobotControl-response>))
  "Converts a ROS message object to a list"
  (cl:list 'RobotControl-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'RobotControl)))
  'RobotControl-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'RobotControl)))
  'RobotControl-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RobotControl)))
  "Returns string type for a service object of type '<RobotControl>"
  "pteam_p2os/RobotControl")