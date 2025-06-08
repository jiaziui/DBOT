#include "robot_machine_driver/robot_machine_driver.h"

FSUS_Protocol protocol(SERVO_PORT_NAME,FSUS_DEFAULT_BAUDRATE);//串口协议初始化
vector<FSUS_Servo> servos;

RobotMachineDriver robot_machine_driver;
robot_imu_data imu_date; //IMU数据结构体
servo_driver servo_data; //舵机数据结构体
robot_balance_param balance_param; //平衡参数结构体
dbot_machine_msg Dbot_msg; //机器人控制msg结构体

ros::Subscriber sub_imu;
ros::Subscriber sub_debug;
ros::Subscriber sub_ctl;
ros::Subscriber sub_machine_msg;

ros::Publisher pub_state;

robot_manager::robot_state state_msg; //机器人状态消息

int main(int argc, char **argv)
{ 
    servos.reserve(robot_servo_num);
    ros::init(argc, argv, "robot_machine_driver"); //ROS initializes and sets the node name //ROS初始化 并设置节点名称 
    ros::NodeHandle n;

    signal(SIGINT, sigintHandler);

    init(); //初始化

    sub_imu = n.subscribe("/imu_data", 10, imu_callback); //订阅imu数据
    sub_debug = n.subscribe("/robot_debug_param", 10, debug_callback); //订阅debug数据
    sub_ctl = n.subscribe("/robot_control", 10, ctl_callback); //订阅控制参数
    sub_machine_msg = n.subscribe("/robot_machine", 10, machine_msg_callback); //订阅机器人控制消息
    pub_state = n.advertise<robot_manager::robot_state>("/robot_state", 10); //发布机器人状态

    ros::Rate loop_rate(100); //设置循环频率
    while(ros::ok())
    {   
        walk(); 
        joint_angle_limit(); 
        robot_servo_refesh(); 
      //  cout<<"robot_control:"<<robot_control<<endl;

        //  if(msg_i++>=robot_msg_frequency){
        //      msg_i=0;
        //      state_msg.robot_driver_state = 1;
        //      state_msg.robot_state = robot_balance_flag; 
        //      state_msg.robot_electricity = 80;
        //      state_msg.robot_camera_state = 1;

        //      pub_state.publish(state_msg);
        // //     read_servo_msg();
        //  }
        ros::spinOnce();//ROS消息处理
        loop_rate.sleep();
    }   

}
//发布

void Robot_system(void)
{
    //参数读取
    //Publisher,发布机器人状态，电压

    //Subscriber,订阅imu节点
    //服务（控制参数）
}

void init(void)
{
    servo_init();//舵机初始化
    joint_param_init();//设置转速，功率
    read_servo_msg(); //读取舵机角度

    robot_balance_init();//平衡参数初始化
    
}

void servo_init(void)
{
    for (int i = 0; i < robot_servo_num; i++) {
        servos.emplace_back(i, &protocol);
    }
}

void joint_angle_init(void)
{
    for(int i =0;i<robot_servo_num;i++)
    {
        servos[i].setRawAngle(servo_data.target_angle[i]-servo_data.server_angle_offset[i],2000,set_run_init_power);
        servo_data.joint_flag[i] = 0;
    }
    return;

}

void joint_param_init(void)
{
    //初始角度
    for(int i =0;i<robot_servo_num;i++)
    {
        servo_data.target_angle[i] = servo_data.robot_init_angle[i];
        servo_data.joint_flag[i] = 1;
    }

    //各种数据
    msg_i =0;

    //角度校准参数
    balance_param.ipb = 0;
    balance_param.irb = 0;
    balance_param.ira = 0;
    balance_param.ipa = 0;
    balance_param.ip = 0;
    balance_param.ir = 0;
    balance_param.robot_roll_offset = 0;
    balance_param.robot_pitch_offset = 0;
    balance_param.robot_gx_offset = 0;
    balance_param.robot_gy_offset = 0;
}


void read_servo_msg(void)
{
    uint8_t status;
    for(int i =0;i<robot_servo_num-6;i++)
    {
        status =0;
        // 读取工作状态数据
    /*
        BIT[0] - 执行指令置1，执行完成后清零。
        BIT[1] - 执行指令错误置1，在下次正确执行后清零。
        BIT[2] - 堵转错误置1，解除堵转后清零。
        BIT[3] - 电压过高置1，电压恢复正常后清零。
        BIT[4] - 电压过低置1，电压恢复正常后清零。
        BIT[5] - 电流错误置1，电流恢复正常后清零。
        BIT[6] - 功率错误置1，功率恢复正常后清零。
        BIT[7] - 温度错误置1，温度恢复正常后清零。
    */
        status = servos[i].queryStatus();
        bool bitValue = bitRead(status, 4);
         if (bitValue)
        {
            cout<<"robot_voltage_low"<<endl;
            return;
         }
        //  bitValue = bitRead(status, 7);
        // {
        //     cout<<"robot_temperature_error"<<endl;
        //     return;
        // }
         servo_data.current_angle[i] = servos[i].queryAngle() + servo_data.server_angle_offset[i];
         
         int temperature = servos[i].queryTemperature();
         float tem = 1 / (log(temperature / (4096.0f - temperature)) / 3435.0f + 1 / (273.15 + 25)) - 273.15;  
         robot_machine_driver.servo_param_data.servo_tempterature[i] = tem;
         robot_machine_driver.servo_param_data.servo_current[i] = servos[i].queryCurrent();
         
         #ifdef robot_msg_debug
            cout << "Servo" << i << "angle: " <<servo_data.current_angle[i] << endl;
            cout << "Servo" << i << " temperature: " << tem << endl;
            cout << "Servo" << i << " current: " << robot_machine_driver.servo_param_data.servo_current[i] << "mA"<<endl;//mv
         #endif

    }

    int voltage = servos[robot_servo_num-7].queryVoltage();
    robot_machine_driver.servo_param_data.servo_voltage = (float)(8400-voltage)/2400*100;//转换百分比

    #ifdef robot_msg_debug 
        cout << "Servo voltage: " << robot_machine_driver.servo_param_data.servo_voltage << "%" << endl;
    #endif

    return;
}

