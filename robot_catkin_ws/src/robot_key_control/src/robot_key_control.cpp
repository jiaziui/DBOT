#include <termios.h>
#include <unistd.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ros/ros.h>
#include "robot_manager/robot_debug.h"
#include <iostream>



using namespace std;

int  robot_fwctEnd = 1000;
int servo_run_power = 10000;
int robot_landF =325;
int robot_landB =350;
int robot_fhMax = 22;//mm
int robot_swMax = 11;//mm
int robot_sport_state = 2;
int robot_fwctUp = 25;
int robot_control = 2;

// 定义按键码
#define KEYCODE_W 0x77
#define KEYCODE_A 0x61
#define KEYCODE_S 0x73
#define KEYCODE_D 0x64
#define KEYCODE_Q 0x71 // 退出键

// 终端原始模式设置
void setTerminalToRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    // 禁用规范模式和回显
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// 恢复终端默认设置
void restoreTerminalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    // 恢复规范模式和回显
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}




// 主函数
int main(int argc, char** argv) {

    ros::init(argc, argv, "robot_key_control");
    ros::NodeHandle n;
    ros::Publisher robot_pub = n.advertise<robot_manager::robot_debug>("/robot_debug_param", 10);

    robot_manager::robot_debug robot_msg;
    robot_msg.robot_control = 2;
    robot_msg.robot_fwctEnd = robot_fwctEnd;
    robot_msg.servo_run_power = servo_run_power;
    robot_msg.robot_landF =robot_landF;
    robot_msg.robot_landB =robot_landB;
    robot_msg.robot_fhMax = robot_fhMax;
    robot_msg.robot_swMax = robot_swMax;
    robot_msg.robot_sport_state = robot_sport_state;
    robot_msg.robot_fwctUp = robot_fwctUp;
   

    char c= 'r';
    char c_old = c;
    bool running = true;

    // 设置终端为原始模式
    setTerminalToRawMode();

    // 提示信息
    printf("使用 WASD 控制,任意键启动，按 Q 退出。\n");

    // 使用 poll 监听键盘输入
    struct pollfd ufd;
    ufd.fd = STDIN_FILENO; // 标准输入
    ufd.events = POLLIN;   // 监听输入事件

    while (running) {
        int ret = poll(&ufd, 1, 100); // 100ms 超时

        if (ret > 0) {
            // 读取按键
            if (read(STDIN_FILENO, &c, 1) < 0) {
                perror("read()");
                break;
            }

            // 处理按键
            switch (c) {
                case KEYCODE_W:
                    printf("前进\n");
                    robot_control = 4;
                    // int robot_swMax = 13;//mm
                    robot_msg.robot_fhMax = 24;//mm
                    break;
                case KEYCODE_S:
                    printf("停止\n");
                    robot_control = 2;
                    robot_msg.robot_fhMax = 20;//mm
                    break;
                case KEYCODE_A:
                    printf("左转\n");
                    robot_control = 6;
                    robot_msg.robot_fhMax = 20;//mm
                    break;
                case KEYCODE_D:
                    printf("右转\n");
                    robot_control = 7;
                    robot_msg.robot_fhMax = 20;//mm

                    break;
                case KEYCODE_Q:
                    printf("退出程序\n");
                    robot_msg.robot_fhMax = 20;//mm
                    running = false;
                    break;
                default:
                    printf("未知按键，启动原地: %c\n", c);
                    robot_control = 3;
                    robot_msg.robot_fhMax = 20;//mm
                    break;
            }
        
        if(c != c_old)
        {
            c_old = c; 
            //发送数据
            robot_msg.robot_control = robot_control;

            robot_pub.publish(robot_msg);
        }
        
        } else if (ret < 0) {
            perror("poll()");
            break;
        }

        

    }

    // 恢复终端默认设置
    restoreTerminalMode();

    printf("程序结束。\n");
    return 0;
}