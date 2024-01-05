#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#define max_scan_count 15000 // 雷达数据个数的最大值

// 声明一个类
class LaserScan {
private:
    ros::NodeHandle node_handle_; // ros中的句柄
    ros::NodeHandle private_node_; // ros中的私有句柄
    ros::Subscriber laser_scan_subscriber_; // 声明一个Subscriber
    ros::Publisher laser_scan_publisher_; // 声明一个Publisher

public:
    LaserScan();
    ~LaserScan();
    void ScanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg);
};

// 构造函数
LaserScan::LaserScan()
    : private_node_("~")
{
    ROS_INFO_STREAM("LaserScan initial.");
    // 将雷达的回调函数与订阅的topic进行绑定
    laser_scan_subscriber_ = node_handle_.subscribe("scan", 1, &LaserScan::ScanCallback, this);
    // 将提取后的点发布到 Lidar_data 这个topic
    laser_scan_publisher_ = node_handle_.advertise<sensor_msgs::LaserScan>("data_scan", 1, this);
}

LaserScan::~LaserScan()
{
}

// 回调函数
void LaserScan::ScanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
    ROS_INFO_STREAM(
        "seqence: " << scan_msg->header.seq << ", time stamp: " << scan_msg->header.stamp << ", frame_id: " << scan_msg->header.frame_id << ", angle_min: " << scan_msg->angle_min << ", angle_max: " << scan_msg->angle_max << ", angle_increment: " << scan_msg->angle_increment << ", time_increment: " << scan_msg->time_increment << ", scan_time: " << scan_msg->scan_time << ", range_min: " << scan_msg->range_min << ", range_max: " << scan_msg->range_max << ", range size: " << scan_msg->ranges.size() << ", intensities size: " << scan_msg->intensities.size());

    // 第5个点的欧式坐标为
    double range = scan_msg->ranges[4];
    double angle = scan_msg->angle_min + scan_msg->angle_increment * 4;
    double x = range * cos(angle);
    double y = range * sin(angle);

    ROS_INFO_STREAM(
        // 第5个数据点对应的极坐标为:
        "range = " << range << ", angle = " << angle <<
        // 第5个数据点对应的欧式坐标为:
        ", x = " << x << ", y = " << y);

    // 声明一个临时的sensor_msgs::LaserScan变量,用于存储特征提取后的scan数据,并发布出去,在rviz中进行显示
    sensor_msgs::LaserScan corner_scan;
    corner_scan.header.seq = scan_msg->header.seq;
    corner_scan.header.stamp = scan_msg->header.stamp;
    corner_scan.header.frame_id = scan_msg->header.frame_id;
    corner_scan.angle_min = scan_msg->angle_min;
    corner_scan.angle_max = scan_msg->angle_max;
    corner_scan.angle_increment = scan_msg->angle_increment;
    corner_scan.time_increment = scan_msg->time_increment;
    corner_scan.scan_time = scan_msg->scan_time;
    corner_scan.range_min = scan_msg->range_min;
    corner_scan.range_max = scan_msg->range_max;
    corner_scan.ranges = scan_msg->ranges;
    corner_scan.intensities = scan_msg->intensities;

    // corner_scan.ranges.resize(max_scan_count);

    laser_scan_publisher_.publish(corner_scan);

}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "question1_laser_scan_node"); // 节点的名字

    LaserScan laser_scan;
    ros::spin(); // 程序执行到此处时开始进行等待，每次订阅的消息到来都会执行一次ScanCallback()
    return 0;
}
