/*这段代码是一个 ROS 2 动作服务器（Action Server）的实现，名为 FibonacciActionServer，
它响应客户端请求，计算斐波那契数列，并支持 反馈 (feedback) 和 取消 (canceling) 机制。
✅ 完整实现了一个支持取消和反馈的 ROS 2 Action Server：
1. 创建 Action Server（create_server）。
2. 处理目标 (handle_goal) 和取消 (handle_cancel)。
3. 使用线程 (handle_accepted) 运行任务。
4. 计算斐波那契数列 (execute)，支持反馈。
5. 任务完成或取消。
*/

#include <functional>
#include <memory>
#include <thread>

#include "action_tutorials_interfaces/action/fibonacci.hpp" // Fibonacci action 接口
#include "rclcpp/rclcpp.hpp"                                // ROS2 基本功能, 包含节点、日志、时间等
#include "rclcpp_action/rclcpp_action.hpp"                  // ROS2 Action 服务器 API
#include "rclcpp_components/register_node_macro.hpp"        // 组件注册, 用于注册节点, 使节点能够被其他节点加载
#include "action_tutorials_cpp/visibility_control.h"        // 控制库的可见性, 用于确保 C++ 代码在 C 语言编译器下也能正确编译

namespace action_tutorials_cpp
{
inline uint64_t Nanosecond() {
  return std::chrono::duration_cast<std::chrono::nanoseconds>(
  std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}
  
class FibonacciActionServer : public rclcpp::Node
{
public:
  // 定义 Fibonacci Action 类型
  using Fibonacci = action_tutorials_interfaces::action::Fibonacci;
  // 定义 GoalHandle 类型
  using GoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;
  // 构造函数, 初始化节点, 创建 Fibonacci 动作服务器
  ACTION_TUTORIALS_CPP_PUBLIC // 公开符号, 用于动态库导出, 保证其他项目可以使用该库
  explicit FibonacciActionServer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions()) // 构造函数
  : Node("fibonacci_action_server", options) // 初始化节点
  {
    using namespace std::placeholders;
    t_start = Nanosecond();
    RCLCPP_INFO(this->get_logger(), "Starting Fibonacci action server, ts_start(s): %f", t_start/1e9);
    // 创建一个Fibonacci动作服务器
    this->action_server_ = rclcpp_action::create_server<Fibonacci>(
      this,
      "fibonacci",
      std::bind(&FibonacciActionServer::handle_goal, this, _1, _2),
      std::bind(&FibonacciActionServer::handle_cancel, this, _1),
      std::bind(&FibonacciActionServer::handle_accepted, this, _1));
  }

private:
  rclcpp_action::Server<Fibonacci>::SharedPtr action_server_; // 动作服务器指针
  uint64_t t_start;
  uint64_t t_end;

  // 处理目标请求的回调函数
  rclcpp_action::GoalResponse handle_goal(
    const rclcpp_action::GoalUUID & uuid,
    std::shared_ptr<const Fibonacci::Goal> goal)
  {
    RCLCPP_INFO(this->get_logger(), "Received goal request with order %d", goal->order);
    (void)uuid; // 防止未使用的警告
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE; // 接受并执行目标
  }

  // 处理取消请求的回调函数
  rclcpp_action::CancelResponse handle_cancel(
    const std::shared_ptr<GoalHandleFibonacci> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void)goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT; // 接受取消请求
  }

  // 处理接受目标的回调函数
  void handle_accepted(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
  {
    using namespace std::placeholders;
    // 需要快速返回以避免阻塞执行器，因此启动一个新线程
    std::thread{std::bind(&FibonacciActionServer::execute, this, _1), goal_handle}.detach();
  }

  // 执行目标的函数
  void execute(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(1000); // 设置循环频率为1Hz
    const auto goal = goal_handle->get_goal(); // 获取目标
    auto feedback = std::make_shared<Fibonacci::Feedback>(); // 创建反馈消息
    auto & sequence = feedback->partial_sequence; // 获取部分序列
    sequence.push_back(0); // 初始化斐波那契数列
    sequence.push_back(1);
    auto result = std::make_shared<Fibonacci::Result>(); // 创建结果消息

    for (int i = 1; (i < goal->order) && rclcpp::ok(); ++i) {
      // 检查是否有取消请求
      if (goal_handle->is_canceling()) {
        result->sequence = sequence; // 设置结果序列
        goal_handle->canceled(result); // 取消目标
        RCLCPP_INFO(this->get_logger(), "Goal canceled");
        return;
      }
      // 更新序列
      sequence.push_back(sequence[i] + sequence[i - 1]);
      // 发布反馈
      goal_handle->publish_feedback(feedback);
      auto t_now = Nanosecond();
      RCLCPP_INFO(this->get_logger(), "Publish feedback: %d, ts: %f", sequence.back(), t_now/1e9);

      loop_rate.sleep(); // 休眠以保持循环频率
    }

    // 检查目标是否完成
    if (rclcpp::ok()) {
      result->sequence = sequence; // 设置结果序列
      goal_handle->succeed(result); // 成功完成目标
      t_end = Nanosecond();
      RCLCPP_INFO(this->get_logger(), "Goal succeeded, ts_end(s): %f, duration(us): %f", t_end/1e9, (t_end-t_start)/1e3);
    }
  }
};  // class FibonacciActionServer

}  // namespace action_tutorials_cpp

// 注册节点
RCLCPP_COMPONENTS_REGISTER_NODE(action_tutorials_cpp::FibonacciActionServer)