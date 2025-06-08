import sys
import rospy
import os
import rospkg
import time

from robot_manager.msg import robot_speaker
from robot_manager.msg import robot_debug

rospack = rospkg.RosPack()
pkg_path = rospack.get_path('robot_i2c_driver')
lib_path = os.path.join(pkg_path, 'lib')
sys.path.append(lib_path)

from DFRobot_PAJ7620U2 import *
from DFRobot_SpeechSynthesis import *
from sys import version_info


robot_fwctEnd = 1000
servo_run_power = 10000
robot_landF =325
robot_landB =350
robot_fhMax = 22
robot_swMax = 11
robot_sport_state = 2
robot_fwctUp = 25
robot_control = 2




paj = DFRobot_PAJ7620U2(bus=1)

alcohol = DFRobot_SpeechSynthesis_I2C(1, I2C_ADDR)

text  = "Hello, 我是机器人助手小新，请多指教。"
msg_buffer_flag = 1

def gesture(pub_dubug):
    global robot_sport_state
    global robot_fwctEnd
    global servo_run_power
    global robot_landF
    global robot_landB
    global robot_fhMax
    global robot_swMax
    global robot_fwctUp
    global robot_control

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
      print("gesture code        = %d"%(gesture))#%(gesture), %d is the placeholder for integer value
      print("gesture description  = "+description)
      debug_msg = robot_debug()#debug接口调用，控制机器人

      if gesture == 4: #up-4-左转
         robot_control = 6
         # int robot_swMax = 13;//mm
         robot_fhMax = 20
      elif gesture == 8: #down-8-右转
         robot_control = 7
         # int robot_swMax = 13;//mm
         robot_fhMax = 20
      elif gesture == 2: #left-2-停止
         robot_control = 2
         robot_fhMax = 20
      elif gesture == 1: #right-1-前进
         robot_control = 4
         robot_fhMax = 24
      else:
          robot_control = 3
          robot_fhMax = 20
      
      debug_msg.robot_sport_state = robot_sport_state
      debug_msg.robot_fwctEnd = robot_fwctEnd
      debug_msg.servo_run_power = servo_run_power
      debug_msg.robot_landF = robot_landF
      debug_msg.robot_landB = robot_landB
      debug_msg.robot_fhMax = robot_fhMax
      debug_msg.robot_swMax = robot_swMax
      debug_msg.robot_fwctUp = robot_fwctUp
      debug_msg.robot_control = robot_control
      print("------------------------------------------------------------------")
      print("robot_sport_state = %d"%(robot_sport_state))
      print("robot_fwctEnd = %d"%(robot_fwctEnd))
      print("servo_run_power = %d"%(servo_run_power))
      print("robot_landF = %d"%(robot_landF))
      print("robot_landB = %d"%(robot_landB))
      print("robot_fhMax = %d"%(robot_fhMax))
      print("robot_swMax = %d"%(robot_swMax))
      print("robot_fwctUp = %d"%(robot_fwctUp))
      print("robot_control = %d"%(robot_control))
      print("------------------------------------------------------------------")

      pub_dubug.publish(debug_msg)
         
      


def speech_module_init():
   
    alcohol.set_voice(9)  # Set volume(0-9)
    alcohol.set_speed(5)  # Set playback speed (0-9)
    alcohol.set_soundType(MEAL)
    alcohol.set_tone(5)  # Set tone(0-9)
    alcohol.set_english_pron(WORD)  # Set word synthesis mode /WORD/ALPHABET

def gesture_module_init():
    paj.set_gesture_highrate(True)


def say_something(text):
    alcohol.speak(text)

def robot_speaker_callback(msg):
    print("msg.chinese_text = ",msg.chinese_text)
    print("msg.msg_buffer_flag = ",msg.msg_buffer_flag)
    global text
    global msg_buffer_flag
    text = msg.chinese_text
    msg_buffer_flag = msg.msg_buffer_flag

    


if __name__ == "__main__":
    
    rospy.init_node('robot_i2c_driver', anonymous=True)#anonymous=True表示节点名称可以重复
    

    if version_info.major == 2 and version_info.minor == 7:#解决编码问题
      reload(sys)
      sys.setdefaultencoding("gbk")
    
    speech_module_init()
    while(paj.begin() != 0):
      print("initial PAJ7620U2 failure! Please check if all the connections are fine, or if the wire sequence is correct?")
      time.sleep(0.5) 
    gesture_module_init()
    
    rate = rospy.Rate(100) # 10hz 
    rospy.Subscriber("/robot_speaker", robot_speaker, robot_speaker_callback)
    pub = rospy.Publisher('/robot_speaker_buffer', robot_speaker, queue_size=10)
    pub_dubug = rospy.Publisher('/robot_debug_param', robot_debug, queue_size=10)#debug接口调用，控制机器人

    while not rospy.is_shutdown():
      gesture(pub_dubug)

      if len(text)>0 and msg_buffer_flag == 1 :
        say_something(text)
        text = ""
        msg_buffer_flag = 0
        pub_msg = robot_speaker()
        pub_msg.msg_clear_buffer_flag = msg_buffer_flag
        pub.publish(pub_msg)
        print("念完了！")

      rate.sleep()
      
      
