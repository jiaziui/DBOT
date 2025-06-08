
(cl:in-package :asdf)

(defsystem "robot_manager-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "imu_date" :depends-on ("_package_imu_date"))
    (:file "_package_imu_date" :depends-on ("_package"))
    (:file "robot_control" :depends-on ("_package_robot_control"))
    (:file "_package_robot_control" :depends-on ("_package"))
    (:file "robot_debug" :depends-on ("_package_robot_debug"))
    (:file "_package_robot_debug" :depends-on ("_package"))
    (:file "robot_speaker" :depends-on ("_package_robot_speaker"))
    (:file "_package_robot_speaker" :depends-on ("_package"))
    (:file "robot_state" :depends-on ("_package_robot_state"))
    (:file "_package_robot_state" :depends-on ("_package"))
  ))