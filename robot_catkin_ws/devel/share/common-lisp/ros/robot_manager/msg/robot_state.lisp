; Auto-generated. Do not edit!


(cl:in-package robot_manager-msg)


;//! \htmlinclude robot_state.msg.html

(cl:defclass <robot_state> (roslisp-msg-protocol:ros-message)
  ((robot_electricity
    :reader robot_electricity
    :initarg :robot_electricity
    :type cl:float
    :initform 0.0)
   (robot_state
    :reader robot_state
    :initarg :robot_state
    :type cl:integer
    :initform 0)
   (robot_driver_state
    :reader robot_driver_state
    :initarg :robot_driver_state
    :type cl:integer
    :initform 0)
   (robot_camera_state
    :reader robot_camera_state
    :initarg :robot_camera_state
    :type cl:integer
    :initform 0))
)

(cl:defclass robot_state (<robot_state>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <robot_state>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'robot_state)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_manager-msg:<robot_state> is deprecated: use robot_manager-msg:robot_state instead.")))

(cl:ensure-generic-function 'robot_electricity-val :lambda-list '(m))
(cl:defmethod robot_electricity-val ((m <robot_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_electricity-val is deprecated.  Use robot_manager-msg:robot_electricity instead.")
  (robot_electricity m))

(cl:ensure-generic-function 'robot_state-val :lambda-list '(m))
(cl:defmethod robot_state-val ((m <robot_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_state-val is deprecated.  Use robot_manager-msg:robot_state instead.")
  (robot_state m))

(cl:ensure-generic-function 'robot_driver_state-val :lambda-list '(m))
(cl:defmethod robot_driver_state-val ((m <robot_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_driver_state-val is deprecated.  Use robot_manager-msg:robot_driver_state instead.")
  (robot_driver_state m))

(cl:ensure-generic-function 'robot_camera_state-val :lambda-list '(m))
(cl:defmethod robot_camera_state-val ((m <robot_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_camera_state-val is deprecated.  Use robot_manager-msg:robot_camera_state instead.")
  (robot_camera_state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <robot_state>) ostream)
  "Serializes a message object of type '<robot_state>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'robot_electricity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'robot_state)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_driver_state)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_camera_state)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <robot_state>) istream)
  "Deserializes a message object of type '<robot_state>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'robot_electricity) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_state) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_driver_state) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_camera_state) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<robot_state>)))
  "Returns string type for a message object of type '<robot_state>"
  "robot_manager/robot_state")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'robot_state)))
  "Returns string type for a message object of type 'robot_state"
  "robot_manager/robot_state")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<robot_state>)))
  "Returns md5sum for a message object of type '<robot_state>"
  "5bad53ba22220257c1d7f0639451f8f3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'robot_state)))
  "Returns md5sum for a message object of type 'robot_state"
  "5bad53ba22220257c1d7f0639451f8f3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<robot_state>)))
  "Returns full string definition for message of type '<robot_state>"
  (cl:format cl:nil "float32 robot_electricity~%int32 robot_state~%int32 robot_driver_state~%int32 robot_camera_state~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'robot_state)))
  "Returns full string definition for message of type 'robot_state"
  (cl:format cl:nil "float32 robot_electricity~%int32 robot_state~%int32 robot_driver_state~%int32 robot_camera_state~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <robot_state>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <robot_state>))
  "Converts a ROS message object to a list"
  (cl:list 'robot_state
    (cl:cons ':robot_electricity (robot_electricity msg))
    (cl:cons ':robot_state (robot_state msg))
    (cl:cons ':robot_driver_state (robot_driver_state msg))
    (cl:cons ':robot_camera_state (robot_camera_state msg))
))
