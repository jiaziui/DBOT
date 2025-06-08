; Auto-generated. Do not edit!


(cl:in-package robot_manager-msg)


;//! \htmlinclude robot_control.msg.html

(cl:defclass <robot_control> (roslisp-msg-protocol:ros-message)
  ((robot_control_date
    :reader robot_control_date
    :initarg :robot_control_date
    :type cl:integer
    :initform 0)
   (robot_speed
    :reader robot_speed
    :initarg :robot_speed
    :type cl:integer
    :initform 0))
)

(cl:defclass robot_control (<robot_control>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <robot_control>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'robot_control)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_manager-msg:<robot_control> is deprecated: use robot_manager-msg:robot_control instead.")))

(cl:ensure-generic-function 'robot_control_date-val :lambda-list '(m))
(cl:defmethod robot_control_date-val ((m <robot_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_control_date-val is deprecated.  Use robot_manager-msg:robot_control_date instead.")
  (robot_control_date m))

(cl:ensure-generic-function 'robot_speed-val :lambda-list '(m))
(cl:defmethod robot_speed-val ((m <robot_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:robot_speed-val is deprecated.  Use robot_manager-msg:robot_speed instead.")
  (robot_speed m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <robot_control>) ostream)
  "Serializes a message object of type '<robot_control>"
  (cl:let* ((signed (cl:slot-value msg 'robot_control_date)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_speed)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <robot_control>) istream)
  "Deserializes a message object of type '<robot_control>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_control_date) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_speed) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<robot_control>)))
  "Returns string type for a message object of type '<robot_control>"
  "robot_manager/robot_control")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'robot_control)))
  "Returns string type for a message object of type 'robot_control"
  "robot_manager/robot_control")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<robot_control>)))
  "Returns md5sum for a message object of type '<robot_control>"
  "dfb01f34da152f6ce58d56cb22596b17")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'robot_control)))
  "Returns md5sum for a message object of type 'robot_control"
  "dfb01f34da152f6ce58d56cb22596b17")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<robot_control>)))
  "Returns full string definition for message of type '<robot_control>"
  (cl:format cl:nil "int32 robot_control_date~%int32 robot_speed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'robot_control)))
  "Returns full string definition for message of type 'robot_control"
  (cl:format cl:nil "int32 robot_control_date~%int32 robot_speed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <robot_control>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <robot_control>))
  "Converts a ROS message object to a list"
  (cl:list 'robot_control
    (cl:cons ':robot_control_date (robot_control_date msg))
    (cl:cons ':robot_speed (robot_speed msg))
))
