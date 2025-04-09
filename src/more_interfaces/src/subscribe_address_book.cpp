#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

class AddressBookSubscriber : public rclcpp::Node
{
public:
    AddressBookSubscriber()
    : Node("address_book_subscriber")
    {
        subscription_ = this->create_subscription<more_interfaces::msg::AddressBook>(
            "address_book", 10, std::bind(&AddressBookSubscriber::topic_callback, this, std::placeholders::_1));
    }

private:
    void topic_callback(const more_interfaces::msg::AddressBook::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), 
        "Received address book entry: first_name:%s, last_name:%s, phone_number: %s, phone_type: %d",
            msg->first_name.c_str(), 
            msg->last_name.c_str(), 
            msg->phone_number.c_str(), 
            msg->phone_type);
    }

    rclcpp::Subscription<more_interfaces::msg::AddressBook>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AddressBookSubscriber>());
    rclcpp::shutdown();
    return 0;
}