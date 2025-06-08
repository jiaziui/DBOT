;; Auto-generated. Do not edit!


(when (boundp 'robot_manager::robot_state)
  (if (not (find-package "ROBOT_MANAGER"))
    (make-package "ROBOT_MANAGER"))
  (shadow 'robot_state (find-package "ROBOT_MANAGER")))
(unless (find-package "ROBOT_MANAGER::ROBOT_STATE")
  (make-package "ROBOT_MANAGER::ROBOT_STATE"))

(in-package "ROS")
;;//! \htmlinclude robot_state.msg.html


(defclass robot_manager::robot_state
  :super ros::object
  :slots (_robot_electricity _robot_state _robot_driver_state _robot_camera_state ))

(defmethod robot_manager::robot_state
  (:init
   (&key
    ((:robot_electricity __robot_electricity) 0.0)
    ((:robot_state __robot_state) 0)
    ((:robot_driver_state __robot_driver_state) 0)
    ((:robot_camera_state __robot_camera_state) 0)
    )
   (send-super :init)
   (setq _robot_electricity (float __robot_electricity))
   (setq _robot_state (round __robot_state))
   (setq _robot_driver_state (round __robot_driver_state))
   (setq _robot_camera_state (round __robot_camera_state))
   self)
  (:robot_electricity
   (&optional __robot_electricity)
   (if __robot_electricity (setq _robot_electricity __robot_electricity)) _robot_electricity)
  (:robot_state
   (&optional __robot_state)
   (if __robot_state (setq _robot_state __robot_state)) _robot_state)
  (:robot_driver_state
   (&optional __robot_driver_state)
   (if __robot_driver_state (setq _robot_driver_state __robot_driver_state)) _robot_driver_state)
  (:robot_camera_state
   (&optional __robot_camera_state)
   (if __robot_camera_state (setq _robot_camera_state __robot_camera_state)) _robot_camera_state)
  (:serialization-length
   ()
   (+
    ;; float32 _robot_electricity
    4
    ;; int32 _robot_state
    4
    ;; int32 _robot_driver_state
    4
    ;; int32 _robot_camera_state
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _robot_electricity
       (sys::poke _robot_electricity (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _robot_state
       (write-long _robot_state s)
     ;; int32 _robot_driver_state
       (write-long _robot_driver_state s)
     ;; int32 _robot_camera_state
       (write-long _robot_camera_state s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _robot_electricity
     (setq _robot_electricity (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _robot_state
     (setq _robot_state (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _robot_driver_state
     (setq _robot_driver_state (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _robot_camera_state
     (setq _robot_camera_state (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get robot_manager::robot_state :md5sum-) "5bad53ba22220257c1d7f0639451f8f3")
(setf (get robot_manager::robot_state :datatype-) "robot_manager/robot_state")
(setf (get robot_manager::robot_state :definition-)
      "float32 robot_electricity
int32 robot_state
int32 robot_driver_state
int32 robot_camera_state



")



(provide :robot_manager/robot_state "5bad53ba22220257c1d7f0639451f8f3")


