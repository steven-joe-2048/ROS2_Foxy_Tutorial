// 监听器（Subscriber）节点实现，订阅 "chatter" 话题，并在接收到消息时打印输出。

#include <memory>
#include "rclcpp/rclcpp.hpp"       // ROS 2 C++ 节点库
#include "std_msgs/msg/string.hpp" // ROS 2 标准消息类型（std_msgs::msg::String）

// 定义 Listener 类，继承自 rclcpp::Node
class Listener : public rclcpp::Node {
public:
    // 构造函数：创建一个名为 "listener" 的 ROS 2 节点
    Listener() : Node("listener") {
        // 创建订阅者，订阅 "chatter" 话题，队列大小设为 10
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "chatter", 10, 
            // 绑定回调函数 topic_callback()，_1 代表回调函数的参数（接收到的消息）
            std::bind(&Listener::topic_callback, this, std::placeholders::_1));
    }

private:
    // 话题回调函数，当收到 "chatter" 话题的消息时被调用
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const {
        // 打印收到的消息内容
        RCLCPP_INFO(this->get_logger(), "I heard: [%s]", msg->data.c_str());
    }

    // 订阅者对象（订阅 "chatter" 话题的消息）
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

// 主函数
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);                    // 初始化 ROS 2
    rclcpp::spin(std::make_shared<Listener>());  // 运行节点，监听 "chatter" 话题
    rclcpp::shutdown();                          // 退出时清理 ROS 2 资源
    return 0;
}


/*
// src/listener.cpp

#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class Listener : public rclcpp::Node {
public:
    Listener() : Node("listener") {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "chatter", 10,
            std::bind(&Listener::topic_callback, this, std::placeholders::_1));
    }

private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "I heard: [%s]", msg->data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Listener>());
    rclcpp::shutdown();
    return 0;
}
*/