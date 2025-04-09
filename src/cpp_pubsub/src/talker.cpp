// talker.cpp
// 该程序是 ROS 2 的一个基本 "发布者" 节点（Publisher），它会在话题 "chatter" 上不断发布字符串消息。

#include <memory>  // 引入 C++ 智能指针 std::shared_ptr
#include "rclcpp/rclcpp.hpp"  // ROS 2 C++ 客户端库，提供节点、日志、发布订阅等功能
#include "std_msgs/msg/string.hpp"  // 引入标准的 String 消息类型

using namespace std::chrono_literals;  // 让我们可以使用 1ms, 1s 等时间单位

// 定义 Talker 类，继承自 rclcpp::Node，它是一个 ROS 2 的发布者节点
class Talker : public rclcpp::Node {
public:
    // 构造函数，初始化节点3
    Talker() : Node("talker"), count_(0) {
        // 创建一个发布者，发布 std_msgs::msg::String 类型的消息，话题名为 "chatter"，队列大小 10
        publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);

        // 创建一个定时器，每 1ms 触发一次 timer_callback() 方法
        timer_ = this->create_wall_timer(
            1ms, std::bind(&Talker::timer_callback, this));
    }

private:
    // 定时器回调函数，每次触发都会执行
    void timer_callback() {
        auto message = std_msgs::msg::String();  // 创建 String 类型的消息对象

        // 生成消息内容，包含 "Hello, world" 和当前时间戳的后两位（纳秒）以及 count_ 计数器
        message.data = "Hello, world, this is a test, not a real message, but the message is not empty, is very long, and it is a test! " 
            + std::to_string(this->get_clock()->now().nanoseconds() % 100)  // 当前 ROS 时间戳的最后两位纳秒
            + std::to_string(count_++);  // 计数器，每次发送递增

        // 打印日志，显示当前发布的消息内容
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());

        // 通过发布者发布消息
        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;  // 定时器指针，每 1ms 触发一次回调函数
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;  // 发布者指针
    size_t count_;  // 计数变量，用于生成不同的消息
};

// 主函数，ROS 2 节点的入口
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);  // 初始化 ROS 2
    rclcpp::spin(std::make_shared<Talker>());  // 运行节点，并保持监听状态
    rclcpp::shutdown();  // 关闭 ROS 2
    return 0;
}



// /* 原来的程序*/
// // src/talker.cpp
// #include <memory>
// #include "rclcpp/rclcpp.hpp"
// #include "std_msgs/msg/string.hpp"

// using namespace std::chrono_literals;

// class Talker : public rclcpp::Node {
// public:
//     Talker() : Node("talker"), count_(0) {
//         publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
//         timer_ = this->create_wall_timer(
//             1ms, std::bind(&Talker::timer_callback, this));
//     }

// private:
//     void timer_callback() {
//         auto message = std_msgs::msg::String();
//         message.data = "Hello, world, this is a test, not a real message, but the message is not empty, is very long, and it is a test! " 
//         + std::to_string(this->get_clock()->now().nanoseconds() % 100) + std::to_string(count_++);
//         RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
//         publisher_->publish(message);
//     }
//     rclcpp::TimerBase::SharedPtr timer_;
//     rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
//     size_t count_;
// };

// int main(int argc, char **argv) {
//     rclcpp::init(argc, argv);
//     rclcpp::spin(std::make_shared<Talker>());
//     rclcpp::shutdown();
//     return 0;
// }
