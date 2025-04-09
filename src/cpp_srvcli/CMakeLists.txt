cmake_minimum_required(VERSION 3.10)
project(cpp_srvcli)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(tutorial_interfaces REQUIRED)        # CHANGE

# The add_executable macro generates an executable you can run using ros2 run. 
# Add the following code block to CMakeLists.txt to create an executable named server:
add_executable(cpp_service src/add_two_ints_server.cpp)
ament_target_dependencies(cpp_service rclcpp example_interfaces)
add_executable(cpp_client src/add_two_ints_client.cpp)
ament_target_dependencies(cpp_client rclcpp example_interfaces)

#### new add CHANGE
add_executable(service_new_intf src/add_two_ints_server_new_intf.cpp)
ament_target_dependencies(service_new_intf rclcpp tutorial_interfaces)
add_executable(client_new_intf src/add_two_ints_client_new_intf.cpp)
ament_target_dependencies(client_new_intf rclcpp tutorial_interfaces)
####

# So ros2 run can find the executable, add the following lines to the end of the file, 
# right before ament_package():
install(TARGETS
  cpp_service
  cpp_client
  service_new_intf
  client_new_intf
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()


