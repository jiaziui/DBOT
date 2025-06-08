import rospy
import rospkg
import pyaudio  
import wave  
import time
import json
import os 
from openai import OpenAI
import base64
import numpy as np#导入numpy库，用于处理音频数据
import soundfile as sf
import requests
from pydub import AudioSegment#导入pydub库，用于处理音频文件


from openai import OpenAI
import requests#导入requests库，用于发送HTTP请求
import sys

from time import sleep
from robot_manager.msg import robot_vosk
from robot_manager.msg import robot_speaker
from robot_manager.msg import robot_i2c_speak
from robot_manager.msg import robot_speak_flag


audio = pyaudio.PyAudio()

robot_buffer = 1
robot_vosk_flag = 0

Dbot_m = 0
Dbot_itr = 0

rospack = rospkg.RosPack()
pkg_path = rospack.get_path('robot_speak')
lib_path = os.path.join(pkg_path, 'lib')
sys.path.append(lib_path)

import snowboydecoder
####################

wave_file = lib_path +"/output.wav"
model_file =lib_path +"/xx.pmdl"
awake_status = 0
robot_audio_flag = 0

dbot_speak_flag = 0


def encode_audio(audio_path):#将音频文件编码为base64格式
    with open(audio_path, "rb") as audio_file:
        return base64.b64encode(audio_file.read()).decode("utf-8")
    
FORMAT = pyaudio.paInt16   # 音频格式
CHANNELS = 1               # 单声道
RATE = 48000               # 采样率
CHUNK = 2048               # 每次读取的音频帧数
THRESHOLD =8000            # 音量阈值 
RECORD_SECONDS = 20        # 最大录音时间 
SILENCE_DURATION = 700     # 静音持续时间（秒）


def get_volume(data):  
    """计算音量"""  
    return np.linalg.norm(np.frombuffer(data, dtype=np.int16)  )

def pub_vosk_flag(pub_vosk):
    Robot_speaker_vosk = robot_vosk()
    Robot_speaker_vosk.robot_audio_flag = 1
    pub_vosk.publish(Robot_speaker_vosk)


def robot_speak_flag_callback(msg):
    global dbot_speak_flag,awake_status,robot_audio_flag,robot_buffer,robot_vosk_flag
    dbot_speak_flag = msg.speaker_flag
    print("dbot_speak_flag =",dbot_speak_flag)
    if dbot_speak_flag == 0:
        awake_status = 0
        robot_audio_flag = 0
        dbot_speak_flag = 0
        robot_buffer = 1
        robot_vosk_flag = 0


def record_audio(pub):  
    # 开始流  
    global awake_status,dbot_speak_flag,robot_buffer,audio
    while robot_buffer == 1:
        sleep(0.1)        
        if robot_buffer == 0:
             print("读功能已关闭，开启录音检测")
             break
    if dbot_speak_flag == 0:
        print("语音功能未启动，等待唤醒词...")
        return    
    # 打开流
    stream = audio.open(format=FORMAT, channels=CHANNELS,  
                        rate=RATE, input=True,  
                        frames_per_buffer=CHUNK,
                        input_device_index=1
                      )  
      
    print("\n请讲...")  
  
    frames = []  
    recording = False  
    silence_start_time = None  # 用于记录静音开始时间  
    start_time = time.time()    # 记录开始时间  
    
    while True:  
        # 读取音频数据  
        if dbot_speak_flag == 0:
            print("语音功能未启动，等待唤醒词...")
            stream.stop_stream()  
            stream.close()  
            return False
        data = stream.read(CHUNK, exception_on_overflow=False)  
        volume = get_volume(data)  
        if volume>10000:
            print(volume)
        if abs(volume) > THRESHOLD and not recording:  
            print("AI: 持续聆听中...")  
            recording = True  
            start_time = time.time()  #记录开始时间
            silence_start_time = None  #重置静音计时器  
          
        if recording:  
            frames.append(data)  
            #print(f"录音中... 音量: {volume}")  
            #print(f".",end="")  
  
            # 检查录音时间  
            if time.time() - start_time > RECORD_SECONDS:  
                print("达到最大录音时间，停止录音")  
                break  
            if time.time()*1000-(start_time*1000)<2000:
                continue
            # 检查静音  
            if abs(volume) < THRESHOLD:
                if silence_start_time is None:
                    silence_start_time=time.time()*1000
                diff = time.time()*1000 - silence_start_time
                if diff > SILENCE_DURATION:  
                    print(f"检测到静音[{diff}ms]超过 1 秒，停止录音")  
                    break 
            else:  
                silence_start_time = None # 记录静音开始时间  
            

    # 停止流  
    stream.stop_stream()  
    stream.close()  
    #audio.terminate() # 关闭音频流
    
  
    # 保存录音  
    if frames: #保存在本地，路径为当前目录下
        with wave.open(wave_file, 'wb') as wf:  # 保存为wav格式  ,路径为lib目录下
            wf.setnchannels(CHANNELS)  
            wf.setsampwidth(audio.get_sample_size(FORMAT))  
            wf.setframerate(RATE)  
            wf.writeframes(b''.join(frames))  
        print("录音已保存为 output.wav")  
        sound = AudioSegment.from_file(wave_file)     # 读取音频文件
        sound = sound.set_frame_rate(16000)              # 设置采样率为 16000Hz
        sound.export(lib_path+"/output_16k.wav", format="wav")
        
        if awake_status == 1:
            #音频录制完成，vosk
            if dbot_speak_flag == 1:
                pub_vosk_flag(pub)

        return True
    else:  
        print("没有录音数据")
        return False


