#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <signal.h>

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <std_msgs/Bool.h>
#include <std_srvs/Empty.h>
#include <geometry_msgs/Vector3Stamped.h>

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#include "robot_manager/imu_date.h"




MPU6050 mpu;
using namespace std;



struct KalmanFilter{
	float LastP;		//上一次协方差
	float NewP;		//最新的协方差
	float Out;			//卡尔曼输出
	float Kg;				//卡尔曼增益
	float Q;				//过程噪声的协方差
	float R;				//观测噪声的协方差
};

void kalmanfiter(struct KalmanFilter *EKF,float input);	
void mpu_kalman();

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO

uint8_t fifoBuffer[64];
Quaternion q;
float ypr[3];

int sample_rate = 100;


int ax, ay, az, gx, gy, gz;
VectorInt16 gyro,accel; 
float pitch, roll, yaw;

bool debug = false;
bool ado = false;


ros::Publisher pub;

void mySigintHandler(int sig){//ctrl+c
	ROS_INFO("Shutting down mpu6050_node...");

	mpu.reset();
	ros::shutdown();
}
// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop(ros::NodeHandle n) {

    robot_manager::imu_date Imu_date;


    fifoCount = mpu.getFIFOCount();

    if (fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
    }
    else if (fifoCount >=  20) {
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    //获取加速度计、陀螺仪数据
    uint8_t status = mpu.dmpGetGyro(&gyro, fifoBuffer); // 确保 `packet` 已正确初始化
    gx = gyro.x;
    gy = gyro.y;
    gz = gyro.z;
    mpu.dmpGetAccel(&accel, fifoBuffer);
    ax = accel.x;
    ay = accel.y;
    az = accel.z;

    //mpu_kalman();//滤波器

    // 计算四元数
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    pitch = asin(-2 * q.x * q.z + 2 * q.w* q.y)* 180/M_PI;	// pitch
	roll  = atan2(2 * q.y * q.z + 2 * q.w * q.x, -2 * q.x * q.x - 2 * q.y* q.y + 1)* 180/M_PI;	// roll
	yaw   = atan2(2*(q.x*q.y + q.w*q.z),q.w*q.w+q.x*q.x-q.y*q.y-q.z*q.z) * 180/M_PI;	//yaw

    if(debug == 1)
    {

        cout<<"ax: "<<ax<<" ay: "<<ay<<" az: "<<az<<" gx: "<<gx<<" gy: "<<gy<<" gz: "<<gz<<endl;
    cout<<"pitch: "<<pitch<<" roll: "<<roll<<" yaw: "<<yaw<<endl;
    cout<<"pitch: "<<pitch<<" roll: "<<roll<<" yaw: "<<yaw<<endl;
    }
    

    Imu_date.ax = ax;
    Imu_date.ay = ay;
    Imu_date.az = az;
    Imu_date.gx = gx;
    Imu_date.gy = gy;
    Imu_date.gz = gz;
    Imu_date.pitch = pitch;
    Imu_date.roll = roll;
    Imu_date.yaw = yaw;

    pub.publish(Imu_date);
    }
}






int main(int argc, char **argv){

    ros::init(argc, argv, "mpu6050");

    // Does not allow parameters being passed in.
    ros::NodeHandle n;

    signal(SIGINT, mySigintHandler);//ctrl+c, 退出程序

    //获取参数debug参数
    n.getParam("/mpu6050_node/debug", debug);
    ROS_INFO("debug: %d", debug);
    //获取频率参数
    n.getParam("/mpu6050_node/frequency", sample_rate);
    

    ROS_INFO("Starting mpu6050_node...");

    
    printf("Initializing I2C...\n");
    I2Cdev::initialize();

    // verify connection
    printf("Testing device connections...\n");
    mpu = MPU6050(ado ? 0x69 : 0x68);
    if(mpu.testConnection()){
        std::cout << "MPU6050 connection successful" << std::endl << std::flush;
    }else{
        std::cout << "MPU6050 connection failed" << std::endl << std::flush;
        return 1;
    }

    // initialize device
    printf("Initializing I2C devices...\n");
    mpu.initialize();

    // load and configure the DMP
    printf("Initializing DMP...\n");
    devStatus = mpu.dmpInitialize();

    // Set accel offsets

    // mpu.setXAccelOffset(0);
    // mpu.setYAccelOffset(0);
    // mpu.setZAccelOffset(0);
    // mpu.setXGyroOffset(0);
    // mpu.setYGyroOffset(0);
    // mpu.setZGyroOffset(0);

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        printf("Enabling DMP...\n");
        
        mpu.setDMPEnabled(true);//启用DMP功能
        // enable Arduino interrupt detection
        //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        //attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        printf("DMP ready!\n");
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        printf("DMP Initialization failed (code %d)\n", devStatus);
    }

    pub = n.advertise<robot_manager::imu_date>("/imu_date", 10);
    
    usleep(100000);
    


    ros::Rate r(sample_rate);

    while(ros::ok()){
        loop(n);
        ros::spinOnce();
        r.sleep();
    }
    std::cout << "Shutdown." << std::endl << std::flush;

    return 0;

}

uint16_t pMpu[6];

//滤波器
void mpu_kalman(){
    pMpu[0] =gx;
    pMpu[1] =gy;
    pMpu[2] =gz;//陀螺仪
    pMpu[3] =ax;
    pMpu[4] =ay;
    pMpu[5] =az;//加速度数据

    for(int i=0;i<6;i++){

        if(i<3)//角加速度卡尔曼
        {
            static struct KalmanFilter EKF[3] = {{0.02,0,0,0,0.001,0.543},{0.02,0,0,0,0.001,0.543},{0.02,0,0,0,0.001,0.543}};
            kalmanfiter(&EKF[i],(float)pMpu[i]);  
				pMpu[i] = (int16_t)EKF[i].Out;
        }
        if(i > 2)		/* 角速度一阶互补滤波 */
		{	
			uint8_t k=i-3;
			const float factor = 0.15f; 	
			static float tBuff[3];		

			pMpu[i] = tBuff[k] = tBuff[k] * (1 - factor) + pMpu[i] * factor;                
		}
    }

    gx=pMpu[0];
    gy=pMpu[1];
    gz=pMpu[2];//陀螺仪
    ax=pMpu[3];
    ay=pMpu[4];
    az=pMpu[5];//加速度数据

}


void kalmanfiter(struct KalmanFilter *EKF,float input)
{
	EKF->NewP = EKF->LastP + EKF->Q;
	EKF->Kg = EKF->NewP / (EKF->NewP + EKF->R);
	EKF->Out = EKF->Out + EKF->Kg * (input - EKF->Out);
	EKF->LastP = (1 - EKF->Kg) * EKF->NewP;
}