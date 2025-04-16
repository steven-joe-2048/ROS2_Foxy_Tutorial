# 1 Writing a simple publisher and subscriber (C++)
ros2 pkg create --build-type ament_cmake cpp_pubsub --dependencies rclcpp std_msgs
# creating folder ./cpp_pubsub/include/cpp_pubsub
# remove build and install folders
rm -rf build install
# build the workspace
colcon build --packages-select cpp_pubsub
# source the workspace
. install/setup.bash
# run the publisher
ros2 run cpp_pubsub cpp_publisher
# run the subscriber
ros2 run cpp_pubsub cpp_subscriber

# 2 Writing a simple publisher and subscriber (Python)
ros2 pkg create --build-type ament_python py_pubsub --dependencies rclpy std_msgs
# creating folder ./py_pubsub/py_pubsub
# remove build and install folders
rm -rf build install
# build the workspace
colcon build --packages-select py_pubsub
# source the workspace
. install/setup.bash
# run the publisher
ros2 run py_pubsub py_publisher
# run the subscriber
ros2 run py_pubsub py_subscriber


# 3 Writing a simple service and client (C++)
# Recall that packages should be created in the src directory, not the root of the workspace. Navigate into ros2_ws/src and create a new package:
ros2 pkg create --build-type ament_cmake cpp_srvcli --dependencies rclcpp example_interfaces
# creating folder ./cpp_srvcli/include/cpp_srvcli
# remove build and install folders
rm -rf build install
# build the workspace
colcon build --packages-select cpp_srvcli
# source the workspace
. install/setup.bash
# run the service
ros2 run cpp_srvcli cpp_service

# 4 Writing a simple service and client (Python)
# Recall that packages should be created in the src directory, not the root of the workspace. Navigate into ros2_ws/src and create a new package:

cd ros2_ws/src
ros2 pkg create --build-type ament_python py_srvcli --dependencies rclpy example_interfaces
# creating folder ./py_srvcli/py_srvcli
# remove build and install folders
rm -rf build install
# build the workspace
colcon build --packages-select py_srvcli
# source the workspace
. install/setup.bash
# run the service
ros2 run py_srvcli py_service

#5 Creating custom msg and srv files
cd ros2_ws/src
ros2 pkg create --build-type ament_cmake tutorial_interfaces
cd tutorial_interfaces
mkdir msg srv
# add some custom message and service files
touch msg/Sphere.msg
touch msg/Num.msg
touch srv/AddThreeInts.srv
# add the following content to the files xml

colcon build --packages-select tutorial_interfaces


#6 create more interfaces
cd ros2_ws/src
ros2 pkg create --build-type ament_cmake more_interfaces
mkdir more_interfaces/msg more_interfaces/srv
colcon build --packages-up-to more_interfaces
source install/setup.bash
ros2 topic echo /address_book


#####6 Using parameters in a class (C++)
cd ros2_ws/src
# The --dependencies argument will automatically add the necessary dependency lines to package.xml and CMakeLists.txt.
ros2 pkg create --build-type ament_cmake cpp_parameters --dependencies rclcpp
colcon build --packages-select cpp_parameters
ros2 run cpp_parameters minimal_param_node

ros2 param set /minimal_param_node my_parameter earth
# [INFO] [1742873068.319643272] [minimal_param_node]: Hello world!
# [INFO] [1742873069.319657326] [minimal_param_node]: Hello earth!
# [INFO] [1742873070.319654562] [minimal_param_node]: Hello world!

#####7 create a action
ros2 pkg create action_tutorials_interfaces
cd action_tutorials_interfaces
mkdir action

touch Fibonacci.action
# int32 order
# ---
# int32[] sequence
# ---
# int32[] partial_sequence


#####8 create a action server and client
cd ros2_ws/src
ros2 pkg create --dependencies action_tutorials_interfaces rclcpp rclcpp_action rclcpp_components -- action_tutorials_cpp
ros2 run action_tutorials_cpp fibonacci_action_server
ros2 run action_tutorials_cpp fibonacci_action_client --ros-args -p order:=20

# 9 create a action server and client (Python)
cd ros2_ws/src