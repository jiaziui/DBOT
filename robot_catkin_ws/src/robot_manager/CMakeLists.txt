cmake_minimum_required(VERSION 3.0.2)
project(robot_manager)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  message_generation
)

add_message_files(
  FILES
  imu_date.msg
  robot_debug.msg
  robot_state.msg
  robot_control.msg
  robot_vosk.msg
  robot_i2c_speak.msg
  robot_machine.msg
  robot_speak_flag.msg
  # Message2.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs message_runtime
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

add_executable(robot_manager src/robot_manager.cpp)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  cjson
  mosquitto
)
