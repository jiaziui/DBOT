#!/bin/bash


#!rosrun robot_key_control robot_key_control &
#!echo "robot_key_control!"

roscore

roslaunch ros_mpu6050_node mpu6050.launch & 
echo "robot_mpu6050_node!"





sleep 6


rosrun robot_machine_driver robot_machine_driver&
echo "robot_machine_driver start!"
