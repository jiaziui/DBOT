#include "robot_manager/robot_manager.h"

using namespace std;

dbot_msg Dbot_msg;


int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "robot_manager");
    
    n = new ros::NodeHandle();

    robot_control_pub = n->advertise<robot_manager::robot_control>("/robot_control", 10);
    robot_machine_pub = n->advertise<robot_manager::robot_machine>("/robot_machine", 10);
    robot_i2c_speak_pub = n->advertise<robot_manager::robot_i2c_speak>("/robot_i2c_speak", 10);
    //robot_socket_pub = n->advertise<ros_socket::socket>("/send_topic", 10);
    //robot_state_sub = n->subscribe("/robot_state", 10, &state_callback);
    //robot_socket_sub = n->subscribe("/recv_topic", 100, &socket_callback);

    signal(SIGINT, sigint_handler);
    struct ifaddrs *ifa = NULL;//保存网卡信息
    struct ifaddrs *ifap = NULL;//保存下一个网卡信息

    //获取网卡信息ip地址
    if (getifaddrs(&ifa) == -1) {
        perror("getifaddrs");
        //exit(EXI  T_FAILURE);
    }

    for (ifap = ifa; ifap != NULL; ifap = ifap->ifa_next) {
        if (ifap->ifa_addr->sa_family == AF_INET) {
            void *addr = &((struct sockaddr_in *)ifap->ifa_addr)->sin_addr;//保存ip地址
            inet_ntop(AF_INET, addr, host, INET_ADDRSTRLEN);//将ip地址转换为字符串，保存到host变量

            cout<<"ip address is :"<<addr<<endl;

            if(strcmp(host,"127.0.0.1")!=0){//排除本地地址
                cout<<"ip address is :"<<host<<endl;
                break;
            }
        }
    }
    // freeifaddrs(ifa);//释放内存
    // freeifaddrs(ifap);
    //cout<<"host:"<<host<<endl;
    // /web_video_server_1/address参数
    ros::param::set("/web_video_server_1/address", host);
    ros::param::set("/web_video_server_1/port", web_voice_port);
    //摄像头参数"http://192.168.137.231:33306/stream?topic=/usb_cam/image_raw"照片流
    //"http://192.168.137.231:33306/snapshot?topic=/usb_cam/image_raw"单张照片

    struct mosquitto *mosq = NULL;

    mosquitto_lib_init();//初始化libmosquitto库

    mosq = mosquitto_new(NULL,session,NULL);//创建mosquitto客户端,mosq为客户端句柄,session为是否开启会话,NULL为用户数据
    if(!mosq){
        
        cout<<"create client failed.."<<endl;
        mosquitto_lib_cleanup();
        return 1;
    }

    //mosquitto_log_callback_set(mosq, my_log_callback);
    mosquitto_connect_callback_set(mosq, my_connect_callback);
    mosquitto_message_callback_set(mosq, my_message_callback);//接收消息回调函数
    mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);//订阅回调函数

    if(mosquitto_connect(mosq, host, PORT, KEEP_ALIVE)){//连接服务器
    
        cout<<"connect server failed.."<<endl;
        return 1;
    }


    int loop = mosquitto_loop_start(mosq);//启动mosquitto循环
    if(loop != MOSQ_ERR_SUCCESS)//循环错误
    {
        cout<<"loop error"<<endl;
    }

    int ip_msg_i =0;    
