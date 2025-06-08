import sys
import rospy
import os
import rospkg
import time


rospack = rospkg.RosPack()
pkg_path = rospack.get_path('robot_i2c_driver')
lib_path = os.path.join(pkg_path, 'lib')
sys.path.append(lib_path)
from DFRobot_PAJ7620U2 import *
paj = DFRobot_PAJ7620U2(bus=1)

def gesture():
    gesture = paj.get_gesture()
    if gesture != paj.GESTURE_NONE:
      '''
      Get the string descritpion corresponding to the gesture number.
      The string description could be 
      "None","Right","Left", "Up", "Down", "Forward", "Backward", "Clockwise", "Anti-Clockwise", "Wave",
      "WaveSlowlyDisorder", "WaveSlowlyLeftRight", "WaveSlowlyUpDown", "WaveSlowlyForwardBackward"
      '''
      description  = paj.gesture_description(gesture);#Convert gesture number into string description
      print("--------------Gesture Recognition System---------------------------")
      print("gesture code        = %d"%(gesture))
      print("gesture description  = "+description)




if __name__ == "__main__":
    
    rospy.init_node('ros_gesture_recognize_highrate', anonymous=True)# 创建节点,命名空间为MPU6050_node_py
    print("Gesture recognition system base on PAJ7620U2")

    while(paj.begin() != 0):
      print("initial PAJ7620U2 failure! Please check if all the connections are fine, or if the wire sequence is correct?")
      time.sleep(0.5)

    print("PAJ7620U2 init finished, start to test the gesture recognition function.")


    rate = rospy.Rate(100) # 10hz 
    paj.set_gesture_highrate(True)

    while not rospy.is_shutdown():
        gesture()
        print("Gesture recognition system is running...")
        rate.sleep()
      
