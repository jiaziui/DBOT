;; Auto-generated. Do not edit!


(when (boundp 'robot_manager::robot_control)
  (if (not (find-package "ROBOT_MANAGER"))
    (make-package "ROBOT_MANAGER"))
  (shadow 'robot_control (find-package "ROBOT_MANAGER")))
(unless (find-package "ROBOT_MANAGER::ROBOT_CONTROL")
  (make-package "ROBOT_MANAGER::ROBOT_CONTROL"))

(in-package "ROS")
;;//! \htmlinclude robot_control.msg.html


(defclass robot_manager::robot_control
  :super ros::object
  :slots (_robot_control_date _robot_speed ))

(defmethod robot_manager::robot_control
  (:init
   (&key
    ((:robot_control_date __robot_control_date) 0)
    ((:robot_speed __robot_speed) 0)
    )
   (send-super :init)
   (setq _robot_control_date (round __robot_control_date))
   (setq _robot_speed (round __robot_speed))
   self)
  (:robot_control_date
   (&optional __robot_control_date)
   (if __robot_control_date (setq _robot_control_date __robot_control_date)) _robot_control_date)
  (:robot_speed
   (&optional __robot_speed)
   (if __robot_speed (setq _robot_speed __robot_speed)) _robot_speed)
  (:serialization-length
   ()
   (+
    ;; int32 _robot_control_date
    4
    ;; int32 _robot_speed
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _robot_control_date
       (write-long _robot_control_date s)
     ;; int32 _robot_speed
       (write-long _robot_speed s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _robot_control_date
     (setq _robot_control_date (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _robot_speed
     (setq _robot_speed (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get robot_manager::robot_control :md5sum-) "dfb01f34da152f6ce58d56cb22596b17")
(setf (get robot_manager::robot_control :datatype-) "robot_manager/robot_control")
(setf (get robot_manager::robot_control :definition-)
      "int32 robot_control_date
int32 robot_speed

")



(provide :robot_manager/robot_control "dfb01f34da152f6ce58d56cb22596b17")