bool bitRead(uint8_t value, uint8_t bit)
{
    return (value >> bit) & 0x01;
}   





void robot_all_joint(float x0, float y0, float x1, float y1, int s){

    static float k1;
    static float k2;
    static bool loin_flag = true;

    // static float left_leg_hight = robot_inital_height;
    // static float right_leg_hight = robot_inital_height;

    static int balance_flag = 0;


	if(s==1){
            if(robot_fwct<robot_landF && robot_control ==robot_control_turn_left && turn_lift_flag == 0 && supportleg == 1)
            {
                turn_lift_flag = 1;
                loin_count = 1;
            }
            
            if(robot_fwct<robot_landF && robot_control ==robot_control_turn_right && turn_right_flag == 0 && supportleg == 0)
            {
                turn_right_flag = 1;
                loin_count = 1;
            }



            if(turn_right_flag||turn_lift_flag)
            {
                if((robot_fwct<=(robot_fwctEnd-robot_landF-robot_landB)/2+ robot_landF && robot_fwct>=robot_landF) && loin_flag == false ) 
                {
                    loin_count *= -1;
                    loin_flag =true;
                }


                if(robot_fwct<robot_landF && loin_flag == true)
                loin_flag =false;
    
                if(loin_count == 1 && robot_fwct>robot_landF && robot_fwct<=(robot_fwctEnd-robot_landF-robot_landB)/2+ robot_landF)
                {   
                    k1 = loin_turn_angle * sin( M_PI*(robot_fwct-robot_landF)/(robot_fwctEnd-(robot_landF+robot_landB)));
                    if(k1<0) k1=0;
                    k2 = -k1;
                }
                else if (loin_count == -1 && robot_fwct>robot_landF && robot_fwct<=(robot_fwctEnd-robot_landF-robot_landB)/2+ robot_landF)
                {
                    k1 = loin_turn_angle * cos( M_PI*(robot_fwct-robot_landF)/(robot_fwctEnd-(robot_landF+robot_landB)));
                    
                    if(k1<0) k1=0;
                    k2= -k1;
                }
            }
            #ifdef robot_msg_debug
            cout<<"k1:"<<k1<<endl;
            cout<<"k2:"<<k2<<endl;
            #endif


            if((robot_control == robot_control_turn_right ||robot_control == robot_control_turn_left) &&  (turn_right_flag == 1||turn_lift_flag == 1))//右转
            {
                servo_data.target_angle[6] = k1;
                servo_data.joint_flag[6] = 1;
                servo_data.target_angle[4] = k2;
                servo_data.joint_flag[4] = 1;
            }
            else 
            {
                turn_right_flag = 0;
                turn_lift_flag = 0;
            }
        }
        else if(s==2 && dbot_mode == 1)
        {
            if(dbot_msg_flag[1] == 1)
                dbot_rool_date_analysis();

            robot_balance_run();

            roll_stab +=  balance_param.robot_roll_compensation_value;
            if(roll_stab > roll_stab_MAX)
            roll_stab = roll_stab_MAX;
            else if(roll_stab < roll_stab_MIN)
            roll_stab = roll_stab_MIN;

            servo_data.robot_foot_angle -= balance_param.robot_pitch_compensation_value;

            if(servo_data.robot_foot_angle > robot_foot_angle_MAX)
            servo_data.robot_foot_angle = robot_foot_angle_MAX;
            else if(servo_data.robot_foot_angle < robot_foot_angle_MIN)
            servo_data.robot_foot_angle = robot_foot_angle_MIN;

            servo_data.target_angle[0] = servo_data.robot_foot_angle;
             servo_data.joint_flag[0] = 1;
             servo_data.target_angle[10] = -servo_data.robot_foot_angle;
             servo_data.joint_flag[10] = 1;

        
            if(balance_flag != 1)
            balance_flag  = 1;
        }

        if((s!=2 && balance_flag == 1) || dbot_mode == 0)
        {
            balance_flag = 0;
            robot_balance_init();
            servo_data.robot_foot_angle = 0;
            servo_data.target_angle[0] = servo_data.robot_foot_angle;
            servo_data.joint_flag[0] = 1;
            servo_data.target_angle[10] = -servo_data.robot_foot_angle;
            servo_data.joint_flag[10] = 1;
            roll_stab = 0;
        }

        if(supportleg==0)
        {
            robot_joint_leg( x0-robot_swx_l, y0, robot_inital_height - roll_stab,0 );//支撑腿
            robot_joint_leg( x0-robot_swx_r, y0, robot_inital_height - robot_fh + roll_stab,1 );
        }
        else
        {
            robot_joint_leg( x0-robot_swx_l, y0, robot_inital_height - robot_fh - roll_stab , 0 );
            robot_joint_leg( x0-robot_swx_r, y0, robot_inital_height + roll_stab,1 );
        }
}



void  robot_all_joint1(int s){
	if(supportleg==0)	robot_all_joint(0, robot_swy,  0, 0 ,s );
	else			robot_all_joint( 0,robot_swy, 0, 0 ,s );
}



bool robot_joint_leg(float xx,float yy,float zz,int leg)
{
    /**
    * xx:中点为0的设置点前后方向距离（前+）
    * yy:中点为0的设置点左右方向距离（左+）
    * zz:中点为0的设置点z方向距离（上+）
    * leg:选择腿
    * 0:左前腿
    * 1:右前腿
    */

    float x,y,z;
    y= -yy;
    z= xx;
    x= zz;
    float k1, k2, k3;
    float theta1, theta2, theta3,theta2_1;

    theta1 = atan2(y,x);
    float _theta1_ = theta1 * 180 / M_PI;
	
	k1 = x*cos(theta1)+y*sin(theta1)-robot_leg_1;
	
	float c3_1 =k1*k1+z*z-robot_leg_3*robot_leg_3-robot_leg_2*robot_leg_2;
	float c3 =  c3_1/(2*robot_leg_2*robot_leg_3);
	
	if(c3<-1 || c3>1)
	{
        cout<<"无解,c3值超出范围"<<endl;
        return false;
	}
	theta3 = acos(c3);
    

	k3 = z;
	k2 = robot_leg_1-x*cos(theta1)-y*sin(theta1);
	float T1 = robot_leg_3*robot_leg_3*sin(theta3)*sin(theta3);
	float T_1 = sqrt(k2*k2+k3*k3-T1); 
	//theta2 = atan2(robot_leg_3*sin(theta3),T_1)-atan2(k3,k2); //去除无用解
	
	theta2_1 = atan2(robot_leg_3*sin(theta3),-T_1)-atan2(k3,k2); 
    
    if(z<0)
	theta2_1 = 2*M_PI-theta2_1;
	else
	theta2_1 = -theta2_1;
    float _theta2_ = theta2_1 * 180 / M_PI;
	float _theta3_ = theta3 * 180 / M_PI - ( theta2_1 * 180 / M_PI);

    #ifdef robot_joint_debug
    cout << "theta1: " << theta1/M_PI*180 << endl;
    cout << "theta2: " << theta2/M_PI*180 << endl;
    //cout << "theta2_1: " << theta2_1/M_PI*180 << endl;
    cout << "theta3: " << theta3/M_PI*180 << endl;

    cout << "换算过后的theta1: " << _theta1_ << endl;
    cout << "换算过后的theta2: " << _theta2_ << endl;
    cout << "换算过后的theta3: " << _theta3_ << endl;
    #endif

    if(leg == 0)
    {
        servo_data.target_angle[3]= _theta1_;
        servo_data.target_angle[2] = _theta2_;
        servo_data.target_angle[1] = _theta3_*-1;//极性改变
        servo_data.joint_flag[3] = 1;
        servo_data.joint_flag[2] = 1;
        servo_data.joint_flag[1] = 1;
    }
    else
    {
        servo_data.target_angle[7] = _theta1_; 
        servo_data.target_angle[8] = _theta2_*-1;//极性改变
        servo_data.target_angle[9] = _theta3_;
        servo_data.joint_flag[7] = 1;
        servo_data.joint_flag[8] = 1;
        servo_data.joint_flag[9] = 1;
    }
	return true;
}



#ifdef _set_leg_
bool robot_joint_leg1(float x,float z,int leg)
{
   /**
    * x:中点为0的设置点前后方向距离（前+）
    * z:中点为0的设置点z方向距离（上+）
    * s:选择腿
    * 0:左前腿
    * 1:右前腿
    */
    float k1, k2;
    float theta1;//关节弧度
    float theta2;

    // 计算 c2
    int c21 = x * x + z * z - robot_leg_2 * robot_leg_2 - robot_leg_3 * robot_leg_3;
    float c2 = (float)c21/(2 * robot_leg_2 * robot_leg_3);
    
    if (c2 >=1 || c2 <=-1) {
        #ifdef robot_joint_debug
        cout<<"无解,c2值超出范围"<<endl;
        #endif
        return false;
    }

    theta2 = acos(c2);   
    k1 = robot_leg_2 + robot_leg_3 * c2;
    k2 = robot_leg_3 * sin(theta2);
    theta1 = atan2(z, x) - atan2(k2, k1);
    
    float _theta1_ = theta1 * 180 / M_PI;//角度换算
	float _theta2_ = theta2 * 180 / M_PI - (180 - theta1 * 180 / M_PI);
	    
    // 舵目标机角度设置 
    if(leg == 0)
    {
        servo_data.target_angle[2] = _theta1_;
        servo_data.joint_flag[2] = 1;
        servo_data.target_angle[1] = _theta2_;
        servo_data.joint_flag[1] = 1;
    }
    else
    {
        servo_data.target_angle[8] = _theta1_;
        servo_data.joint_flag[8] = 1;
        servo_data.target_angle[9] = _theta2_;
        servo_data.joint_flag[9] = 1;
    }
    return true;
}
#endif

void robot_servo_refesh(void)
{
    for(int i =0;i<robot_servo_num;i++)
    {
        if (servo_data.joint_flag[i] != 1)
            continue;
        servos[i].setRawAngle(servo_data.target_angle[i]-servo_data.server_angle_offset[i],10,servo_run_power);
        servo_data.joint_flag[i] = 0;
    }
}


void joint_angle_limit(void)
{
    for(int i =0;i<robot_servo_num;i++)
    {
        if(servo_data.target_angle[i] > servo_data.joint_limit_max[i])
        {
            servo_data.target_angle[i] = servo_data.joint_limit_max[i];
        }
        if(servo_data.target_angle[i] < servo_data.joint_limit_min[i])
        {
            servo_data.target_angle[i] = servo_data.joint_limit_min[i];
        }   
    }
    return;
}


