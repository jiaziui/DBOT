import rospy
import sys
import os
import rospkg

rospack = rospkg.RosPack()
pkg_path = rospack.get_path('ros_mpu6050_node')
lib_path = os.path.join(pkg_path, 'lib')
sys.path.append(lib_path)


from  MPU6050 import MPU6050
import time
from robot_manager.msg import imu_date   # 导入自定义消息类型imu_date

if __name__ == "__main__":
    i2c_bus = 1
    device_address = 0x68

    x_accel_offset = int(926)
    y_accel_offset = int(2136)
    z_accel_offset = int(-856)
    x_gyro_offset = int(36)
    y_gyro_offset = int(-8)
    z_gyro_offset = int(-28)

    rospy.init_node('MPU6050_node_py', anonymous=True)# 创建节点,命名空间为MPU6050_node_py
    pub = rospy.Publisher('/imu_data', imu_date, queue_size=10) # 创建发布者,话题名为imu_data,队列长度为10

    # x_avg_read: 0.08 x_avg_offset: 926.423499999996
    # y_avg_read: -0.72 y_avg_offset: 2136.152999999997
    # z_avg_read: 0.34 z_avg_offset: -856.0713749999996
    # x_avg_read: 0.16 x_avg_offset: 35.570499999999996
    # y_avg_read: -0.07 y_avg_offset: -8.081437499999883
    # z_avg_read: -0.01 z_avg_offset: -28.00306249999999

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

    rate = rospy.Rate(100) # 10hz 

    try:
        while not rospy.is_shutdown():
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

                pub.publish(Imu_date)

                rate.sleep()
    except KeyboardInterrupt:
        print('\n Ctrl + C QUIT')


    
