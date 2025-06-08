; Auto-generated. Do not edit!


(cl:in-package robot_manager-msg)


;//! \htmlinclude robot_debug.msg.html

(cl:defclass <robot_debug> (roslisp-msg-protocol:ros-message)
  ((servo_run_power
    :reader servo_run_power
    :initarg :servo_run_power
    :type cl:integer
    :initform 0)
   (robot_landF
    :reader robot_landF
    :initarg :robot_landF
    :type cl:integer
    :initform 0)
   (robot_landB
    :reader robot_landB
    :initarg :robot_landB
    :type cl:integer
    :initform 0)
   (robot_fhMax
    :reader robot_fhMax
    :initarg :robot_fhMax
    :type cl:integer
    :initform 0)
   (robot_swMax
    :reader robot_swMax
    :initarg :robot_swMax
    :type cl:integer
    :initform 0)
   (robot_sport_state
    :reader robot_sport_state
    :initarg :robot_sport_state
    :type cl:integer
    :initform 0)
   (robot_fwctUp
    :reader robot_fwctUp
    :initarg :robot_fwctUp
    :type cl:integer
    :initform 0)
   (robot_control
    :reader robot_control
    :initarg :robot_control
    :type cl:integer
    :initform 0)
   (robot_fwctEnd
    :reader robot_fwctEnd
    :initarg :robot_fwctEnd
    :type cl:integer
    :initform 0))
)

(cl:defclass robot_debug (<robot_debug>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <robot_debug>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'robot_debug)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_manager-msg:<robot_debug> is deprecated: use robot_manager-msg:robot_debug instead.")))

(cl:ensure-generic-function 'servo_run_power-val :lambda-list '(m))
(cl:defmethod servo_run_power-val ((m <robot_debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:servo_run_power-val is deprecated.  Use robot_manager-msg:servo_run_power instead.")
  (servo_run_power m))

(cl:ensure-generic-function 'robot_landF-val :lambda-list '(m))
(cl:defmethod robot_landF-val ((m <robot_debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_landF-val is deprecated.  Use robot_manager-msg:robot_landF instead.")
  (robot_landF m))

(cl:ensure-generic-function 'robot_landB-val :lambda-list '(m))
(cl:defmethod robot_landB-val ((m <robot_debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_landB-val is deprecated.  Use robot_manager-msg:robot_landB instead.")
  (robot_landB m))

(cl:ensure-generic-function 'robot_fhMax-val :lambda-list '(m))
(cl:defmethod robot_fhMax-val ((m <robot_debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_fhMax-val is deprecated.  Use robot_manager-msg:robot_fhMax instead.")
  (robot_fhMax m))

(cl:ensure-generic-function 'robot_swMax-val :lambda-list '(m))
(cl:defmethod robot_swMax-val ((m <robot_debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_swMax-val is deprecated.  Use robot_manager-msg:robot_swMax instead.")
  (robot_swMax m))

(cl:ensure-generic-function 'robot_sport_state-val :lambda-list '(m))
(cl:defmethod robot_sport_state-val ((m <robot_debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_sport_state-val is deprecated.  Use robot_manager-msg:robot_sport_state instead.")
  (robot_sport_state m))

(cl:ensure-generic-function 'robot_fwctUp-val :lambda-list '(m))
(cl:defmethod robot_fwctUp-val ((m <robot_debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_fwctUp-val is deprecated.  Use robot_manager-msg:robot_fwctUp instead.")
  (robot_fwctUp m))

(cl:ensure-generic-function 'robot_control-val :lambda-list '(m))
(cl:defmethod robot_control-val ((m <robot_debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_control-val is deprecated.  Use robot_manager-msg:robot_control instead.")
  (robot_control m))

(cl:ensure-generic-function 'robot_fwctEnd-val :lambda-list '(m))
(cl:defmethod robot_fwctEnd-val ((m <robot_debug>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_fwctEnd-val is deprecated.  Use robot_manager-msg:robot_fwctEnd instead.")
  (robot_fwctEnd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <robot_debug>) ostream)
  "Serializes a message object of type '<robot_debug>"
  (cl:let* ((signed (cl:slot-value msg 'servo_run_power)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_landF)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_landB)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_fhMax)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_swMax)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_sport_state)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_fwctUp)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_control)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_fwctEnd)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <robot_debug>) istream)
  "Deserializes a message object of type '<robot_debug>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'servo_run_power) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_landF) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_landB) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_fhMax) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_swMax) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_sport_state) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_fwctUp) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_control) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_fwctEnd) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<robot_debug>)))
  "Returns string type for a message object of type '<robot_debug>"
  "robot_manager/robot_debug")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'robot_debug)))
  "Returns string type for a message object of type 'robot_debug"
  "robot_manager/robot_debug")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<robot_debug>)))
  "Returns md5sum for a message object of type '<robot_debug>"
  "2f2e39311972ce7b431a280d95b132fa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'robot_debug)))
  "Returns md5sum for a message object of type 'robot_debug"
  "2f2e39311972ce7b431a280d95b132fa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<robot_debug>)))
  "Returns full string definition for message of type '<robot_debug>"
  (cl:format cl:nil "int32 servo_run_power~%int32 robot_landF~%int32 robot_landB~%int32 robot_fhMax~%int32 robot_swMax~%int32 robot_sport_state~%int32 robot_fwctUp~%int32 robot_control~%int32 robot_fwctEnd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'robot_debug)))
  "Returns full string definition for message of type 'robot_debug"
  (cl:format cl:nil "int32 servo_run_power~%int32 robot_landF~%int32 robot_landB~%int32 robot_fhMax~%int32 robot_swMax~%int32 robot_sport_state~%int32 robot_fwctUp~%int32 robot_control~%int32 robot_fwctEnd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <robot_debug>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <robot_debug>))
  "Converts a ROS message object to a list"
  (cl:list 'robot_debug
    (cl:cons ':servo_run_power (servo_run_power msg))
    (cl:cons ':robot_landF (robot_landF msg))
    (cl:cons ':robot_landB (robot_landB msg))
    (cl:cons ':robot_fhMax (robot_fhMax msg))
    (cl:cons ':robot_swMax (robot_swMax msg))
    (cl:cons ':robot_sport_state (robot_sport_state msg))
    (cl:cons ':robot_fwctUp (robot_fwctUp msg))
    (cl:cons ':robot_control (robot_control msg))
    (cl:cons ':robot_fwctEnd (robot_fwctEnd msg))
))