void walk(void)
{
    

    switch(robot_sport_state)
    {
        case robot_start://初始化，重置

            joint_angle_init();//等待1.5s
            usleep(1500000);

          //数值初始化
          joint_param_init();

          robot_joint_leg(0,0,robot_inital_height,0);//左前腿
          robot_joint_leg(0,0,robot_inital_height,1);
          robot_sport_state = robot_imu_adjust;
          #ifdef robot_joint_debug
                cout<<"初始化完成！";
                cout<<"robot_sport_state:"<<robot_sport_state<<endl; 
          #endif
            break;
        case robot_imu_adjust://角度校准
        robot_angAdj();//角度校准
        if( balance_param.ip==100 ){
            // balance_param.robot_pitch_offset=balance_param.ipa/100;
            // balance_param.robot_roll_offset=balance_param.ira/100;
            // balance_param.robot_gx_offset = balance_param.igxa/100;
            // balance_param.robot_gy_offset = balance_param.igya/100;
            
            robot_sport_state=robot_control_stop;		//状态转变
            robot_control = robot_control_stop;

            #ifdef topic_debug
                cout<<"角度校准完成！";
                // cout<<"robot_sport_state:"<<robot_sport_state<<endl;
                // cout <<"robot_pitch_offset:"<<balance_param.robot_pitch_offset<<endl;
                // cout <<"robot_roll_offset:"<<balance_param.robot_roll_offset<<endl;
                printf("robot_pitch_offset:%f\n", balance_param.robot_pitch_offset);
                printf("robot_roll_offset:%.6f\n", balance_param.robot_roll_offset);
                printf("robot_gx_offset:%f\n",balance_param.robot_gx_offset);
                printf("robot_gy_offset%f\n",balance_param.robot_gy_offset);

                cout<<"***********************************************************"<<endl;

            #endif
        }

        robot_detAng();//全向跌倒检测
        
        break;
        case robot_control_stop://等待指令
        //imu_Continu_calibration();//持续校准
        robot_detAng();//监测是否跌倒
        robot_all_joint1(2);

        robot_status_switch(robot_control_stop);
       
        /*自平衡反馈检测*/
        // if(	fabs(imu_date.roll_angle)>15 || fabs(imu_date.pitch_angle)>15 )
        // {
        //     imu_date.roll_angle>0?supportleg=0:supportleg= 1;
        //     //找到开始支撑脚
        //     //转换状态，反馈自平衡
        //     robot_status_switch(14);
        //   // #ifdef robot_joint_debug //反馈调节模式
        //     cout << "roll："<< imu_date.roll_angle << " pitch："<< imu_date.pitch_angle << endl;
        //     cout << "supportleg:" <<supportleg<<endl;
        //     cout <<"mode_switch: "<< robot_sport_state <<"robot_feedback_regulation"<<endl;
        //     //#endif
        // }

        break;

        case robot_control_word://初始化启动开始执行步态

        robot_footUp();//抬腿
        robot_swCont();
        robot_all_joint1(0);
        counterCont();        
        robot_detAng();
        robot_status_switch(robot_control_word);
        break;
        case robot_control_forward://前进
        robot_footUp();
        robot_swCont();
        robot_swx_Cont();
        robot_all_joint1(0);
        counterCont();
        robot_detAng();
        robot_status_switch(robot_control_forward);
        break;
        case robot_control_backward://后退
        robot_footUp();
        robot_swCont();
        robot_swx_Cont();
        robot_all_joint1(0);
        counterCont();
        robot_detAng();
        robot_status_switch(robot_control_backward);
        break;
        case robot_control_turn_left://左转
        robot_footUp();
        robot_swCont();
        robot_all_joint1(1);
        counterCont();
        robot_detAng();
        robot_status_switch(robot_control_turn_left);
        break;
        case robot_control_turn_right://右转
        robot_footUp();
        robot_swCont();
        robot_all_joint1(1);
        counterCont();
        robot_detAng();
        robot_status_switch(robot_control_turn_right);
        break;
        case robot_control_move_left://左横向
        robot_detAng();
        robot_status_switch(robot_control_move_left);
        break;
        case robot_control_move_right://右横向


        robot_detAng();
        robot_status_switch(robot_control_move_right);
        break;
        case robot_status_switching:
        robot_sport_state = robot_control;

        cout<<"robot_status_switching:"<<robot_sport_state<<endl;

        cout<<"d等待切换!"<<endl;
        if(supportleg == 0 && robot_fwct == 0)
        {
            robot_sport_state = robot_control;
            cout<<"切换："<<endl;
        }
        else{
            robot_footUp();
            robot_swCont();
            robot_all_joint1(0);
            counterCont();
            if(supportleg == 0 && robot_fwct == 0)
            {
                robot_sport_state = robot_control;
                cout<<"切换："<<endl;
            }    
        }

        break;
        case robot_param_change:
        
        //参数数据解算
        date_analysis();
        /**
         * 计算对应参数
         * 参数修改，标志位拉起
         */
        if(dbot_msg_flag[0] == 1)
        {
            robot_joint_leg(0,0,robot_inital_height,0);
            robot_joint_leg(0,0,robot_inital_height,1);
        }
        // if(dbot_msg_flag[1] == 1)
        // {
        //     robot_joint_leg(0,0,robot_inital_height,0);
        //     robot_joint_leg(0,0,robot_inital_height,1);
        // }
        // if(dbot_msg_flag[2] == 1)
        // {
        //     robot_joint_leg(0,0,robot_inital_height,0);
        //     robot_joint_leg(0,0,robot_inital_height,1);
        // }
        robot_status_switch(robot_param_change);

        break;
        default://fault 重置

        robot_detAng();
            break;
    }
}

void robot_status_switch(int statu_praesens)
{
    if(robot_sport_state == robot_control_stop || robot_sport_state == robot_param_change )
    {
        robot_fwct = 0;
    }
    //cout<<"robot_fwct:"<<robot_fwct<<endl;
    if(robot_control != statu_praesens && robot_fwct == 0)
    {
        cout<<"----准备状态切换----"<<endl;
        robot_status_param_init();

        if(supportleg == 0)
            robot_sport_state = robot_control;//支撑腿状态切换
        else
            robot_sport_state = robot_status_switching;//等待支撑腿状态切换
        
        cout<<"robot_sport_state:"<<robot_sport_state<<endl;
    }
    else
    {
        #ifdef robot_control_debug
        cout<<"robot_control_flag:"<<robot_control<<endl;
        #endif
    }   

    
    return;
}

