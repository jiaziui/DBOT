import sys
import rospy
import os
import rospkg
import time

from robot_manager.msg import robot_speaker
from robot_manager.msg import robot_debug
from robot_manager.msg import robot_i2c_speak
from robot_manager.msg import robot_speak_flag

rospack = rospkg.RosPack()
pkg_path = rospack.get_path('robot_i2c_driver')
lib_path = os.path.join(pkg_path, 'lib')
sys.path.append(lib_path)

from  MPU6050 import MPU6050
from DFRobot_PAJ7620U2 import *
from DFRobot_SpeechSynthesis import *
from sys import version_info
from robot_manager.msg import imu_date# 导入自定义消息类型imu_date


robot_fwctEnd = 1000
servo_run_power = 10000
robot_landF =325
robot_landB =350
robot_fhMax = 22
robot_swMax = 11
robot_sport_state = 2
robot_fwctUp = 25
robot_control = 2

Dbot_m = 0
Dbot_itr = 0
Dbot_itr_flag = 0
Dbot_itr_old = 0

paj = DFRobot_PAJ7620U2(bus=1)

alcohol = DFRobot_SpeechSynthesis_I2C(1, I2C_ADDR)

text  = "Hello, 我是机器人助手小新,请叫我名字唤醒我。"
msg_buffer_flag = 1
speak_flag = 0
#speak_flag_old = 0
speak_msg_flag = 0

def robot_i2c_speak_callback(msg):

    global Dbot_m,Dbot_itr,Dbot_itr_flag,Dbot_itr_old,text,msg_buffer_flag,speak_flag,speak_msg_flag
    Dbot_m = msg.dbot_m

    Dbot_itr = msg.dbot_itr
    if Dbot_m == 1:
        Dbot_itr = 4
        Dbot_itr_flag = 1
    if Dbot_itr_flag == 1 and Dbot_m == 0:
       Dbot_itr_flag = 0
       Dbot_itr = 0

    if Dbot_itr == 2 and Dbot_itr_old != 2:
       text  = "Hello, 我是机器人助手小新,请叫我名字唤醒我。"
       msg_buffer_flag = 1
       speak_msg_flag = 1
       speak_flag = 1
    else:
       msg_buffer_flag = 0
       text = ""
       speak_msg_flag = 1
       speak_flag = 0
    
    Dbot_itr_old = Dbot_itr

def robot_msg_analysis(pub):
   global speak_flag,speak_msg_flag
   if(speak_msg_flag == 1):
      print("speak_msg_flag:",speak_msg_flag)
      speak_msg_flag = 0
      robot_speak_flag_msg = robot_speak_flag()
      robot_speak_flag_msg.speaker_flag = speak_flag
      pub.publish(robot_speak_flag_msg)
    


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
         robot_control = 7
         #int robot_swMax = 13;//mm
         robot_fhMax = 20
      elif gesture == 8: #down-8-右转
         robot_control = 6
         #int robot_swMax = 13;//mm
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

      if robot_control != 0:
        debug_msg.robot_sport_state = 0
        #debug_msg.robot_fwctEnd = robot_fwctEnd
        #debug_msg.servo_run_power = servo_run_power
        #debug_msg.robot_landF = robot_landF
        #debug_msg.robot_landB = robot_landB
        debug_msg.robot_fhMax = robot_fhMax
        #debug_msg.robot_swMax = robot_swMax
        #debug_msg.robot_fwctUp = robot_fwctUp
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
        robot_control = 0
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
    
################################### ROS功能包初始化 #################################
    rospy.init_node('robot_i2c_driver', anonymous=True)#anonymous=True表示节点名称可以重复

    rospy.Subscriber("/robot_speaker", robot_speaker, robot_speaker_callback)
    rospy.Subscriber("/robot_i2c_speak", robot_i2c_speak, robot_i2c_speak_callback)
    pub_imu = rospy.Publisher('/imu_data', imu_date, queue_size=10)
    pub = rospy.Publisher('/robot_speaker_buffer', robot_speaker, queue_size=10)
    pub_dubug = rospy.Publisher('/robot_debug_param', robot_debug, queue_size=10)#debug接口调用，控制机器人
    pub_speak = rospy.Publisher('/robot_speak_flag', robot_speak_flag, queue_size=10)

    pub_msg = robot_speaker()

    rate = rospy.Rate(100)
