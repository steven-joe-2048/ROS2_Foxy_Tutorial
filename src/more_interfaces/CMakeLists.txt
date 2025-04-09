cmake_minimum_required(VERSION 3.10)
project(more_interfaces)

# 默认 C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# 默认 C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 发现依赖
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# 设定自定义消息
set(msg_files
  "msg/AddressBook.msg"
)

# C++ 应用
find_package(rclcpp REQUIRED)
find_package(tutorial_interfaces REQUIRED)

# 生成接口，包含 tutorial_interfaces 依赖
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES tutorial_interfaces
)

ament_export_dependencies(rosidl_default_runtime)

add_executable(publish_address_book src/publish_address_book.cpp)
ament_target_dependencies(publish_address_book rclcpp std_msgs tutorial_interfaces)

add_executable(subscribe_address_book src/subscribe_address_book.cpp)
ament_target_dependencies(subscribe_address_book rclcpp std_msgs tutorial_interfaces)

install(TARGETS
    publish_address_book
    subscribe_address_book
    DESTINATION lib/${PROJECT_NAME})

# 让可执行文件支持 rosidl 接口
rosidl_target_interfaces(publish_address_book
  ${PROJECT_NAME} "rosidl_typesupport_cpp")
rosidl_target_interfaces(subscribe_address_book
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

# 测试支持
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