void robot_status_param_init(void)
{
    turn_lift_flag = 0;//开始标志位
    turn_right_flag = 0;
    loin_count = -1;

    robot_forword_flag = 0;
    robot_swx_l =0;
    robot_swx_r =0;
    robot_B_F_offset = 0;

    servo_data.target_angle[0] = 0;
    servo_data.target_angle[4] = 0;
    servo_data.target_angle[6] = 0;
    servo_data.target_angle[10] = 0;

    servo_data.joint_flag[4] = 1;
    servo_data.joint_flag[6] = 1;
    servo_data.joint_flag[0] = 1;
    servo_data.joint_flag[10] = 1;
    return;
}


void imu_Continu_calibration(void)
{
    if( balance_param.ip>=20 ){//持续校准
        balance_param.ip=0;
        if(imu_date.roll_angle >0) balance_param.robot_roll_offset+=0.01;
        if(imu_date.roll_angle <0) balance_param.robot_roll_offset-=0.01;
        if(imu_date.pitch_angle>0) balance_param.robot_pitch_offset+=0.01;
        if(imu_date.pitch_angle<0) balance_param.robot_pitch_offset-=0.01;

        #ifdef robot_joint_debug
            cout <<"robot_pitch_offset:"<<balance_param.robot_pitch_offset<<endl;
            cout <<"robot_roll_offset:"<<balance_param.robot_roll_offset<<endl;
        #endif
    }
    else ++balance_param.ip;
}


void robot_angAdj(void)
{
    if( imu_date.pitch_angle<=balance_param.ipb+1 && imu_date.pitch_angle>=balance_param.ipb-1 &&
		imu_date.roll_angle <=balance_param.irb+1 && imu_date.roll_angle >=balance_param.irb-1 	){//超出范围,积分
		++balance_param.ip;
		balance_param.ipa+=imu_date.pitch_angle;
		balance_param.ira+=imu_date.roll_angle;
        balance_param.igxa+=imu_date.gyros_x_data;
        balance_param.igya+=imu_date.gyros_y_data;

	}
	else {
		balance_param.ip=0;
		balance_param.ipa=0;
		balance_param.ira=0;
	}
	balance_param.ipb=imu_date.pitch_angle;
	balance_param.irb=imu_date.roll_angle;

}


void robot_detAng(void)
{
    
        if( 30>fabs(imu_date.pitch_angle) && 30>fabs(imu_date.roll_angle) ) return;//跌倒检测
        robot_balance_flag = 0;
        
        #ifdef robot_joint_debug
        cout<<"pitch_angle:"<<imu_date.pitch_angle<<endl;
        cout<<"roll_angle:"<<imu_date.roll_angle<<endl;
        cout<<"跌倒!!!"<<endl;
        #endif

        //设置所有舵机为阻尼模式,摔倒反馈
        for(int i =0;i<robot_servo_num;i++)
        {
        servos[i].setDamping(set_Damping_power);
        }

        while(ros::ok()){ 
            ros::spinOnce();
            //loop_rate.sleep();
             if (30>fabs(imu_date.pitch_angle) && 30>fabs(imu_date.roll_angle))//角度检测重置
             {
                dbot_mode = 0;
                 #ifdef robot_control_debug
                 if(msg_i++>=robot_msg_frequency)
                 {
                    msg_i=0;
                    state_msg.robot_driver_state = 1;
                    state_msg.robot_state = robot_balance_flag; 
                    state_msg.robot_electricity = 80;
                    state_msg.robot_camera_state = 1;
       
                    pub_state.publish(state_msg);
               //     read_servo_msg();
                }
                #endif
                #ifdef _dbug_msg
                cout<<"***************robot***************等待重启..."<<endl;
                #endif
                }             
                else 
                {
                    if(robot_control == 0)
                    {
                        #ifdef _dbug_msg
                        cout<<"***************robot***************重启..."<<endl;
                        #endif
                        break;
                    }
                }

        }
}


void imu_callback(const robot_manager::imu_date::ConstPtr &msg)
{
    //处理imu数据
    imu_date.accele_x_data = msg->ax;
    imu_date.accele_y_data = msg->ay;
    imu_date.accele_z_data = msg->az;
    imu_date.gyros_x_data = msg->gx;
    imu_date.gyros_y_data = msg->gy;
    imu_date.gyros_z_data = msg->gz;

    imu_date.accele_x_data -= balance_param.robot_gx_offset;
    imu_date.accele_y_data -= balance_param.robot_gy_offset;

    imu_date.pitch_angle = msg->roll;//角度
    imu_date.roll_angle = msg->pitch;
    imu_date.yaw_angle = msg->yaw;

    imu_date.roll_angle -= balance_param.robot_roll_offset;//角度校准
    imu_date.pitch_angle -= balance_param.robot_pitch_offset;

    imu_date.yaws = imu_date.yaw_angle  *M_PI / 180;//转弧度制
    imu_date.pitchs = imu_date.pitch_angle  *M_PI / 180;
    imu_date.rolls = imu_date.roll_angle *M_PI / 180;

    #ifdef robot_msg_debug
        cout << "accele_x_data: " << imu_date.accele_x_data << endl;
        cout << "accele_y_data: " << imu_date.accele_y_data << endl;
        cout << "accele_z_data: " << imu_date.accele_z_data << endl;
        cout << "gyros_x_data: " << imu_date.gyros_x_data << endl;
        cout << "gyros_y_data: " << imu_date.gyros_y_data << endl;
        cout << "gyros_z_data: " << imu_date.gyros_z_data << endl;
        cout << "yaw_angle: " << imu_date.yaw_angle << endl;
        cout << "pitch_angle: " << imu_date.pitch_angle << endl;
        cout << "roll_angle: " << imu_date.roll_angle << endl;
    #endif
    //read_servo_msg();
}

