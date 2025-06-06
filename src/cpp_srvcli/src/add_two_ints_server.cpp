#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#include <chrono> // std::chrono::seconds
#include <functional> // std::bind
#include <memory>

void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
               std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
{
  response->sum = request->a + request->b;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld",
                request->a, request->b);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}
void multiply(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
               std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
{
  response->sum = request->a * request->b;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request: a: %ld" " b: %ld",
                request->a, request->b);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");

  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr add_service =
    node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);

  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr multiply_service =
    node->create_service<example_interfaces::srv::AddTwoInts>("multiply_two_ints", &multiply);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}