def encode_audio(audio_path):#将音频文件编码为base64格式
    with open(audio_path, "rb") as audio_file:
        return base64.b64encode(audio_file.read()).decode("utf-8")

client = OpenAI(
    # 若没有配置环境变量，请用百炼API Key将下行替换为：api_key="sk-xxx",
    api_key="sk-e73bc39023ab48bba6cc2149d04396e9",
    base_url="https://dashscope.aliyuncs.com/compatible-mode/v1",
)

def remove_unsupported_chars(text):
    return text.encode('gb2312', errors='ignore').decode('gb2312', errors='ignore')


sys_msg={
    "role": "system",
    "content": [{"type": "text", "text": "You are a helpful robot."}],
}

messages=[]
def generate(pub,Robot_speaker):  
    print("AI: 正在生成回复...")
    global robot_vosk_flag,dbot_speak_flag,robot_buffer,messages

    base64_audio = encode_audio(lib_path + "/output.wav")#将音频文件编码为base64格式
    messages=messages[-5:]+[{
                "role": "user",
                "content": [
                    {
                        "type": "input_audio",
                        "input_audio": {
                            "data": f"data:;base64,{base64_audio}",
                            "format": "wav",
                        },
                    }
                ],
            }]
    completion = client.chat.completions.create(
        model="qwen-omni-turbo",
        messages=[sys_msg]+messages[-6:],
        # 设置输出数据的模态，当前支持两种：["text","audio"]、["text"]
        modalities=["text"],
        #audio={"voice": "Chelsie", "format": "wav"},
        # stream 必须设置为 True，否则会报错
        stream=True,
        stream_options={"include_usage": True},
    )
    full_response = ""
    for chunk in completion:#遍历每一块数据，包括文本和音频     
         if chunk.choices:
            delta_obj = chunk.choices[0].delta
            delta_text = delta_obj.content  # 取出字符串内容
            if delta_text:  # 只有有内容时才处理
                #print(delta_text, end="", flush=True)
                full_response += delta_text
        # else:
        #     print(chunk.usage)#打印使用情况
    #print(f"AI: {text}")
    #print(full_response)
    
    full_response = remove_unsupported_chars(full_response)
    print(f"AI: {full_response}")

    if len(full_response)>0 and dbot_speak_flag == 1:
        
        while robot_vosk_flag == 0:
            sleep(0.1)        
        if robot_vosk_flag == 1:
            print("读功能已关闭，开启录音检测")
            return
    
        Robot_speaker.chinese_text = full_response
        Robot_speaker.msg_buffer_flag  = 1
        pub.publish(Robot_speaker)
        robot_buffer = 1
        robot_vosk_flag = 0

def robot_vosk_callback(msg):
    global robot_vosk_flag,robot_buffer 
    robot_vosk_flag = msg.robot_vosk_flag
    print("robot_vosk_flag =",robot_vosk_flag)
    if robot_vosk_flag == 1:
        robot_buffer = 1

def robot_speaker_buffer_callback(msg):
    global robot_buffer
    robot_buffer = msg.msg_clear_buffer_flag
    print("robot_buffer =" ,robot_buffer)

def robot_i2c_speak_callback(msg):
    global Dbot_m,Dbot_itr
    Dbot_m = msg.dbot_m
    Dbot_itr = msg.dbot_itr
    print("Dbot_m =",Dbot_m)

if __name__ == "__main__":#主函数
    rospy.init_node('robot_speak_api', anonymous=True)

    pub = rospy.Publisher('/robot_speaker', robot_speaker, queue_size=10) #创建发布者,话题名为imu_data,队列长度为10,消息类型为imu_data类型
    rospy.Subscriber("/robot_speaker_buffer", robot_speaker, robot_speaker_buffer_callback)
    pub_vosk = rospy.Publisher('/robot_vosk', robot_vosk, queue_size=10)
    rospy.Subscriber("/robot_vosk", robot_vosk, robot_vosk_callback)
    rospy.Subscriber("/robot_speak_flag", robot_speak_flag, robot_speak_flag_callback)
    rospy.Subscriber("/robot_i2c_speak", robot_i2c_speak, robot_i2c_speak_callback)

    Robot_speaker = robot_speaker()
    audio_flag = 0 
    rate = rospy.Rate(20)

    while True:
        if dbot_speak_flag == 1:

            audio_flag = record_audio(pub_vosk)  
            if audio_flag:#如果录音成功
                if awake_status == 0:
                    audio_flag = 0
                    f = wave.open(lib_path+"/output_16k.wav")
                    assert f.getnchannels() == 1, "Error: Snowboy only supports 1 channel of audio (mono, not stereo)"
                    assert f.getframerate() == 16000, "Error: Snowboy only supports 16K sampling rate"
                    assert f.getsampwidth() == 2, "Error: Snowboy only supports 16bit per sample"
                    data = f.readframes(f.getnframes())
                    f.close()

                    sensitivity = 0.55
                    detection = snowboydecoder.HotwordDetector(model_file, sensitivity=sensitivity)

                    ans = detection.detector.RunDetection(data)

                    if ans == 1:
                        print("检测到唤醒词，开始生成回复")
                        Robot_speaker.chinese_text = "哎"
                        Robot_speaker.msg_buffer_flag  = 1
                        pub.publish(Robot_speaker)
                        robot_buffer = 1

                        awake_status = 1
                    else:
                        print("未检测到唤醒词，继续录音")
                else:
                    audio_flag = 0
                    awake_status = 0
                    generate(pub,Robot_speaker)#生成回复
        else:
            print("等待语音功能启动...")
            awake_status = 0
            robot_audio_flag = 0
            robot_buffer = 1
            robot_vosk_flag = 0
        rate.sleep()