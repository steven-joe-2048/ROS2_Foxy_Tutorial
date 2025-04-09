
/**
 * 
 * This example demonstrates how to create a simple service and client with rclcpp.
 * the client sends a request to the service, and the service responds with the sum of two integers.
 * only excute once
 */

// #include "rclcpp/rclcpp.hpp"
// #include "example_interfaces/srv/add_two_ints.hpp"
// #include <chrono>
// #include <cstdlib>
// #include <memory>

// using namespace std::chrono_literals;

// int main(int argc, char **argv)
// {
//   rclcpp::init(argc, argv);

//   if (argc != 3) {
//       RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_two_ints_client X Y");
//       return 1;
//   }

//   std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_client");
//   rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client =
//     node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

//   auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
//   request->a = atoll(argv[1]);
//   request->b = atoll(argv[2]);

//   while (!client->wait_for_service(1s)) {
//     if (!rclcpp::ok()) {
//       RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
//       return 0;
//     }
//     RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
//   }

//   auto result = client->async_send_request(request);
//   // Wait for the result.
//   if (rclcpp::spin_until_future_complete(node, result) ==
//     rclcpp::FutureReturnCode::SUCCESS)
//   {
//     RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
//   } else {
//     RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
//   }

//   rclcpp::shutdown();
//   return 0;
// }



// #include <chrono>
// #include <memory>
// #include "rclcpp/rclcpp.hpp"
// #include "example_interfaces/srv/add_two_ints.hpp"

// using namespace std::chrono_literals;

// class AddTwoIntsClient : public rclcpp::Node
// {
// public:
//     AddTwoIntsClient() : Node("add_two_ints_client")
//     {
//         client_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
//     }

//     void send_request()
//     {
//         auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
//         request->a = 22222;
//         request->b = 33333;
//         RCLCPP_INFO(this->get_logger(), "Sending request with a: %ld, b: %ld", request->a, request->b);

//         while (!client_->wait_for_service(1s)) {
//             if (!rclcpp::ok()) {
//                 RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
//                 return;
//             }
//             RCLCPP_INFO(this->get_logger(), "Service not available, waiting again...");
//         }

//         auto result = client_->async_send_request(request);
//         if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) ==
//             rclcpp::FutureReturnCode::SUCCESS)
//         {
//             RCLCPP_INFO(this->get_logger(), "Sum: %ld", result.get()->sum);
//             return;
//         } else {
//             RCLCPP_ERROR(this->get_logger(), "Failed to call service add_two_ints");
//         }
//     }

// private:
//     rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;
// };

// int main(int argc, char **argv)
// {
//     rclcpp::init(argc, argv);
//     auto node = std::make_shared<AddTwoIntsClient>();
//     node->send_request();
//     rclcpp::shutdown();
//     return 0;
// }

/**
 * This example demonstrates how to create a simple service and client with rclcpp.
 * the client sends a request regularly to the service, and the service responds with the sum of two integers.
 */
#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;

class AddTwoIntsClient : public rclcpp::Node
{
public:
    AddTwoIntsClient() : Node("add_two_ints_client")
    {
        client_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        timer_ = this->create_wall_timer(
            500ms, std::bind(&AddTwoIntsClient::send_request, this));
    }

private:
    void send_request()
    {
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = 22222;
        request->b = 33333;
        RCLCPP_INFO(this->get_logger(), "Sending request with a: %ld, b: %ld", request->a, request->b);

        while (!client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Service not available, waiting again...");
        }

        // 发送异步请求，使用回调函数接收结果
        auto future_result = client_->async_send_request(request,
            std::bind(&AddTwoIntsClient::response_callback, this, std::placeholders::_1));
    }

    void response_callback(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture future)
    {
        auto result = future.get();
        RCLCPP_INFO(this->get_logger(), "Sum: %ld", result->sum);
    }

    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AddTwoIntsClient>());
    rclcpp::shutdown();
    return 0;
}