void debug_callback(const robot_manager::robot_debug::ConstPtr &msg)
{
    //robot_fwctEnd = msg->robot_fwctEnd;
    //servo_run_power = msg->servo_run_power;
    //robot_landF = msg->robot_landF;
    //robot_landB = msg->robot_landB;
    //robot_swMax = msg->robot_swMax;//mm
    //robot_sport_state = msg->robot_sport_state;
    //robot_fwctUp = msg->robot_fwctUp;  

    robot_fhMax = msg->robot_fhMax;//mm
    robot_control = msg->robot_control;

    #ifdef robot_msg_debug
    cout<<"debug_msg_success!"<<endl;
    cout<<"robot_fwctEnd:"<<servo_run_power<<endl;
    cout<<"robot_landF:"<<robot_landF<<endl;
    cout<<"robot_landB:"<<robot_landB<<endl;
    cout<<"robot_fhMax:"<<robot_fhMax<<endl;
    cout<<"robot_fwctEnd:"<<robot_fwctEnd<<endl;
    cout<<"robot_swMax:"<<robot_swMax<<endl;
    cout<<"robot_sport_state:"<<robot_sport_state<<endl;
    cout<<"robot_fwctUp:"<<robot_fwctUp<<endl;
    #endif
}

void ctl_callback(const robot_manager::robot_control::ConstPtr &msg)
{
    robot_control = msg->robot_control_date;

    #ifdef topic_debug
    cout<<"robot_control:"<<robot_control<<endl;
    #endif
}

void robot_footUp(void)
{
    if( robot_fwct>robot_landF && robot_fwct<=(robot_fwctEnd-robot_landB) ) robot_fh = robot_fhMax * sin( M_PI*(robot_fwct-robot_landF)/(robot_fwctEnd-(robot_landF+robot_landB)) );
	else	robot_fh = 0;
    //cout<<robot_fwct<<"robot_fh:"<<robot_fh<<endl;
}

void counterCont(void)
{
    if(robot_fwct>=robot_fwctEnd){	
		supportleg^=1;//状态转变,^1取反相同为0，不同为1	
		robot_fwct=0;
		robot_fh=0;
	}
	else{
		robot_fwct+=robot_fwctUp;
		if(robot_fwct>robot_fwctEnd) robot_fwct=robot_fwctEnd;
	}

}

void robot_swCont(void)
{
    float k=robot_swMax*sinf(M_PI*robot_fwct/robot_fwctEnd);
    if (k<0) k=0;
    if(supportleg) robot_swy = -k;
    else robot_swy = k;

    #ifdef robot_joint_debug
    cout<<"robot_swCont:"<<robot_swy<<endl;
    #endif

}

void robot_swx_Cont(void)
{
    static float k1,k2;//跨步，支撑


    if( supportleg == 1 && robot_forword_flag == 0)
    {
        robot_forword_flag = 1;
        
        }
        if((robot_B_F_offset+=0.8)<robot_B_F_offset_Max)
        {
            if(robot_control == 4)
            {
                servo_data.target_angle[0] =robot_B_F_offset;
                servo_data.joint_flag[0] = 1;
                servo_data.target_angle[10] = -robot_B_F_offset;
                servo_data.joint_flag[10] = 1;
            }
            else if(robot_control == 5)
            {
                servo_data.target_angle[0] = -robot_B_F_offset;
                servo_data.joint_flag[0] = 1;
                servo_data.target_angle[10] = robot_B_F_offset;
                servo_data.joint_flag[10] = 1;
            }
    }
        
        

    if(robot_fwct>robot_landF && robot_fwct<=(robot_fwctEnd-robot_landB))
    {   

        k1 = robot_swx_max * sin( M_PI*(robot_fwct-robot_landF)/(robot_fwctEnd-(robot_landF+robot_landB))-M_PI/2);
        if(robot_control == 5) k1 = -k1;
        k2 = -k1;
        
        if(robot_forword_flag == 0 && supportleg == 0)
        {
            robot_swx_l = 0;
            robot_swx_r = k1;
        }
        else if(robot_forword_flag == 1 && supportleg == 0)
        {
            robot_swx_l = k2;
            robot_swx_r = k1;
        }
        else if(robot_forword_flag == 1 && supportleg == 1)
        {
            robot_swx_l = k1;
            robot_swx_r = k2;
        }
    
    }
}

    
void robot_balance_init(void)//机器人平衡初始化,主要是PID参数初始化
{
    balance_param.kp_leg = 0.01;//根据腿高实现开环调整

    balance_param.kp_roll = 0.0205;//0.0205
    balance_param.kd_roll = 0.00095;//0.00095

    balance_param.kd_pitch = 0;//
    balance_param.kp_pitch = 0;//0.0277
    balance_param.robot_roll_compensation_value = 0;
    balance_param.robot_pitch_compensation_value = 0;

}

