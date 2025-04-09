#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>  // for std::stringstream
#include <iomanip>  // for std::fixed and std::setprecision

#include "action_tutorials_interfaces/action/fibonacci.hpp"  // Fibonacci action 接口
#include "rclcpp/rclcpp.hpp"  // ROS2 基本功能
#include "rclcpp_action/rclcpp_action.hpp"  // ROS2 Action 客户端 API
#include "rclcpp_components/register_node_macro.hpp"  // 组件注册

namespace action_tutorials_cpp  // 定义命名空间
{
    inline uint64_t Nanosecond() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();
      }
      
class FibonacciActionClient : public rclcpp::Node
{
public:
  // 定义 Fibonacci Action 类型
  using Fibonacci = action_tutorials_interfaces::action::Fibonacci;
  using GoalHandleFibonacci = rclcpp_action::ClientGoalHandle<Fibonacci>;

  explicit FibonacciActionClient(const rclcpp::NodeOptions & options)
  : Node("fibonacci_action_client", options)  // 初始化 ROS2 节点
  {
    t_start = Nanosecond();
    RCLCPP_INFO(this->get_logger(), "Starting Fibonacci action client, ts_start(s): %f", t_start/1e9);
    // 创建 Action 客户端，连接名为 "fibonacci" 的 Action 服务
    this->client_ptr_ = rclcpp_action::create_client<Fibonacci>(
      this,
      "fibonacci");

    // 设置一个 500ms 的定时器，触发 `send_goal()` 发送任务
    this->timer_ = this->create_wall_timer(
      std::chrono::milliseconds(500),
      std::bind(&FibonacciActionClient::send_goal, this));
  }

  // 发送 Action 任务
  void send_goal()
  {
    using namespace std::placeholders;

    // 取消定时器，确保任务只发送一次
    this->timer_->cancel();

    // 等待 Action Server 可用
    if (!this->client_ptr_->wait_for_action_server()) {
      RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
      rclcpp::shutdown();
    }

    // 获取命令行参数
    int order = this->declare_parameter<int>("order", 20);  // 默认值为20
    // 创建 Fibonacci 任务
    auto goal_msg = Fibonacci::Goal();
    goal_msg.order = order;  // 使用命令行参数设置 order

    RCLCPP_INFO(this->get_logger(), "Sending goal with order: %d", order);

    // 设置 Action 客户端的回调函数
    auto send_goal_options = rclcpp_action::Client<Fibonacci>::SendGoalOptions();
    send_goal_options.goal_response_callback =
      std::bind(&FibonacciActionClient::goal_response_callback, this, _1);
    send_goal_options.feedback_callback =
      std::bind(&FibonacciActionClient::feedback_callback, this, _1, _2);
    send_goal_options.result_callback =
      std::bind(&FibonacciActionClient::result_callback, this, _1);

    // 异步发送目标任务
    this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
  }

private:
  rclcpp_action::Client<Fibonacci>::SharedPtr client_ptr_;  // Action 客户端指针
  rclcpp::TimerBase::SharedPtr timer_;  // 定时器指针
  /*   // 目标任务响应回调函数
   When the server receives and accepts the goal, it will send a response to the client. 
   That response is handled by goal_response_callback:
  */
  void goal_response_callback(std::shared_future<GoalHandleFibonacci::SharedPtr> future)
  {
    auto goal_handle = future.get();  // 获取目标句柄
    if (!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");  // 任务被拒绝
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");  // 任务已接受
    }
  }
  /*  // 反馈回调函数（每次有新数据时调用）
    Assuming the goal was accepted by the server, it will start processing. 
    Any feedback to the client will be handled by the feedback_callback:
  */

  void feedback_callback(
    GoalHandleFibonacci::SharedPtr,
    const std::shared_ptr<const Fibonacci::Feedback> feedback)
  {
    std::stringstream ss;
    auto feedback_time = Nanosecond();
    ss << "Next number in sequence received: t_now(s): "
       << std::fixed << std::setprecision(6) << (feedback_time / 1e9) << " ";
    for (auto number : feedback->partial_sequence) {
      ss << number << " ";
    }
    RCLCPP_INFO(this->get_logger(), ss.str().c_str());
  }

  /*// 结果回调函数（任务完成时调用）
    When the server finishes processing the goal, it will send a result to the client. 
    The result is handled by the result_callback:
  */
  void result_callback(const GoalHandleFibonacci::WrappedResult & result)
  {
    switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        break;  // 任务成功
      case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
        return;
      case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
        return;
      default:
        RCLCPP_ERROR(this->get_logger(), "Unknown result code");
        return;
    }

    // 任务成功，输出最终结果
    std::stringstream ss;
    ss << "Result received: ";
    for (auto number : result.result->sequence) {
      ss << number << " ";
    }
    RCLCPP_INFO(this->get_logger(), ss.str().c_str());

    rclcpp::shutdown();  // 任务完成后关闭节点
    t_end = Nanosecond();
    RCLCPP_INFO(this->get_logger(), "Fibonacci action client end, t_end(s): %f Time elapsed: %f us", t_end/1e9, (t_end - t_start) / 1e3);
  }
  uint64_t t_start;
  uint64_t t_end;
};  // class FibonacciActionClient

}  // namespace action_tutorials_cpp

// 注册为 ROS2 组件
RCLCPP_COMPONENTS_REGISTER_NODE(action_tutorials_cpp::FibonacciActionClient)