//2.循环等待输入json字符串

    ros::Rate loop_rate(10); //设置循环频率

    
    while (ros::ok())
    {

        // if(ip_msg_i++>100) //10s发送一次ip地址
        // {
        //     ip_msg_i = 0;
        // cJSON *json = cJSON_CreateObject();
        // string cream_add = string("http://")+host+":33306/stream?topic=/usb_cam/image_raw";
        // cJSON_AddStringToObject(json, "robot_ip", host);
        // cJSON_AddStringToObject(json, "robot_cream_gain", cream_add.c_str());
        // cJSON_AddStringToObject(json, "robot_Picture_gain", cream_add.c_str());

        // char *json_string  = cJSON_Print(json);//将json数据转换为字符串
        // cJSON_Delete(json);//释放内存

        // mosquitto_publish(mosq,NULL,"lj_lth",strlen(json_string)+1,json_string,0,0);
        // memset(json_string,0,sizeof(json_string));
        // }

        ros::spinOnce(); //接收消息
        loop_rate.sleep(); 

    }
    
    mosquitto_destroy(mosq);//销毁mosquitto客户端
    mosquitto_lib_cleanup();//释放libmosquitto库资源
    }



    void date_parse(char *date) {    

        cJSON *json = cJSON_Parse(date);
        if (json == NULL) {
            fprintf(stderr, "Error before: [%s]\n", cJSON_GetErrorPtr());
            return ;
        }
        Dbot_msg.dbot_h = cJSON_GetObjectItem(json, "dbot_h")->valueint - 190;//腿部高度转换
        Dbot_msg.dbot_roll = cJSON_GetObjectItem(json, "dbot_roll")->valueint;
        Dbot_msg.dbot_p =10000 / cJSON_GetObjectItem(json, "dbot_p")->valueint;//周期参数转换1000*10
        Dbot_msg.dbot_m = cJSON_GetObjectItem(json, "dbot_m")->valueint;
        if(Dbot_msg.dbot_m == 1)
            Dbot_msg.dbot_itr = 4;    
        else
           Dbot_msg.dbot_itr = cJSON_GetObjectItem(json, "dbot_itr")->valueint;
        Dbot_msg.dbot_ctl = cJSON_GetObjectItem(json, "dbot_ctl")->valueint;
        Dbot_msg.dbot_act = cJSON_GetObjectItem(json, "dbot_act")->valueint;

        #ifdef _MQTT_DEBUG_
        cout<<"dbot_h:"<<Dbot_msg.dbot_h<<endl;
        cout<<"dbot_roll:"<<Dbot_msg.dbot_roll<<endl;
        cout<<"dbot_p:"<<Dbot_msg.dbot_p<<endl;
        cout<<"dbot_m:"<<Dbot_msg.dbot_m<<endl;
        cout<<"dbot_ctl:"<<Dbot_msg.dbot_ctl<<endl;
        cout<<"dbot_itr:"<<Dbot_msg.dbot_itr<<endl;
        cout<<"dbot_act:"<<Dbot_msg.dbot_act<<endl;
        #endif

        //robot_work_mode = cJSON_GetObjectItem(json, "robot_work_mode")->valueint;
        //robot_work_control = cJSON_GetObjectItem(json, "robot_work_control")->valueint;
        //robot_work_speed = cJSON_GetObjectItem(json, "robot_work_speed")->valueint;
        //robot_work_entertainment = cJSON_GetObjectItem(json, "robot_work_entertainment_control")->valueint;//娱乐控制
        // robot_control = cJSON_GetObjectItem(json,"robot_control_date")->valueint;
        // robot_mode = cJSON_GetObjectItem(json,"robot_mode")->valueint;
        // cout<<"robot_control:"<<robot_control<<"robot_mode:"<<robot_mode<<endl;
        cJSON_Delete(json);//释放内存
        // robot_manager::robot_control robot_control_msg;
        // //robot_control_msg.robot_mode = robot_mode;
        // //robot_control_msg.robot_speed = robot_speed;
        // robot_control_msg.robot_control_date = robot_control;
        // robot_control_pub.publish(robot_control_msg);
        /************************************收到信息立即向各个功能包进行数据更新*********************************************/
        //向robot_machine_driver更新数据
        //dbot_h、dbot_roll、dbot_p（计算后发出去）、dbot_m(机器人控制模式)、dbot_ctl（机器人控制）、dbot_act（机器人动作，表示运行哪一个动作模型）
        robot_machine_pub_msg();

        //向robot_i2c_driver、robot_speak更新数据
        //dbot_itr（活动模式）、dbot_m(机器人控制模式、只需要处理自平衡模式，优先级最高)
        robot_i2c_speak_pub_msg();
        
        /************************************************************************************************************/
    }


// void socket_callback(const ros_socket::socket::ConstPtr& msg)
// {
//     cout<<"bridge_node:receive message:"<<msg->socket_recv_date<<endl;
//     //信息处理，并将数据发送到socket
//     string send_msg = msg->socket_recv_date;
//     //数据解析
    