void robot_balance_run(void)//机器人平衡运行，开环PID控制
{
    float roll_output,pitch_output;
    float roll_error,pitch_error;

    roll_error = imu_date.roll_angle - balance_param.ira;
    pitch_error = imu_date.pitch_angle - balance_param.ipa;


    roll_output = balance_param.kp_roll * robot_roll_offset_get() - balance_param.kd_roll * imu_date.gyros_y_data;// + balance_param.kd_roll * (roll_error - balance_param.ira) ;
    pitch_output = balance_param.kp_pitch * robot_pitch_offset_get() - balance_param.kd_pitch *imu_date.gyros_y_data ;

     if(roll_output>1) roll_output=1;//增量使PID增益稳定，防止过度增益
     if(roll_output<-1) roll_output=-1;

     if(pitch_output>1) pitch_output=1;
     if(pitch_output<-1) pitch_output=-1;
    
    balance_param.robot_roll_compensation_value = roll_output;
    balance_param.robot_pitch_compensation_value = pitch_output;

    // servo_data.target_angle[4] = -roll_output*180/M_PI;
    // servo_data.joint_flag[4] = 1;
    // servo_data.target_angle[6] = pitch_output*180/M_PI;
    // servo_data.joint_flag[6] = 1;
    
    #ifdef robot_joint_debug
    cout<<"roll_output:"<<roll_output<<endl;
    cout<<"pitch:"<<imu_date.pitch_angle<<endl;
    cout<<"pitch_output:"<<pitch_output<<endl;
    cout<<"roll_error:"<<roll_error<<endl;
    cout<<"pitch_error:"<<pitch_error<<endl;
    cout<<"roll_output:"<<roll_output<<endl;
    cout<<"pitch_output:"<<pitch_output<<endl;
    #endif
}


float robot_roll_offset_get(void)//roll偏差获取函数，推算横滚(roll)的高度偏差
{
    int   k = 1;
    float k1;
    float k2;
    // if(imu_date.rolls <0)
    // {
    //     k = -1;
    //     k1 = -imu_date.rolls;
    // }
    k2 = robot_Span_width * tan(imu_date.rolls - dbot_roll_angle/180*M_PI);
    return k2;
}

float robot_pitch_offset_get(void)//pitch偏差获取函数
{
    return -imu_date.pitch_angle;
}

float robot_roll_compensation_value(void)//roll补偿值获取函数
{
    return -balance_param.robot_roll_compensation_value;  
}
float robot_pitch_compensation_value(void)//pitch补偿值获取函数，推算前后俯仰(pitch)的角度补偿值
{
    return -balance_param.robot_pitch_compensation_value; 
}


void sigintHandler(int sig) 
{
    ROS_INFO("robot_machine_driver shutting down...");
    ros::shutdown();
}


void machine_msg_callback(const robot_manager::robot_machine::ConstPtr &msg)
{
    /*
    typedef struct Dbot_machine_msg{
    dbot_h = 0;
    dbot_roll = 0;
    dbot_p = 0;
    dbot_m = 0;
    dbot_ctl = 0;
    dbot_act = 0;
    }dbot_machine_msg;
    */
    static int dbot_h_old = 173;
    static int dbot_roll_old = 0;
    static int dbot_p_old = 25;

    static unsigned char dbot_m_old = 0;
    static int dbot_ctl_old = 2;

    if(msg->dbot_ctl == 0)
    {
        robot_inital_height = 173;
        #ifdef _dbug_msg
        cout<<"复位！"<<endl;
        #endif

        Dbot_msg.dbot_m = 0;//模式
        //Dbot_msg.dbot_p = msg->dbot_p;//目标周期
        Dbot_msg.dbot_ctl = 2;//控制目标
        Dbot_msg.dbot_roll = 0;//目标姿态
        Dbot_msg.dbot_h = robot_inital_height;//目标高度
        Dbot_msg.dbot_act = msg->dbot_act;//目标动作执行
        dbot_ctl_old = 2;
        robot_control = 0;
        dbot_h_old = robot_inital_height;
        dbot_p_old = 25;
        dbot_roll_old = 0;
        dbot_m_old = 0;

        for(int i=0;i<3;i++)
        {
            dbot_msg_flag[i] = 0;
        }
        

    }
    else{
    if(dbot_msg_flag[0] != 1 && dbot_msg_flag[1] != 1)
    {
        Dbot_msg.dbot_m = msg->dbot_m;//模式
        Dbot_msg.dbot_p = msg->dbot_p;//目标周期
        Dbot_msg.dbot_ctl = msg->dbot_ctl;//控制目标
        Dbot_msg.dbot_roll = msg->dbot_roll;//目标姿态
        Dbot_msg.dbot_h = msg->dbot_h;//目标高度
        Dbot_msg.dbot_act = msg->dbot_act;//目标动作执行


    if(dbot_h_old != Dbot_msg.dbot_h)
    {
        robot_control = robot_param_change;

        dbot_h_old = Dbot_msg.dbot_h;
        //高度变化标志位h
        dbot_msg_flag[0] = 1;

        #ifdef _dbug_msg
            cout<<"dbot_msg_flag[0]:"<<dbot_msg_flag[0]<<endl;
        #endif
    }

     //ctl
    if(dbot_m_old!= Dbot_msg.dbot_m)
    {
        dbot_mode = Dbot_msg.dbot_m;
        if(dbot_m_old == 1)
        {
            robot_balance_init();
            roll_stab = 0;
            robot_control = 0;
        }
        dbot_m_old = Dbot_msg.dbot_m;
    }

    if(dbot_roll_old != Dbot_msg.dbot_roll && dbot_mode == 1)
    {
        dbot_roll_old = Dbot_msg.dbot_roll;
        //倾斜角标志位
        dbot_msg_flag[1] = 1;
        
        #ifdef _dbug_msg
            cout<<"dbot_msg_flag[1]:"<<dbot_msg_flag[1]<<endl;
        #endif
    }

    if(dbot_p_old != Dbot_msg.dbot_p)
    {

        //robot_control = robot_param_change;
        dbot_p_old = Dbot_msg.dbot_p;
        robot_fwctUp = Dbot_msg.dbot_p;

        //周期变化标志位
        // dbot_msg_flag[2] = 1;
        // #ifdef topic_debug
        //     cout<<"dbot_msg_flag[2]:"<<dbot_msg_flag[2]<<endl;
        // #endif
    }


    if(dbot_mode == 0)
    {
        if(dbot_ctl_old != Dbot_msg.dbot_ctl)
        {
            robot_control = Dbot_msg.dbot_ctl;
            dbot_ctl_old = Dbot_msg.dbot_ctl;

            #ifdef _dbug_msg
            cout<<"robot_control:"<<robot_control<<endl;
            #endif

            if(robot_control == 3)
                robot_fhMax = 20;
            else if(robot_control == 4)
                robot_fhMax = 25;
            else if(robot_control == 5)
                robot_fhMax = 25;
            else if(robot_control == 6)
                robot_fhMax = 20;
            else if(robot_control == 7)
                robot_fhMax = 20;
            else
                robot_fhMax = 20;
        }
    }
    else
    {
        robot_control = 2;
    }
    
        #ifdef topic_debug
        cout<<"dbot_h:"<<Dbot_msg.dbot_h<<endl;
        cout<<"dbot_roll:"<<Dbot_msg.dbot_roll<<endl;
        cout<<"dbot_p:"<<Dbot_msg.dbot_p<<endl;
        cout<<"dbot_m:"<<Dbot_msg.dbot_m<<endl;
        cout<<"dbot_ctl:"<<Dbot_msg.dbot_ctl<<endl;
        cout<<"dbot_act:"<<Dbot_msg.dbot_act<<endl;
        #endif 
    }

    }
}

