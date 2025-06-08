import rospy
import rospkg

import os
import wave
import json
from time import sleep
from vosk import Model, KaldiRecognizer
import sys

import requests
import base64
from openai import OpenAI

from robot_manager.msg import robot_vosk
from robot_manager.msg import robot_speaker
from robot_manager.msg import robot_speak_flag
from robot_manager.msg import robot_debug


dbot_speak_flag = 0


def pub_act(pub):
    print("已发布动作信息！")
    debug_msg = robot_debug()
    debug_msg.robot_sport_state = 12
    pub.publish(debug_msg)

client = OpenAI(
    api_key="sk-2bed04c284ca42fd9fdddd72b64146c3",
    base_url="https://dashscope.aliyuncs.com/compatible-mode/v1",
)

rospack = rospkg.RosPack()
pkg_path = rospack.get_path('robot_speak')
lib_path = os.path.join(pkg_path, 'lib')
sys.path.append(lib_path)

out_text = ""
Robot_speaker = robot_speaker()
robot_audio_flag = 0

def robot_speak_flag_callback(msg):
    global dbot_speak_flag, out_text, robot_audio_flag
    dbot_speak_flag = msg.speaker_flag
    if dbot_speak_flag == 0:
        print("robot_speak_flag = 1")
        out_text = ""
        robot_audio_flag = 0


def get_image_base64_from_url(image_url):
    response = requests.get(image_url)
    if response.status_code != 200:
        raise Exception(f"图像获取失败，状态码：{response.status_code}")
    
    content_type = response.headers.get('Content-Type', '')
    if 'jpeg' in content_type:
        mime_type = "image/jpeg"
    elif 'png' in content_type:
        mime_type = "image/png"
    elif 'webp' in content_type:
        mime_type = "image/webp"
    else:
        raise Exception(f"不支持的图像格式: {content_type}")

    base64_image = base64.b64encode(response.content).decode('utf-8')
    return f"data:{mime_type};base64,{base64_image}"





def remove_all_spaces(text):
    return text.replace(" ", "")

model_dir = lib_path + "/vosk-model-small-cn-0.22"  # 如果目录名包含连字符，需用引号包裹
if not os.path.exists(model_dir):
    print("model load fail!")
    exit(1)

model = Model(model_dir)


def pub_vosk_flag(flag,pub_vosk):
     Robot_speaker_vosk = robot_vosk()
     Robot_speaker_vosk.robot_vosk_flag = flag
     print("robot_vosk_flag =",Robot_speaker_vosk.robot_vosk_flag)
     pub_vosk.publish(Robot_speaker_vosk)

def keyword_recognize(pub,pub_vosk,pub_debug):
    global out_text#全局部变量
    global Robot_speaker

    print("关键字识别:")

    if(out_text.find("能力")>=0 or out_text.find("自我介绍") >= 0):   
        Robot_speaker.chinese_text = "您好，我是一款非常可爱且有礼貌的双足机器人，我的名字叫小新，你可以叫我的名字唤醒我。我的能力有语音互动、手势互动、人脸识别,你也可以使用手机APP与我互动!"
        Robot_speaker.msg_buffer_flag  = 1
        pub.publish(Robot_speaker)

        
        print("识别到关键字")
        pub_vosk_flag(1,pub_vosk)
    elif out_text.find("看到")>=0:
        print("识别结果为")
        try:
            image_data_url = get_image_base64_from_url(image_url)
        except Exception as e:
            print(f"获取图像失败: {e}")

        completion = client.chat.completions.create(
                model="qwen-vl-max-latest",
                messages=[
                    {"role": "system", "content": [{"type": "text", "text": "You are a helpful assistant."}]},
                    {"role": "user", "content": [
                        {"type": "image_url", "image_url": {"url": image_data_url}},
                        {"type": "text", "text": "你看到了的是什么景象?20个字回答我,不用说明背景中的内容"}
                    ]}
                ]
            )
        print(completion.choices[0].message.content)

        Robot_speaker.chinese_text = completion.choices[0].message.content
        Robot_speaker.msg_buffer_flag  = 1
        pub.publish(Robot_speaker)
        
        pub_vosk_flag(1,pub_vosk)        
    elif out_text.find("动起来")>=0:
        print("动起来")
        pub_act(pub_debug)


        Robot_speaker.chinese_text = "好的，好的"
        Robot_speaker.msg_buffer_flag  = 1
        pub.publish(Robot_speaker)

        pub_vosk_flag(1,pub_vosk)
        
        '''
        #这是我写的这个项目的最后的代码，请不要删除，以此留念！  
                这个项目是我目前做过的最复杂的项目了，我很享受这个
            过程，我也很感谢我的激情和热情，在这个过程中，我学到了
            很多，也收获了很多，我也很开心，我也很期待我的未来，我
            也很期待我的下一个项目。
                                                        ---jia
        '''
    else:
        print("没有识别到关键字")
        pub_vosk_flag(2,pub_vosk)
	


def robot_vosk_callback(msg):
    global robot_audio_flag
    robot_audio_flag = msg.robot_audio_flag

if __name__ == "__main__":#主函数
    rospy.init_node('robot_hear_vosk', anonymous=True)
   
    ip = rospy.get_param('/web_video_server_1/address')

    image_url = "http://"+ip+":33306/snapshot?topic=/usb_cam/image_raw"

    pub = rospy.Publisher('/robot_speaker', robot_speaker, queue_size=10)
    pub_vosk = rospy.Publisher('/robot_vosk', robot_vosk, queue_size=10) 
    rospy.Subscriber("/robot_vosk", robot_vosk, robot_vosk_callback)
    rospy.Subscriber("/robot_speak_flag", robot_speak_flag, robot_speak_flag_callback)
    pub_dubug = rospy.Publisher('/robot_debug_param', robot_debug, queue_size=10)
    
    rate = rospy.Rate(10)

    while not rospy.is_shutdown():

        if robot_audio_flag == 1:
            #############################################################################################################
            print("开始识别...")
            wf = wave.open(lib_path + "/output_16k.wav", "rb")  # 识别路径
            # if wf.getnchannels() != 1 or wf.getsampwidth() != 2 or wf.getcomptype() != "NONE":  # 修正点：添加引号和冒号
            #     print("Audio file must be WAV format mono PCM.")
            #     exit(1)
            rec = KaldiRecognizer(model, wf.getframerate())
            all_results = []
            while True:  #修正点：添加冒号
                data = wf.readframes(8000) 
                if len(data) == 0:
                    break
                if rec.AcceptWaveform(data):
                    result = json.loads(rec.Result())  # 解析结果为字典
                    if "text" in result:
                        all_results.append(result["text"])  # 存储中文结果
                else:  #修正点：添加冒号
                    rec.PartialResult()

            out_text = remove_all_spaces(" ".join(all_results))
            print("最终识别结果：")
            print(out_text)
            print("**********************************")

            keyword_recognize(pub,pub_vosk,pub_dubug)

            out_text = ""
            robot_audio_flag = 0
            #############################################################################################################
        rate.sleep()

        # 循环等待回调函数topic
        #rospy.spin()
        #不循环等待
        #rospy.spinOnce()
        