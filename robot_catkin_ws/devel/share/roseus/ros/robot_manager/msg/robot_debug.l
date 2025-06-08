;; Auto-generated. Do not edit!


(when (boundp 'robot_manager::robot_debug)
  (if (not (find-package "ROBOT_MANAGER"))
    (make-package "ROBOT_MANAGER"))
  (shadow 'robot_debug (find-package "ROBOT_MANAGER")))
(unless (find-package "ROBOT_MANAGER::ROBOT_DEBUG")
  (make-package "ROBOT_MANAGER::ROBOT_DEBUG"))

(in-package "ROS")
;;//! \htmlinclude robot_debug.msg.html


(defclass robot_manager::robot_debug
  :super ros::object
  :slots (_servo_run_power _robot_landF _robot_landB _robot_fhMax _robot_swMax _robot_sport_state _robot_fwctUp _robot_control _robot_fwctEnd ))

(defmethod robot_manager::robot_debug
  (:init
   (&key
    ((:servo_run_power __servo_run_power) 0)
    ((:robot_landF __robot_landF) 0)
    ((:robot_landB __robot_landB) 0)
    ((:robot_fhMax __robot_fhMax) 0)
    ((:robot_swMax __robot_swMax) 0)
    ((:robot_sport_state __robot_sport_state) 0)
    ((:robot_fwctUp __robot_fwctUp) 0)
    ((:robot_control __robot_control) 0)
    ((:robot_fwctEnd __robot_fwctEnd) 0)
    )
   (send-super :init)
   (setq _servo_run_power (round __servo_run_power))
   (setq _robot_landF (round __robot_landF))
   (setq _robot_landB (round __robot_landB))
   (setq _robot_fhMax (round __robot_fhMax))
   (setq _robot_swMax (round __robot_swMax))
   (setq _robot_sport_state (round __robot_sport_state))
   (setq _robot_fwctUp (round __robot_fwctUp))
   (setq _robot_control (round __robot_control))
   (setq _robot_fwctEnd (round __robot_fwctEnd))
   self)
  (:servo_run_power
   (&optional __servo_run_power)
   (if __servo_run_power (setq _servo_run_power __servo_run_power)) _servo_run_power)
  (:robot_landF
   (&optional __robot_landF)
   (if __robot_landF (setq _robot_landF __robot_landF)) _robot_landF)
  (:robot_landB
   (&optional __robot_landB)
   (if __robot_landB (setq _robot_landB __robot_landB)) _robot_landB)
  (:robot_fhMax
   (&optional __robot_fhMax)
   (if __robot_fhMax (setq _robot_fhMax __robot_fhMax)) _robot_fhMax)
  (:robot_swMax
   (&optional __robot_swMax)
   (if __robot_swMax (setq _robot_swMax __robot_swMax)) _robot_swMax)
  (:robot_sport_state
   (&optional __robot_sport_state)
   (if __robot_sport_state (setq _robot_sport_state __robot_sport_state)) _robot_sport_state)
  (:robot_fwctUp
   (&optional __robot_fwctUp)
   (if __robot_fwctUp (setq _robot_fwctUp __robot_fwctUp)) _robot_fwctUp)
  (:robot_control
   (&optional __robot_control)
   (if __robot_control (setq _robot_control __robot_control)) _robot_control)
  (:robot_fwctEnd
   (&optional __robot_fwctEnd)
   (if __robot_fwctEnd (setq _robot_fwctEnd __robot_fwctEnd)) _robot_fwctEnd)
  (:serialization-length
   ()
   (+
    ;; int32 _servo_run_power
    4
    ;; int32 _robot_landF
    4
    ;; int32 _robot_landB
    4
    ;; int32 _robot_fhMax
    4
    ;; int32 _robot_swMax
    4
    ;; int32 _robot_sport_state
    4
    ;; int32 _robot_fwctUp
    4
    ;; int32 _robot_control
    4
    ;; int32 _robot_fwctEnd
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _servo_run_power
       (write-long _servo_run_power s)
     ;; int32 _robot_landF
       (write-long _robot_landF s)
     ;; int32 _robot_landB
       (write-long _robot_landB s)
     ;; int32 _robot_fhMax
       (write-long _robot_fhMax s)
     ;; int32 _robot_swMax
       (write-long _robot_swMax s)
     ;; int32 _robot_sport_state
       (write-long _robot_sport_state s)
     ;; int32 _robot_fwctUp
       (write-long _robot_fwctUp s)
     ;; int32 _robot_control
       (write-long _robot_control s)
     ;; int32 _robot_fwctEnd
       (write-long _robot_fwctEnd s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _servo_run_power
     (setq _servo_run_power (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _robot_landF
     (setq _robot_landF (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _robot_landB
     (setq _robot_landB (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _robot_fhMax
     (setq _robot_fhMax (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _robot_swMax
     (setq _robot_swMax (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _robot_sport_state
     (setq _robot_sport_state (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _robot_fwctUp
     (setq _robot_fwctUp (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _robot_control
     (setq _robot_control (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _robot_fwctEnd
     (setq _robot_fwctEnd (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get robot_manager::robot_debug :md5sum-) "2f2e39311972ce7b431a280d95b132fa")
(setf (get robot_manager::robot_debug :datatype-) "robot_manager/robot_debug")
(setf (get robot_manager::robot_debug :definition-)
      "int32 servo_run_power
int32 robot_landF
int32 robot_landB
int32 robot_fhMax
int32 robot_swMax
int32 robot_sport_state
int32 robot_fwctUp
int32 robot_control
int32 robot_fwctEnd

")



(provide :robot_manager/robot_debug "2f2e39311972ce7b431a280d95b132fa")


