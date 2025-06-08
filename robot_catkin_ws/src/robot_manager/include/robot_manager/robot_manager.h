#ifndef ROBOT_MANAGER_H
#define ROBOT_MANAGER_H

#include <ros/ros.h>
#include <iostream>
#include <string>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <mosquitto.h>
#include "cjson/cJSON.h"

#include "robot_manager/robot_state.h"
#include "robot_manager/robot_control.h"
#include "robot_manager/robot_i2c_speak.h"
#include "robot_manager/robot_machine.h"
//#include "ros_socket/socket.h"
/************debug**********/
//#define _MQTT_DEBUG_

#define PORT  1883//端口号
#define KEEP_ALIVE 60//心跳间隔
#define MSG_MAX_SIZE  512//消息最大长度
#define web_voice_port 33306//web_video_server_1端口号


char host[INET_ADDRSTRLEN];//保存ip地址字符串
char buff[MSG_MAX_SIZE];


bool session = true;//是否开启会话

float robot_electricity = 0.0; //电量
int robot_state = 0; //机器人状态
int robot_robot_devicer_state = 0;
int robot_camera_state = 0;

int robot_mode = 0; //机器人模式
int robot_speed = 0; //速度
int robot_control = 0;

char recv_date_buf[512] = {};


typedef struct Dbot_msg_center{
 //{"dbot_h":152,"dbot_roll":10,"dbot_p":338,"dbot_m":0,"dbot_ctl":4,"dbot_itr":0,"dbot_act":0}
    int dbot_h = 173;//mm
    int dbot_roll = 0;//°
    int dbot_p = 400;//ms
    int dbot_m = 0;//mod
    int dbot_ctl = 0;//ctl
    int dbot_itr = 0;//itr
    int dbot_act = 0;//action
}dbot_msg;



ros::NodeHandle *n;
//发布者
ros::Publisher robot_control_pub; 
// ros::Publisher robot_socket_pub; 
//订阅者
// ros::Subscriber robot_state_sub; 
// ros::Subscriber robot_socket_sub; 

ros::Publisher robot_machine_pub; 
ros::Publisher robot_i2c_speak_pub;

//void socket_callback(const ros_socket::socket::ConstPtr& msg);
void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos);
void my_connect_callback(struct mosquitto *mosq, void *userdata, int result);
void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
void my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str);
void state_callback(const robot_manager::robot_state::ConstPtr& msg);
void sigint_handler(int sig);
void robot_i2c_speak_pub_msg(void);
void robot_machine_pub_msg(void);



#endif // ROBOT_MANAGER_H