#!/bin/bash
echo "***DBOT***: *****************************************************************************"
echo "***DBOT***: 外设准备中！"
i2cdetect -y 1
i2cdetect -y 1
i2cdetect -y 1
echo "***DBOT***: i2c 检测完成！"

[ -e /dev/ttyAMA0 ] && echo "***DBOT***: 外设已启动" || echo "***DBOT***: 外设未启动"

pgrep -f mosquitto && echo "***DBOT***: MQTT 服务正在运行" || echo "***DBOT***: MQTT 服务未运行"


echo "***DBOT***: 外设准备完成！"
echo "***DBOT***: 666!"
echo "***DBOT***: *****************************************************************************"
echo "***DBOT***: 等待DBOT启动···"
roslaunch robot_manager  robot_start.launch
echo "***DBOT***: DBOT结束完成!"
echo "***DBOT***: *****************************************************************************"




