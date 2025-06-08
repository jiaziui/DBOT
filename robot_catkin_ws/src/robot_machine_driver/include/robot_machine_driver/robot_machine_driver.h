#ifndef ROBOT_MACHINE_DRIVER_H
#define ROBOT_MACHINE_DRIVER_H

#include <ros/ros.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <signal.h>
#include <stdio.h>

#include "CSerialPort/SerialPort.h"
#include "FashionStar/UServo/FashionStar_UartServoProtocol.h"
#include "FashionStar/UServo/FashionStar_UartServo.h"

#include "robot_manager/imu_date.h"
#include "robot_manager/robot_debug.h"
#include "robot_manager/robot_control.h"
#include "robot_manager/robot_state.h"
#include "robot_manager/robot_machine.h"

#define SERVO_PORT_NAME "/dev/ttyAMA0"  // 树莓派串口"/dev/ttyAMA0"
#define robot_servo_num 16

/***************DEBUG****************/
//#define robot_msg_debug 
//#define robot_control_debug 
//#define robot_joint_debug
//#define topic_debug
//#define dbot_rub
//#define _dbug_msg

/***************参数数据************/
#define set_Damping_power 1000 //摔倒阻尼功率
#define set_run_init_power 20000 //初始运行功率

//#define _set_leg_

#define robot_leg_1 40 //mm
#define robot_leg_2 94 
#define robot_leg_3 94 
#define robot_leg_4 40
float robot_inital_height = 173.0; //173mm
#define robot_height_MAX  210.0 
#define robot_height_MIN 140.0 
#define roll_stab_MAX  30 //mm
#define roll_stab_MIN -30 //mm
#define robot_foot_angle_MAX 20 //单位度
#define robot_foot_angle_MIN -20 
#define robot_Span_width 85.0
#define robot_roll_abnormal 30 //单位度
#define robot_pitch_abnormal 30


/*****robot_control_param****/
#define robot_start 0 //初始状态
#define robot_imu_adjust 1 //imu校准
#define robot_control_stop 2 //imu持续校准,停止工作
#define robot_control_word 3 //原地
#define robot_control_forward 4
#define robot_control_backward 5
#define robot_control_turn_left 6
#define robot_control_turn_right 7
#define robot_control_move_left 8
#define robot_control_move_right 9
#define robot_status_switching 10//状态切换
#define robot_param_change 11//参数修改

#define robot_msg_frequency 500

using namespace std;
using namespace fsuservo;

/************运动控制参数***************/
float roll_stab = 0;
int msg_i;

bool supportleg = 0;
int  robot_fwct = 0;
float robot_fh = 0;
float robot_swy = 0;

//前进|后退
float robot_swx_max = 8;
int robot_forword_flag = 0;
float robot_swx_l =0,robot_swx_r =0;
float robot_B_F_offset = 0;
float robot_B_F_offset_Max = 2.4;

int loin_count = -1;
float loin_turn_angle = 8;
bool turn_lift_flag = 0;//开始标志位
bool turn_right_flag = 0;

int robot_fwctEnd =1000;
int servo_run_power = 10000;
int robot_landF =325;
int robot_landB =350;
float robot_fhMax = 22;//mm
float robot_swMax = 11;//mm
int robot_sport_state = 0;
int robot_fwctUp = 25;//25*4*10  = 1000
int robot_control = 0;

int robot_balance_flag = 1;

/***************DBOT**************/
volatile unsigned char dbot_msg_flag[3] ={0,0,0};
//#define _bit_opr

/*
dbot_msg_flag   [0]位 高读变化flag 
dbot_msg_flag   [1]位 倾斜度变化flag 
dbot_msg_flag   [2]位 周期变化flag
[''']
*/

unsigned char dbot_mode = 0;

#ifdef dbot_rub
int motCt_h = 0;
int motCt_p = 0;
int motCt_r = 0;
#endif

 float dbot_roll_angle = 0;

/**********************************/

typedef struct Dbot_machine_msg{
    int dbot_h = 0;
    int dbot_roll = 0;
    int dbot_p = 0;
    int dbot_m = 0;
    int dbot_ctl = 0;
    int dbot_act = 0;

}dbot_machine_msg;


struct robot_balance_param{
    //imu校准参数
    float ipb;//上一次的角度
    float irb;
    float ira;//角度积分
    float ipa;
    float ip;
    float ir;
    float igxa;
    float igya;
    float robot_roll_offset = 3.0146;//测得偏差
    float robot_pitch_offset = 4.252325;
    float robot_gx_offset = -43.742500;
    float robot_gy_offset = -19.175;
    //float robot_gz_offset;

    //PID参数
    float kp_leg = 0.3;//比例系数

    float kp_roll = 0.3;//roll比例系数
    float kp_pitch = 0.3;//pitch比例系数

    float kd_roll = 0.1;//roll微分系数
    float kd_pitch = 0.1;//pitch微分系数

