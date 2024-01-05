# 项目说明

本项目为机器人操作系统理论与实践课程设计项目——**基于激光雷达的地图构建**

- 编写读取rosbag数据，通过话题发布**激光雷达数据**；
- 写节点实现激光雷达数据的**特征点提取与发布**；
- 节点实现激光雷达**里程计的计算与发布**；
- 节点实现**二维激光雷达地图的构建与发布**；
- 论文格式要求见模板，需附ROS的关键代码。

---

# 环境配置

项目创建的环境为：**Ubuntu 20.04 + ROS Noetic** 。

项目下载之后，编译之前所需工作：

- **修改bag文件路径**：将所有功能包的 launch 文件的 bag 路径，更改为本机的 bag 数据的路径。
- **安装GSL库**：
```bash
    sudo apt-get install libgsl0-dev
```
- **安装CSM库**：在question_3中用到了CSM库，需要安装CSM库，在任意目录下执行以下命令：
```bash
    git clone https://github.com/AndreaCensi/csm
    cd csm
    mkdir build && cd build
    cmake ..
    make
    sudo make install

```

- **安装Gmapping库**：

```bash
    # 设置源
    sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

    # 设置密钥（非必要步骤）
    sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116

    sudo apt-get update

    
    sudo apt install ros-noetic-gazebo-ros-pkgs ros-noetic-gazebo-ros-control

    # 安装gmapping
    sudo apt install ros-noetic-gmapping

    # 安装地图服务包（用于保存和读取地图）
    sudo apt install ros-noetic-map-server

    # 安装navigation包（用于定位以及路径规划）
    sudo apt install ros-noetic-navigation

```



---

# License

MIT

---
