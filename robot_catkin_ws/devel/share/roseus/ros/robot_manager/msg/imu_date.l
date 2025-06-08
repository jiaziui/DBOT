;; Auto-generated. Do not edit!


(when (boundp 'robot_manager::imu_date)
  (if (not (find-package "ROBOT_MANAGER"))
    (make-package "ROBOT_MANAGER"))
  (shadow 'imu_date (find-package "ROBOT_MANAGER")))
(unless (find-package "ROBOT_MANAGER::IMU_DATE")
  (make-package "ROBOT_MANAGER::IMU_DATE"))

(in-package "ROS")
;;//! \htmlinclude imu_date.msg.html


(defclass robot_manager::imu_date
  :super ros::object
  :slots (_ax _ay _az _gx _gy _gz _yaw _pitch _roll ))

(defmethod robot_manager::imu_date
  (:init
   (&key
    ((:ax __ax) 0)
    ((:ay __ay) 0)
    ((:az __az) 0)
    ((:gx __gx) 0)
    ((:gy __gy) 0)
    ((:gz __gz) 0)
    ((:yaw __yaw) 0.0)
    ((:pitch __pitch) 0.0)
    ((:roll __roll) 0.0)
    )
   (send-super :init)
   (setq _ax (round __ax))
   (setq _ay (round __ay))
   (setq _az (round __az))
   (setq _gx (round __gx))
   (setq _gy (round __gy))
   (setq _gz (round __gz))
   (setq _yaw (float __yaw))
   (setq _pitch (float __pitch))
   (setq _roll (float __roll))
   self)
  (:ax
   (&optional __ax)
   (if __ax (setq _ax __ax)) _ax)
  (:ay
   (&optional __ay)
   (if __ay (setq _ay __ay)) _ay)
  (:az
   (&optional __az)
   (if __az (setq _az __az)) _az)
  (:gx
   (&optional __gx)
   (if __gx (setq _gx __gx)) _gx)
  (:gy
   (&optional __gy)
   (if __gy (setq _gy __gy)) _gy)
  (:gz
   (&optional __gz)
   (if __gz (setq _gz __gz)) _gz)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:pitch
   (&optional __pitch)
   (if __pitch (setq _pitch __pitch)) _pitch)
  (:roll
   (&optional __roll)
   (if __roll (setq _roll __roll)) _roll)
  (:serialization-length
   ()
   (+
    ;; int32 _ax
    4
    ;; int32 _ay
    4
    ;; int32 _az
    4
    ;; int32 _gx
    4
    ;; int32 _gy
    4
    ;; int32 _gz
    4
    ;; float32 _yaw
    4
    ;; float32 _pitch
    4
    ;; float32 _roll
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _ax
       (write-long _ax s)
     ;; int32 _ay
       (write-long _ay s)
     ;; int32 _az
       (write-long _az s)
     ;; int32 _gx
       (write-long _gx s)
     ;; int32 _gy
       (write-long _gy s)
     ;; int32 _gz
       (write-long _gz s)
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pitch
       (sys::poke _pitch (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _roll
       (sys::poke _roll (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _ax
     (setq _ax (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _ay
     (setq _ay (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _az
     (setq _az (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _gx
     (setq _gx (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _gy
     (setq _gy (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _gz
     (setq _gz (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pitch
     (setq _pitch (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _roll
     (setq _roll (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get robot_manager::imu_date :md5sum-) "576dcb682721d1959a6c3a178592e858")
(setf (get robot_manager::imu_date :datatype-) "robot_manager/imu_date")
(setf (get robot_manager::imu_date :definition-)
      "int32 ax
int32 ay
int32 az
int32 gx
int32 gy
int32 gz
float32 yaw
float32 pitch
float32 roll


")



(provide :robot_manager/imu_date "576dcb682721d1959a6c3a178592e858")


