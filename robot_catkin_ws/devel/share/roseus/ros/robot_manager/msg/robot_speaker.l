;; Auto-generated. Do not edit!


(when (boundp 'robot_manager::robot_speaker)
  (if (not (find-package "ROBOT_MANAGER"))
    (make-package "ROBOT_MANAGER"))
  (shadow 'robot_speaker (find-package "ROBOT_MANAGER")))
(unless (find-package "ROBOT_MANAGER::ROBOT_SPEAKER")
  (make-package "ROBOT_MANAGER::ROBOT_SPEAKER"))

(in-package "ROS")
;;//! \htmlinclude robot_speaker.msg.html


(defclass robot_manager::robot_speaker
  :super ros::object
  :slots (_chinese_text _msg_buffer_flag _msg_clear_buffer_flag ))

(defmethod robot_manager::robot_speaker
  (:init
   (&key
    ((:chinese_text __chinese_text) "")
    ((:msg_buffer_flag __msg_buffer_flag) 0)
    ((:msg_clear_buffer_flag __msg_clear_buffer_flag) 0)
    )
   (send-super :init)
   (setq _chinese_text (string __chinese_text))
   (setq _msg_buffer_flag (round __msg_buffer_flag))
   (setq _msg_clear_buffer_flag (round __msg_clear_buffer_flag))
   self)
  (:chinese_text
   (&optional __chinese_text)
   (if __chinese_text (setq _chinese_text __chinese_text)) _chinese_text)
  (:msg_buffer_flag
   (&optional __msg_buffer_flag)
   (if __msg_buffer_flag (setq _msg_buffer_flag __msg_buffer_flag)) _msg_buffer_flag)
  (:msg_clear_buffer_flag
   (&optional __msg_clear_buffer_flag)
   (if __msg_clear_buffer_flag (setq _msg_clear_buffer_flag __msg_clear_buffer_flag)) _msg_clear_buffer_flag)
  (:serialization-length
   ()
   (+
    ;; string _chinese_text
    4 (length _chinese_text)
    ;; int32 _msg_buffer_flag
    4
    ;; int32 _msg_clear_buffer_flag
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _chinese_text
       (write-long (length _chinese_text) s) (princ _chinese_text s)
     ;; int32 _msg_buffer_flag
       (write-long _msg_buffer_flag s)
     ;; int32 _msg_clear_buffer_flag
       (write-long _msg_clear_buffer_flag s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _chinese_text
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _chinese_text (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _msg_buffer_flag
     (setq _msg_buffer_flag (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _msg_clear_buffer_flag
     (setq _msg_clear_buffer_flag (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get robot_manager::robot_speaker :md5sum-) "40c45f84b5c08c0a75df65acb133f8c5")
(setf (get robot_manager::robot_speaker :datatype-) "robot_manager/robot_speaker")
(setf (get robot_manager::robot_speaker :definition-)
      "string chinese_text
int32 msg_buffer_flag
int32 msg_clear_buffer_flag

")



(provide :robot_manager/robot_speaker "40c45f84b5c08c0a75df65acb133f8c5")


