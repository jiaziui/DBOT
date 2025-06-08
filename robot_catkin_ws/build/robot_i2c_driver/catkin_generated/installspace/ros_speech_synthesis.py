import sys
import rospy
import os
import rospkg
import time

rospack = rospkg.RosPack()
pkg_path = rospack.get_path('robot_i2c_driver')
lib_path = os.path.join(pkg_path, 'lib')
sys.path.append(lib_path)


from DFRobot_SpeechSynthesis import *
from sys import version_info


if __name__ == "__main__":
    
    rospy.init_node('ros_speech_synthesis', anonymous=True)# 创建节点,命名空间为MPU6050_node_py

    if version_info.major == 2 and version_info.minor == 7:#解决编码问题
        reload(sys)
        sys.setdefaultencoding("gbk")

    alcohol = DFRobot_SpeechSynthesis_I2C(1, I2C_ADDR)
  # alcohol = DFRobot_SpeechSynthesis_UART(115200)

    alcohol.set_voice(9)  # Set volume(0-9)
    alcohol.set_speed(5)  # Set playback speed (0-9)

    alcohol.set_tone(5)  # Set tone(0-9)
    alcohol.set_english_pron(WORD)  # Set word synthesis mode /WORD/ALPHABET

    rate = rospy.Rate(100) # 10hz 

    while not rospy.is_shutdown():
        
        alcohol.speak("i have a book")
        alcohol.speak("She sells seashells by the seashore")
        alcohol.speak("Hello world")
        #time.sleep(1)
        rate.sleep()
      

