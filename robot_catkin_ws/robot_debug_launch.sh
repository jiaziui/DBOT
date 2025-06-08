#robot_speaker启动

roslaunch robot_speak robot_speak.launch


#延时前启动
sleep 6
i2cdetect -y 1
i2cdetect -y 1
i2cdetect -y 1
#i2cdetect

#延时后启动
rosrun robot_i2c_driver robot_i2c_driver.py & 
echo "robot_i2c_driver!"

#robot_driver启动
rosrun robot_machine_driver robot_machine_driver&
echo "robot_machine_driver start!"
