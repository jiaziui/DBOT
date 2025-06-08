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


rospack = rospkg.RosPack()
pkg_path = rospack.get_path('robot_speak')
lib_path = os.path.join(pkg_path, 'lib')
sys.path.append(lib_path)

from DFRobot_SpeechSynthesis import *
from sys import version_info

if version_info.major == 2 and version_info.minor == 7:
    reload(sys)
    sys.setdefaultencoding("gbk")

####################


def encode_audio(audio_path):#将音频文件编码为base64格式
    with open(audio_path, "rb") as audio_file:
        return base64.b64encode(audio_file.read()).decode("utf-8")
    
FORMAT = pyaudio.paInt16  # 音频格式  
CHANNELS = 1               # 单声道  
RATE = 44100               # 采样率  
CHUNK = 2048               # 每次读取的音频帧数  
THRESHOLD =10000            # 音量阈值  
RECORD_SECONDS = 20        # 最大录音时间  
SILENCE_DURATION = 700      # 静音持续时间（秒） 


def get_volume(data):  
    """计算音量"""  
    return np.linalg.norm(np.frombuffer(data, dtype=np.int16)  )


def record_audio():  
    # 开始流  
    audio = pyaudio.PyAudio() 

    stream = audio.open(format=FORMAT, channels=CHANNELS,  
                        rate=RATE, input=True,  
                        frames_per_buffer=CHUNK
                        )  
      
    print("\n请讲...")  
  
    frames = []  
    recording = False  
    silence_start_time = None  # 用于记录静音开始时间  
    start_time = time.time()    # 记录开始时间  
  
    while True:  
        # 读取音频数据  
        data = stream.read(CHUNK, exception_on_overflow=False)  
        volume = get_volume(data)  
        if volume>10000:
            print(volume)  
        if abs(volume) > THRESHOLD and not recording:  
            print("AI: 持续聆听中...")  
            recording = True  
            start_time = time.time()  # 记录开始时间  
            silence_start_time = None  # 重置静音计时器  
          
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
    audio.terminate() # 关闭音频流
    #audio.close()# 关闭音频对象
  
    # 保存录音  
    if frames:  
        with wave.open("output.wav", 'wb') as wf:  
            wf.setnchannels(CHANNELS)  
            wf.setsampwidth(audio.get_sample_size(FORMAT))  
            wf.setframerate(RATE)  
            wf.writeframes(b''.join(frames))  
        print("录音已保存为 output.wav")  
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
def generate(alcohol):  
    print("AI: 正在生成回复...")
    global messages  
    base64_audio = encode_audio("/home/jia/ftp_share/Ai_api/yuyinluzhi/output.wav")
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
                print(delta_text, end="", flush=True)
                full_response += delta_text
        # else:
        #     print(chunk.usage)#打印使用情况
    #print(f"AI: {text}")
    #print(full_response)
    if len(full_response)>0:
        full_response = remove_unsupported_chars(full_response)
        alcohol.speak(full_response)



if __name__ == "__main__":#主函数
    rospy.init_node('robot_speak_api', anonymous=True)

    audio_flag = 0 
    alcohol = DFRobot_SpeechSynthesis_I2C(1, I2C_ADDR)
    alcohol.set_voice(9)  # Set volume(0-9)
    alcohol.set_speed(5)  # Set playback speed (0-9)
    alcohol.set_soundType(MEAL)
    alcohol.set_tone(5) 
    alcohol.set_english_pron(WORD)  # Set word synthesis mode /WORD/ALPHABET

    while True:
        audio_flag = record_audio()  
        if audio_flag:#如果录音成功
            audio_flag = 0
            generate(alcohol)#生成回复
        
        