###################################################################################

######################### MPU6050 初始化############################################
    i2c_bus = 1
    device_address = 0x68

    x_accel_offset = int(926)
    y_accel_offset = int(2136)
    z_accel_offset = int(-856)
    x_gyro_offset = int(36)
    y_gyro_offset = int(-8)
    z_gyro_offset = int(-28)

    enable_debug_output = True
    mpu = MPU6050(i2c_bus, device_address, x_accel_offset, y_accel_offset,z_accel_offset, x_gyro_offset, y_gyro_offset, z_gyro_offset,enable_debug_output)

    mpu.dmp_initialize()
    mpu.set_DMP_enabled(True)
    mpu_int_status = mpu.get_int_status()
    print(hex(mpu_int_status))
    packet_size = mpu.DMP_get_FIFO_packet_size()
    print(packet_size)
    FIFO_count = mpu.get_FIFO_count()
    print(FIFO_count)
    FIFO_buffer = [0]*64
######################################################################################


###################################语音合成模块初始化###################################
    if version_info.major == 2 and version_info.minor == 7:#解决编码问题
      reload(sys)
      sys.setdefaultencoding("gbk")
    
    speech_module_init()
#####################################################################################



##############################################手势识别模块初始化######################
    while(paj.begin() != 0):
      print("initial PAJ7620U2 failure! Please check if all the connections are fine, or if the wire sequence is correct?")
      time.sleep(0.5) 
    gesture_module_init()
####################################################################################


    while not rospy.is_shutdown():
      #gesture(pub_dubug)#手势识别


        #Dbot_itr
        if Dbot_itr == 1:#手势识别
            gesture(pub_dubug)
        elif Dbot_itr == 2:#语音合成
            if len(text)>0 and msg_buffer_flag == 1 :
                say_something(text)#语音合成
                text = "" #清空缓冲区
                msg_buffer_flag = 0
                #pub_msg
                pub_msg.msg_clear_buffer_flag = msg_buffer_flag
                pub.publish(pub_msg)
                print("念完了！")
        elif Dbot_itr == 3:#人脸识别
            print("人脸识别")
        elif Dbot_itr == 4:#MPU6050
            try:
                FIFO_count = mpu.get_FIFO_count()
                mpu_int_status = mpu.get_int_status()
            except:
                continue
            
            if (FIFO_count == 1024) or (mpu_int_status & 0x10):
                mpu.reset_FIFO()
                #print('overflow!')
            elif (mpu_int_status & 0x02):

                while FIFO_count < packet_size:
                    FIFO_count = mpu.get_FIFO_count()
                FIFO_buffer = mpu.get_FIFO_bytes(packet_size)#读取数据
                gyro =mpu.get_rotation()
                accel = mpu.DMP_get_acceleration_int16(FIFO_buffer)#加速度
                quat = mpu.DMP_get_quaternion_int16(FIFO_buffer)#四元数
                grav = mpu.DMP_get_gravity(quat)#重力向量
                roll_pitch_yaw = mpu.DMP_get_euler_roll_pitch_yaw(quat, grav)#欧拉角
                
                #str_show = "roll: %.2f  pitch: %.2f  yaw: %.2f        "%(roll_pitch_yaw.x,roll_pitch_yaw.y,roll_pitch_yaw.z)
            
                #print("\r %s"%(str_show),end='')
                Imu_date  = imu_date()

                Imu_date.ax = accel.x
                Imu_date.ay = accel.y
                Imu_date.az = accel.z
                #陀螺仪数据
                Imu_date.gx = gyro[0]           # 这里需要添加四元数的转换
                Imu_date.gy = gyro[1]
                Imu_date.gz = gyro[2]
                #欧垃角数据
                Imu_date.pitch = roll_pitch_yaw.y
                Imu_date.roll = roll_pitch_yaw.x
                Imu_date.yaw = roll_pitch_yaw.z
                pub_imu.publish(Imu_date)
        robot_msg_analysis(pub_speak)
        rate.sleep()
        