// 引入必要的头文件
#include <chrono> // 用于时间相关功能，如秒(std::chrono::seconds)
#include <memory> // 用于智能指针，如std::shared_ptr
#include "rclcpp/rclcpp.hpp" // ROS2的C++客户端库核心功能
#include "more_interfaces/msg/address_book.hpp" // 自定义消息类型

// #include "tutorial_interfaces/msg/contact.hpp"     // CHANGE  测试失败 20250325

using namespace std::chrono_literals; // 启用时间字面量，如1s表示1秒

// 定义一个继承自rclcpp::Node的地址簿发布者类
class AddressBookPublisher : public rclcpp::Node
{
public:
  // 构造函数
  AddressBookPublisher()
  : Node("address_book_publisher") // 调用基类构造函数，设置节点名
  {
    // 创建一个发布者，发布到"address_book"话题，消息类型为AddressBook，队列大小10
    address_book_publisher_ =
      this->create_publisher<more_interfaces::msg::AddressBook>("address_book", 10);

    // 定义发布消息的lambda函数
    auto publish_msg = [this]() -> void {
        /* //firs type of message only use interafece defined in the same package*/
        // 创建一个AddressBook消息对象
        auto message = more_interfaces::msg::AddressBook();
        // 设置消息内容
        message.first_name = "John";
        message.last_name = "Doe";
        message.phone_number = "1234567890";
        message.phone_type = message.PHONE_TYPE_MOBILE; // 使用枚举值设置手机类型
        // 打印发布的信息到控制台
        std::cout << "Publishing Contact\nFirst:" << message.first_name 
        <<"  Last:" << message.last_name 
        <<"  Phone:" << message.phone_number
        <<"  Type:" << static_cast<int>(message.phone_type)
        << std::endl;
        // 发布消息
        this->address_book_publisher_->publish(message);
        
        // // CHANGE; using an existing message type to fill the new message type
        /*从一个外部的以来接口导入本地接口信息，测试失败*/
        // auto msg = std::make_shared<more_interfaces::msg::AddressBook>();
        // {
        //   tutorial_interfaces::msg::Contact contact;
        //   contact.first_name = "John";
        //   contact.last_name = "Doe";
        //   contact.phone_number = "1234567890";
        //   contact.phone_type = message.PHONE_TYPE_MOBILE;
        //   msg->address_book.push_back(contact);
        // }
        // {
        //   tutorial_interfaces::msg::Contact contact;
        //   contact.first_name = "Jane";
        //   contact.last_name = "Doe";
        //   contact.phone_number = "4254242424";
        //   contact.phone_type = message.PHONE_TYPE_HOME;
        //   msg->address_book.push_back(contact);
        // }
        // std::cout << "Publishing address book:" << std::endl;
        // for (auto contact : msg->address_book) {
        //   std::cout << "First:" << contact.first_name << "  Last:" << contact.last_name <<
        //     std::endl;
        // }
        // address_book_publisher_->publish(*msg);
      };
    
    // 创建一个定时器，每1秒触发一次publish_msg函数
    timer_ = this->create_wall_timer(1s, publish_msg);
  }

private:
  // 声明发布者共享指针
  rclcpp::Publisher<more_interfaces::msg::AddressBook>::SharedPtr address_book_publisher_;
  // 声明定时器共享指针
  rclcpp::TimerBase::SharedPtr timer_;
};

// 主函数
int main(int argc, char * argv[])
{
  // 初始化ROS2客户端库
  rclcpp::init(argc, argv);
  // 创建AddressBookPublisher节点并进入自旋状态(处理回调)
  rclcpp::spin(std::make_shared<AddressBookPublisher>());
  // 关闭ROS2客户端库
  rclcpp::shutdown();

  return 0;
}