void date_analysis(void)
{
    /****************Data analysis********************/  
        if(dbot_msg_flag[0] == 1)
        {
            /*高度变化处理*/
            if(robot_inital_height<Dbot_msg.dbot_h)
            {
                robot_inital_height += 0.08;
                if(robot_inital_height > Dbot_msg.dbot_h)
                robot_inital_height = Dbot_msg.dbot_h;
            }
            else if(robot_inital_height>Dbot_msg.dbot_h)
            {
                robot_inital_height -= 0.08;
                if(robot_inital_height < Dbot_msg.dbot_h)
                robot_inital_height = Dbot_msg.dbot_h;
            }
            
            #ifdef _dbug_msg
            cout << "robot_inital_height:" << robot_inital_height << endl;
            #endif

            if(robot_inital_height >= Dbot_msg.dbot_h - 1 && robot_inital_height <= Dbot_msg.dbot_h)
            {
                robot_inital_height = Dbot_msg.dbot_h;
                dbot_msg_flag[0] = 0;//高度变化标志位清零
                robot_control = 2;
            }
            
        }

        // if(dbot_msg_flag[2] == 1)
        // {
        //     /*周期变换*/
        //     robot_fwctEnd = Dbot_msg.dbot_p;
        //     dbot_msg_flag[2] = 0;//周期变化标志位清零
            
        // }
        //动作参数执行，主要负责动作模型的复现执行
}



#ifdef _bit_opr
void set_bit(bool set_val, unsigned char bit_num,unsigned char x_bit)
{
    if(set_val) x_bit |= (1 << bit_num);
    else x_bit &= ~(1 << bit_num);
    return;
}

bool get_bit(unsigned char bit_num,unsigned char x_bit)
{
    return (x_bit >> bit_num) & 0x01;
}
#endif

void dbot_mot_ii(int date_1,int date_2,int motCt)
{
    //参数 int date_1：当前位置 int data_2：目标位置
	if(motCt--<1) date_1 = date_2;
	else date_1 += (date_2-date_1)/motCt;
    return;

}

void dbot_mot_if(int date_1,float date_2,int motCt)
{
    //参数 int date_1：当前位置 int data_2：目标位置
	if(motCt--<1) date_1 = date_2;
	else date_1 += (date_2-date_1)/motCt;
    return;
}

void dbot_mot_fi(float date_1,int date_2,int motCt)
{
    //参数 int date_1：当前位置 int data_2：目标位置
	if(motCt--<1) date_1 = date_2;
	else date_1 += (date_2-date_1)/motCt;
    return;
}

void dbot_mot_ff(float date_1,float date_2,int motCt)
{
    //参数 float date_1：当前位置 float data_2：目标位置
	if(motCt--<1) date_1 = date_2;
	else date_1 += (date_2-date_1)/motCt;
    return;
}


void dbot_rool_date_analysis(void)
{
    //cout<<"robot_control:"<<robot_control<<endl;

            /*姿态变化处理*/
        // dbot_roll_angle+=0.01;
        // if(dbot_roll_angle >= Dbot_msg.dbot_roll)
        // {
        //     dbot_roll_angle = Dbot_msg.dbot_roll;
        //     dbot_msg_flag[1] = 0;//姿态变化标志位清零
        //     robot_control = 2;
        // }

        if(dbot_roll_angle<Dbot_msg.dbot_roll)
        {
            dbot_roll_angle += 0.008;
            if(dbot_roll_angle > Dbot_msg.dbot_roll)
                dbot_roll_angle = Dbot_msg.dbot_roll;
        }
        else if(dbot_roll_angle>Dbot_msg.dbot_roll)
        {
            dbot_roll_angle -= 0.008;
            if(dbot_roll_angle < Dbot_msg.dbot_roll)
            dbot_roll_angle = Dbot_msg.dbot_roll;
        }
        
        #ifdef _dbug_msg
        cout << "dbot_roll_angle:" << dbot_roll_angle << endl;
        #endif

        if(dbot_roll_angle >= Dbot_msg.dbot_roll - 0.5 && dbot_roll_angle <= Dbot_msg.dbot_roll + 0.5)
        {
            dbot_roll_angle = Dbot_msg.dbot_roll;
            dbot_msg_flag[1] = 0;//姿态变化标志位清零
            robot_control = 2;
            #ifdef _dbug_msg
            cout<<"抵达目标值"<<endl;
            #endif
        }
}  