    //补偿值
    float robot_roll_compensation_value = 0;//roll补偿值，补偿高度
    float robot_pitch_compensation_value = 0;//pitch补偿值,补偿角度

};

 struct servo_driver{
    float current_angle[17];
    float target_angle[17];
    float server_angle_offset[17] = {-1 ,8,37.5,1.5,-3,-9,-4,6.5,-31,-7,3,-6.5,-50,-11,-39, 0 ,13};

    float joint_limit_min[17] = {-50,  -90, 0, -10, -30, -50, -30, -90,-90, 0,-50,-180,-40, -90,-180,-40,-90};
    float joint_limit_max[17] = { 60, 0, 90, 90,  30,  50,  30,  10,  0,90, 60, 180, 180, 90, 180, 180, 90};

    float joint_flag[17] ={1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1};

    float robot_init_angle[17] = {0,-45,45,3,0,0,0,-3,-45,45,0,0,0,0,0,0,0};
    //int robot_servo_polarity[17] = {1,1,1,1,1,1,1,-1,1,1,1,1,1,1,1,1,1};//舵机极性
    float robot_foot_angle = 0.0;
};


struct robot_control_data{
    int robot_control_mode;
    int robot_control; // 0:stop, 1:word, 2:forward, 3:turn left, 4:turn right,~

};

 struct robot_imu_data{

	float accele_x_data; 
	float accele_y_data; 	
	float accele_z_data; 
    float gyros_x_data; 
	float gyros_y_data; 	
	float gyros_z_data; 

    float yaw_angle;
    float pitch_angle;
    float roll_angle;

    float rolls;
    float pitchs;
    float yaws;
};


struct servo_param{
    //msg
    float servo_tempterature[17];
    float servo_voltage;
    float servo_current[17];

    //control
    int power[17];//功率
    int interval[17];//ms
};

struct RobotMachineDriver
{
    //舵机数据结构
    //robot_debug_data debug_data;//调试数据结构
    robot_control_data control_data;//控制数据结构
    servo_param servo_param_data;//舵机参数数据结构
};

void ctl_callback(const robot_manager::robot_control::ConstPtr &msg);
void imu_callback(const robot_manager::imu_date::ConstPtr &msg); //imu数据回调函数
void debug_callback(const robot_manager::robot_debug::ConstPtr &msg); //调试数据回调函数
void machine_msg_callback(const robot_manager::robot_machine::ConstPtr &msg);//DBOT：app_date

void sigintHandler(int sig); //信号处理函数
void init(void); //初始化函数
void servo_init(void); //舵机初始化函数
void joint_angle_init(void); //各关节角度标定
void joint_param_init(void); //设置转速，功率

void read_servo_msg(void); //读取舵机角度
bool bitRead(uint8_t value, uint8_t bit);//判断某个位是否为1

void walk(); //机器人驱动
//角度限幅
void joint_angle_limit(void); //各关节角度限幅
void robot_servo_refesh(void); //舵机角度刷新,非阻塞
void robot_angAdj(void);// 角度校准
void robot_detAng(void);// 全向跌倒检测
#ifdef _set_leg_
bool robot_joint_leg1(float x,float z,int leg);
#endif
bool robot_joint_leg(float xx,float yy,float zz,int leg);
void robot_all_joint(float x0, float y0, float x1, float y1, int s);
void robot_all_joint1(int s);

void robot_footUp(void);//抬腿
void counterCont(void);//计数器控制
void robot_swCont(void);//横向控制
void robot_swx_Cont(void);//前后控制
void imu_Continu_calibration(void); //imu持续误差校准,减少机械误差带来的影响
void robot_status_switch(int statu_praesens); //状态切换
void robot_status_param_init(void); //状态参数初始化
    
void robot_balance_init(void);//机器人平衡初始化,主要是PID参数初始化
void robot_balance_run(void);//机器人平衡运行，开环PID控制
float robot_roll_offset_get(void);//roll偏差获取函数，推算横滚(roll)的高度偏差
float robot_pitch_offset_get(void);//pitch偏差获取函数
float robot_roll_compensation_value(void);//roll补偿值获取函数，
float robot_pitch_compensation_value(void);//pitch补偿值获取函数，推算前后俯仰(pitch)的角度补偿值

/************************************DBOT*******************************************/
void date_analysis(void);//数据变化驱动
void dbot_mot_ii(int date_1,int date_2,int motCt);//数据减速处理
void dbot_mot_ff(float date_1,float date_2,int motCt);//数据减速处理
void dbot_mot_if(int date_1,float date_2,int motCt);//数据减速处理
void dbot_mot_fi(float date_1,int date_2,int motCt);//数据减速处理
void dbot_rool_date_analysis(void);

#ifdef _bit_opr
bool get_bit(unsigned char bit_num,unsigned char x_bit);//位读取
void set_bit(bool set_val, unsigned char bit_num,unsigned char x_bit);//位赋值
#endif

#endif


