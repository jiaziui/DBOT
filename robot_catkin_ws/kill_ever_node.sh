#!/bin/bash

# 一键终止指定ROS1节点的脚本
# 目标节点：/robot_manager /usb_cam /web_video_server_1

# 定义颜色代码
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # 恢复默认颜色

# 检查ROS环境
if [ -z "$ROS_DISTRO" ]; then
    echo -e "${RED}错误：未检测到ROS1环境！请先执行 source devel/setup.bash${NC}"
    exit 1
fi

# 目标节点列表
TARGET_NODES=(
    "/robot_manager"
    "/usb_cam" 
    "/web_video_server_1"
)

# 优雅终止节点
echo -e "${YELLOW}正在终止指定节点...${NC}"
for node in "${TARGET_NODES[@]}"; do
    if rosnode list | grep -q "$node"; then
        echo -e "→ 关闭 $node"
        rosnode kill "$node" >/dev/null 2>&1
        
        # 检查是否成功关闭
        if [ $? -eq 0 ]; then
            echo -e "  ${GREEN}✓ 成功${NC}"
        else
            echo -e "  ${RED}✗ 失败，尝试强制终止${NC}"
            pkill -f "$node"
        fi
    else
        echo -e "→ ${YELLOW}$node 未运行${NC}"
    fi
done

# 强制清理残留进程（3秒后）
echo -e "\n${YELLOW}清理残留进程...${NC}"
sleep 3
pkill -f "robot_manager|usb_cam|web_video_server"

# 验证结果
echo -e "\n${GREEN}操作完成！当前运行节点：${NC}"
rosnode list
