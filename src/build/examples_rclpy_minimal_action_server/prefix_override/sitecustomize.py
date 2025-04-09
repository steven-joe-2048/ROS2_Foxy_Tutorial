import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/caros/DEV/ROS_DEV/ros2_dev/src/install/examples_rclpy_minimal_action_server'