//     copy(send_msg.begin(), send_msg.end(), recv_date_buf);
//     cout<<"message,char[]:"<<recv_date_buf<<endl;

//     recv_date_buf[send_msg.size()] = '\0';
//     date_parse(recv_date_buf);//解析数据

//     recv_date_buf[0]='\0';

// }


void state_callback(const robot_manager::robot_state::ConstPtr& msg)
{
    robot_electricity = msg->robot_electricity;  //获取电量
    robot_state = msg->robot_state;  //获取机器人状态
    robot_robot_devicer_state = msg->robot_driver_state;  //获取机器人设备状态
    robot_camera_state = msg->robot_camera_state;  //获取机器人摄像头状态
    
    cout<<"robot_electricity:"<<robot_electricity<<endl;
    cout<<"robot_state:"<<robot_state<<endl;
    cout<<"robot_robot_devicer_state:"<<robot_robot_devicer_state<<endl;
    cout<<"robot_camera_state:"<<robot_camera_state<<endl;

    //json数据包封装
    cJSON *json = cJSON_CreateObject();

    cJSON_AddNumberToObject(json, "robot_electricity", robot_electricity);
    cJSON_AddNumberToObject(json, "robot_state", robot_state);
    cJSON_AddNumberToObject(json, "robot_robot_devicer_state", robot_robot_devicer_state);
    cJSON_AddNumberToObject(json, "robot_camera_state", robot_camera_state);
    cJSON_AddStringToObject(json, "robot_ip", host);

    char *json_string  = cJSON_Print(json);//将json数据转换为字符串
    
    cJSON_Delete(json);//释放内存
   // ros_socket::socket Socket;

    //Socket.socket_send_date = json_string;//自定义消息类型，Topic_Send_Msg为string类型变量，用于发送socket消息

    //robot_socket_pub.publish(Socket);//发送数据

}


void my_connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
    int i;
    if(!result){
        /* Subscribe to broker information topics on successful connect. */
        mosquitto_subscribe(mosq, NULL, "app", 2);//订阅主题,app为主题名
    }else{
        #ifdef _MQTT_DEBUG_
        cout<<"connect failed"<<endl;

        #endif
    }
}
 

 void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)//接收消息回调函数
{
    if(message->payloadlen){

        #ifdef _MQTT_DEBUG_
        cout<<"来自"<<message->topic<<": "<<(char*)message->payload<<endl;
        #endif
        //json数据解析
        date_parse((char*)message->payload);
    }else{
          
        #ifdef _MQTT_DEBUG_
        cout<<"message payload is null!"<<endl;  
        #endif
    }
    fflush(stdout);
}

 
void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)//订阅回调函数
{
    #ifdef _MQTT_DEBUG_
    cout<<"subscribe success!"<<endl;
    #endif
    //printf("Subscribed (mid: %d): %s\n", mid, msg);
    //fflush(stdout);
    //printf("granted_qos:%d\n", granted_qos[0]);
    //printf("granted_qos:%d\n", granted_qos[1]);
    //printf("granted_qos:%d\n", granted_qos[2]);
    //printf("granted_qos:%d\n", granted_qos[3]);
}

void my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str)//日志回调函数
{
    
    #ifdef _MQTT_DEBUG_
    cout<<"log:"<<str<<endl;
    #endif
}


void sigint_handler(int sig)
{

    cout<<"exit"<<endl;
    ros::shutdown();
}



void robot_i2c_speak_pub_msg(void)
{
    
    robot_manager::robot_i2c_speak msg;
    msg.dbot_m = Dbot_msg.dbot_m;
    msg.dbot_itr = Dbot_msg.dbot_itr;
    robot_i2c_speak_pub.publish(msg);

}
void robot_machine_pub_msg(void)
{
    robot_manager::robot_machine msg;
    msg.dbot_h = Dbot_msg.dbot_h ;
    msg.dbot_roll = Dbot_msg.dbot_roll;
    msg.dbot_p = Dbot_msg.dbot_p;
    msg.dbot_m = Dbot_msg.dbot_m;
    msg.dbot_ctl = Dbot_msg.dbot_ctl;
    msg.dbot_act = Dbot_msg.dbot_act;
    robot_machine_pub.publish(msg);
    
}



