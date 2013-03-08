; Auto-generated. Do not edit!


(cl:in-package pteam_p2os-srv)


;//! \htmlinclude RobotControl-request.msg.html

(cl:defclass <RobotControl-request> (roslisp-msg-protocol:ros-message)
  ((affinity
    :reader affinity
    :initarg :affinity
    :type cl:float
    :initform 0.0)
   (angular_speed
    :reader angular_speed
    :initarg :angular_speed
    :type cl:float
    :initform 0.0)
   (angular_speed_set
    :reader angular_speed_set
    :initarg :angular_speed_set
    :type cl:boolean
    :initform cl:nil)
   (linear_speed
    :reader linear_speed
    :initarg :linear_speed
    :type cl:float
    :initform 0.0)
   (linear_speed_set
    :reader linear_speed_set
    :initarg :linear_speed_set
    :type cl:boolean
    :initform cl:nil)
   (gripper_move_down
    :reader gripper_move_down
    :initarg :gripper_move_down
    :type cl:boolean
    :initform cl:nil)
   (gripper_move_set
    :reader gripper_move_set
    :initarg :gripper_move_set
    :type cl:boolean
    :initform cl:nil)
   (behavior_name
    :reader behavior_name
    :initarg :behavior_name
    :type cl:string
    :initform ""))
)

(cl:defclass RobotControl-request (<RobotControl-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RobotControl-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RobotControl-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pteam_p2os-srv:<RobotControl-request> is deprecated: use pteam_p2os-srv:RobotControl-request instead.")))

(cl:ensure-generic-function 'affinity-val :lambda-list '(m))
(cl:defmethod affinity-val ((m <RobotControl-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-srv:affinity-val is deprecated.  Use pteam_p2os-srv:affinity instead.")
  (affinity m))

(cl:ensure-generic-function 'angular_speed-val :lambda-list '(m))
(cl:defmethod angular_speed-val ((m <RobotControl-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-srv:angular_speed-val is deprecated.  Use pteam_p2os-srv:angular_speed instead.")
  (angular_speed m))

(cl:ensure-generic-function 'angular_speed_set-val :lambda-list '(m))
(cl:defmethod angular_speed_set-val ((m <RobotControl-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-srv:angular_speed_set-val is deprecated.  Use pteam_p2os-srv:angular_speed_set instead.")
  (angular_speed_set m))

(cl:ensure-generic-function 'linear_speed-val :lambda-list '(m))
(cl:defmethod linear_speed-val ((m <RobotControl-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-srv:linear_speed-val is deprecated.  Use pteam_p2os-srv:linear_speed instead.")
  (linear_speed m))

(cl:ensure-generic-function 'linear_speed_set-val :lambda-list '(m))
(cl:defmethod linear_speed_set-val ((m <RobotControl-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-srv:linear_speed_set-val is deprecated.  Use pteam_p2os-srv:linear_speed_set instead.")
  (linear_speed_set m))

(cl:ensure-generic-function 'gripper_move_down-val :lambda-list '(m))
(cl:defmethod gripper_move_down-val ((m <RobotControl-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-srv:gripper_move_down-val is deprecated.  Use pteam_p2os-srv:gripper_move_down instead.")
  (gripper_move_down m))

(cl:ensure-generic-function 'gripper_move_set-val :lambda-list '(m))
(cl:defmethod gripper_move_set-val ((m <RobotControl-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-srv:gripper_move_set-val is deprecated.  Use pteam_p2os-srv:gripper_move_set instead.")
  (gripper_move_set m))

(cl:ensure-generic-function 'behavior_name-val :lambda-list '(m))
(cl:defmethod behavior_name-val ((m <RobotControl-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pteam_p2os-srv:behavior_name-val is deprecated.  Use pteam_p2os-srv:behavior_name instead.")
  (behavior_name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RobotControl-request>) ostream)
  "Serializes a message object of type '<RobotControl-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'affinity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angular_speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'angular_speed_set) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'linear_speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'linear_speed_set) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'gripper_move_down) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'gripper_move_set) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'behavior_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'behavior_name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RobotControl-request>) istream)
  "Deserializes a message object of type '<RobotControl-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'affinity) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angular_speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'angular_speed_set) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'linear_speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'linear_speed_set) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'gripper_move_down) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'gripper_move_set) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'behavior_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'behavior_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
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
  "9c51bfb4ee117f894f2c7dfa4bb16bb8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RobotControl-request)))
  "Returns md5sum for a message object of type 'RobotControl-request"
  "9c51bfb4ee117f894f2c7dfa4bb16bb8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RobotControl-request>)))
  "Returns full string definition for message of type '<RobotControl-request>"
  (cl:format cl:nil "float32 affinity~%float32 angular_speed~%bool angular_speed_set~%float32 linear_speed~%bool linear_speed_set~%bool gripper_move_down~%bool gripper_move_set~%string behavior_name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RobotControl-request)))
  "Returns full string definition for message of type 'RobotControl-request"
  (cl:format cl:nil "float32 affinity~%float32 angular_speed~%bool angular_speed_set~%float32 linear_speed~%bool linear_speed_set~%bool gripper_move_down~%bool gripper_move_set~%string behavior_name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RobotControl-request>))
  (cl:+ 0
     4
     4
     1
     4
     1
     1
     1
     4 (cl:length (cl:slot-value msg 'behavior_name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RobotControl-request>))
  "Converts a ROS message object to a list"
  (cl:list 'RobotControl-request
    (cl:cons ':affinity (affinity msg))
    (cl:cons ':angular_speed (angular_speed msg))
    (cl:cons ':angular_speed_set (angular_speed_set msg))
    (cl:cons ':linear_speed (linear_speed msg))
    (cl:cons ':linear_speed_set (linear_speed_set msg))
    (cl:cons ':gripper_move_down (gripper_move_down msg))
    (cl:cons ':gripper_move_set (gripper_move_set msg))
    (cl:cons ':behavior_name (behavior_name msg))
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
  "9c51bfb4ee117f894f2c7dfa4bb16bb8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RobotControl-response)))
  "Returns md5sum for a message object of type 'RobotControl-response"
  "9c51bfb4ee117f894f2c7dfa4bb16bb8")
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