cmake_minimum_required(VERSION 3.0.2)
project(robot_machine_driver)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  robot_manager
)

generate_messages(
   DEPENDENCIES
   std_msgs
 )

#jia:添加生成的消息依
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES robot_machine_driver
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime robot_manager
  DEPENDS system_lib
)


set(CMAKE_INSTALL_PREFIX /usr/local)
include_directories(
 include
${catkin_INCLUDE_DIRS}
${CMAKE_INSTALL_PREFIX}/include
)

link_directories(
${CMAKE_INSTALL_PREFIX}/lib
)

add_executable(robot_machine_driver src/robot_machine_driver.cpp)

target_link_libraries(robot_machine_driver
  ${catkin_LIBRARIES}
  cserialport # 轻量级串口通信庿  
  fsuartservo # FashionStar总线伺服舵机SDK (C++) 
)
