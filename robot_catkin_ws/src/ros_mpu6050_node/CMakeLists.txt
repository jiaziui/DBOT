# http://wiki.ros.org/catkin/CMakeLists.txt
cmake_minimum_required(VERSION 2.8.3)
project(ros_mpu6050_node)

set( PATH_I2CDEVLIB "/usr/share/arduino/libraries/i2cdevlib/" )

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
   roscpp
   sensor_msgs
   std_msgs
   std_srvs
   geometry_msgs
   robot_manager
)

#add_definitions( -DMPU6050 -DHMC5883L_SECONDARY -DEMPL_TARGET_LINUX )

#set(CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_C_FLAGS}")

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

#SET(CMAKE_BUILD_TYPE Debug)

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

#######################################
## Declare ROS messages and services ##
#######################################

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
#add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
#)

## Generate added messages and services with any dependencies listed here
#generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
#)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES mpu6050
   CATKIN_DEPENDS std_msgs std_srvs geometry_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
   include  ${catkin_INCLUDE_DIRS}
    #src/linux-mpu9150/glue src/linux-mpu9150/eMPL src/linux-mpu9150/mpu9150
    ${PATH_I2CDEVLIB}RaspberryPi_bcm2835/I2Cdev
    ${PATH_I2CDEVLIB}Arduino/MPU6050/
)

## Declare a cpp library
# add_library(mpu6050
#   src/${PROJECT_NAME}/mpu6050.cpp
# )

## Declare a cpp executable
add_executable(mpu6050_node
    src/mpu6050_node.cpp
    ${PATH_I2CDEVLIB}RaspberryPi_bcm2835/I2Cdev/I2Cdev.cpp
    ${PATH_I2CDEVLIB}Arduino/MPU6050/MPU6050.cpp
)


catkin_install_python(PROGRAMS scripts/robot_mpu6050.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
#add_dependencies(mpu6050_node mpu6050_generate_messages_cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(mpu6050_node
   ${catkin_LIBRARIES}
   bcm2835
   m
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS mpu6050 mpu6050_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )
