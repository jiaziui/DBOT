; Auto-generated. Do not edit!


(cl:in-package robot_manager-msg)


;//! \htmlinclude robot_speaker.msg.html

(cl:defclass <robot_speaker> (roslisp-msg-protocol:ros-message)
  ((chinese_text
    :reader chinese_text
    :initarg :chinese_text
    :type cl:string
    :initform "")
   (msg_buffer_flag
    :reader msg_buffer_flag
    :initarg :msg_buffer_flag
    :type cl:integer
    :initform 0)
   (msg_clear_buffer_flag
    :reader msg_clear_buffer_flag
    :initarg :msg_clear_buffer_flag
    :type cl:integer
    :initform 0))
)

(cl:defclass robot_speaker (<robot_speaker>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <robot_speaker>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'robot_speaker)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_manager-msg:<robot_speaker> is deprecated: use robot_manager-msg:robot_speaker instead.")))

(cl:ensure-generic-function 'chinese_text-val :lambda-list '(m))
(cl:defmethod chinese_text-val ((m <robot_speaker>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:chinese_text-val is deprecated.  Use robot_manager-msg:chinese_text instead.")
  (chinese_text m))

(cl:ensure-generic-function 'msg_buffer_flag-val :lambda-list '(m))
(cl:defmethod msg_buffer_flag-val ((m <robot_speaker>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:msg_buffer_flag-val is deprecated.  Use robot_manager-msg:msg_buffer_flag instead.")
  (msg_buffer_flag m))

(cl:ensure-generic-function 'msg_clear_buffer_flag-val :lambda-list '(m))
(cl:defmethod msg_clear_buffer_flag-val ((m <robot_speaker>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_manager-msg:msg_clear_buffer_flag-val is deprecated.  Use robot_manager-msg:msg_clear_buffer_flag instead.")
  (msg_clear_buffer_flag m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <robot_speaker>) ostream)
  "Serializes a message object of type '<robot_speaker>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'chinese_text))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'chinese_text))
  (cl:let* ((signed (cl:slot-value msg 'msg_buffer_flag)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'msg_clear_buffer_flag)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <robot_speaker>) istream)
  "Deserializes a message object of type '<robot_speaker>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'chinese_text) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'chinese_text) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'msg_buffer_flag) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'msg_clear_buffer_flag) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<robot_speaker>)))
  "Returns string type for a message object of type '<robot_speaker>"
  "robot_manager/robot_speaker")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'robot_speaker)))
  "Returns string type for a message object of type 'robot_speaker"
  "robot_manager/robot_speaker")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<robot_speaker>)))
  "Returns md5sum for a message object of type '<robot_speaker>"
  "40c45f84b5c08c0a75df65acb133f8c5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'robot_speaker)))
  "Returns md5sum for a message object of type 'robot_speaker"
  "40c45f84b5c08c0a75df65acb133f8c5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<robot_speaker>)))
  "Returns full string definition for message of type '<robot_speaker>"
  (cl:format cl:nil "string chinese_text~%int32 msg_buffer_flag~%int32 msg_clear_buffer_flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'robot_speaker)))
  "Returns full string definition for message of type 'robot_speaker"
  (cl:format cl:nil "string chinese_text~%int32 msg_buffer_flag~%int32 msg_clear_buffer_flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <robot_speaker>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'chinese_text))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <robot_speaker>))
  "Converts a ROS message object to a list"
  (cl:list 'robot_speaker
    (cl:cons ':chinese_text (chinese_text msg))
    (cl:cons ':msg_buffer_flag (msg_buffer_flag msg))
    (cl:cons ':msg_clear_buffer_flag (msg_clear_buffer_flag msg))
))
