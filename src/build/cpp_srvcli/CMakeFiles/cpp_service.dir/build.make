# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/caros/DEV/ROS_DEV/ros2_dev/src/cpp_srvcli

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/caros/DEV/ROS_DEV/ros2_dev/src/build/cpp_srvcli

# Include any dependencies generated for this target.
include CMakeFiles/cpp_service.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cpp_service.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cpp_service.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpp_service.dir/flags.make

CMakeFiles/cpp_service.dir/codegen:
.PHONY : CMakeFiles/cpp_service.dir/codegen

CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.o: CMakeFiles/cpp_service.dir/flags.make
CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.o: /home/caros/DEV/ROS_DEV/ros2_dev/src/cpp_srvcli/src/add_two_ints_server.cpp
CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.o: CMakeFiles/cpp_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/caros/DEV/ROS_DEV/ros2_dev/src/build/cpp_srvcli/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.o -MF CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.o.d -o CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.o -c /home/caros/DEV/ROS_DEV/ros2_dev/src/cpp_srvcli/src/add_two_ints_server.cpp

CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/caros/DEV/ROS_DEV/ros2_dev/src/cpp_srvcli/src/add_two_ints_server.cpp > CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.i

CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/caros/DEV/ROS_DEV/ros2_dev/src/cpp_srvcli/src/add_two_ints_server.cpp -o CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.s

# Object files for target cpp_service
cpp_service_OBJECTS = \
"CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.o"

# External object files for target cpp_service
cpp_service_EXTERNAL_OBJECTS =

cpp_service: CMakeFiles/cpp_service.dir/src/add_two_ints_server.cpp.o
cpp_service: CMakeFiles/cpp_service.dir/build.make
cpp_service: /opt/ros/foxy/lib/librclcpp.so
cpp_service: /opt/ros/foxy/lib/libexample_interfaces__rosidl_typesupport_introspection_c.so
cpp_service: /opt/ros/foxy/lib/libexample_interfaces__rosidl_typesupport_c.so
cpp_service: /opt/ros/foxy/lib/libexample_interfaces__rosidl_typesupport_introspection_cpp.so
cpp_service: /opt/ros/foxy/lib/libexample_interfaces__rosidl_typesupport_cpp.so
cpp_service: /opt/ros/foxy/lib/liblibstatistics_collector.so
cpp_service: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_introspection_c.so
cpp_service: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_generator_c.so
cpp_service: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_c.so
cpp_service: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_introspection_cpp.so
cpp_service: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_cpp.so
cpp_service: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_introspection_c.so
cpp_service: /opt/ros/foxy/lib/libstd_msgs__rosidl_generator_c.so
cpp_service: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_c.so
cpp_service: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_introspection_cpp.so
cpp_service: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_cpp.so
cpp_service: /opt/ros/foxy/lib/librcl.so
cpp_service: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_introspection_c.so
cpp_service: /opt/ros/foxy/lib/librcl_interfaces__rosidl_generator_c.so
cpp_service: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_c.so
cpp_service: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_introspection_cpp.so
cpp_service: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_cpp.so
cpp_service: /opt/ros/foxy/lib/librmw_implementation.so
cpp_service: /opt/ros/foxy/lib/librmw.so
cpp_service: /opt/ros/foxy/lib/librcl_logging_spdlog.so
cpp_service: /usr/lib/x86_64-linux-gnu/libspdlog.so.1.5.0
cpp_service: /opt/ros/foxy/lib/librcl_yaml_param_parser.so
cpp_service: /opt/ros/foxy/lib/libyaml.so
cpp_service: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_introspection_c.so
cpp_service: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_generator_c.so
cpp_service: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_c.so
cpp_service: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_introspection_cpp.so
cpp_service: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_cpp.so
cpp_service: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_introspection_c.so
cpp_service: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_generator_c.so
cpp_service: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_c.so
cpp_service: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_introspection_cpp.so
cpp_service: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_cpp.so
cpp_service: /opt/ros/foxy/lib/libtracetools.so
cpp_service: /opt/ros/foxy/lib/libexample_interfaces__rosidl_generator_c.so
cpp_service: /opt/ros/foxy/lib/libaction_msgs__rosidl_typesupport_introspection_c.so
cpp_service: /opt/ros/foxy/lib/libaction_msgs__rosidl_generator_c.so
cpp_service: /opt/ros/foxy/lib/libaction_msgs__rosidl_typesupport_c.so
cpp_service: /opt/ros/foxy/lib/libaction_msgs__rosidl_typesupport_introspection_cpp.so
cpp_service: /opt/ros/foxy/lib/libaction_msgs__rosidl_typesupport_cpp.so
cpp_service: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_c.so
cpp_service: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_generator_c.so
cpp_service: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_c.so
cpp_service: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_cpp.so
cpp_service: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_cpp.so
cpp_service: /opt/ros/foxy/lib/libunique_identifier_msgs__rosidl_typesupport_introspection_c.so
cpp_service: /opt/ros/foxy/lib/libunique_identifier_msgs__rosidl_generator_c.so
cpp_service: /opt/ros/foxy/lib/libunique_identifier_msgs__rosidl_typesupport_c.so
cpp_service: /opt/ros/foxy/lib/libunique_identifier_msgs__rosidl_typesupport_introspection_cpp.so
cpp_service: /opt/ros/foxy/lib/librosidl_typesupport_introspection_cpp.so
cpp_service: /opt/ros/foxy/lib/librosidl_typesupport_introspection_c.so
cpp_service: /opt/ros/foxy/lib/libunique_identifier_msgs__rosidl_typesupport_cpp.so
cpp_service: /opt/ros/foxy/lib/librosidl_typesupport_cpp.so
cpp_service: /opt/ros/foxy/lib/librosidl_typesupport_c.so
cpp_service: /opt/ros/foxy/lib/librcpputils.so
cpp_service: /opt/ros/foxy/lib/librosidl_runtime_c.so
cpp_service: /opt/ros/foxy/lib/librcutils.so
cpp_service: CMakeFiles/cpp_service.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/caros/DEV/ROS_DEV/ros2_dev/src/build/cpp_srvcli/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cpp_service"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpp_service.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpp_service.dir/build: cpp_service
.PHONY : CMakeFiles/cpp_service.dir/build

CMakeFiles/cpp_service.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpp_service.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpp_service.dir/clean

CMakeFiles/cpp_service.dir/depend:
	cd /home/caros/DEV/ROS_DEV/ros2_dev/src/build/cpp_srvcli && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/caros/DEV/ROS_DEV/ros2_dev/src/cpp_srvcli /home/caros/DEV/ROS_DEV/ros2_dev/src/cpp_srvcli /home/caros/DEV/ROS_DEV/ros2_dev/src/build/cpp_srvcli /home/caros/DEV/ROS_DEV/ros2_dev/src/build/cpp_srvcli /home/caros/DEV/ROS_DEV/ros2_dev/src/build/cpp_srvcli/CMakeFiles/cpp_service.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cpp_service.dir/depend

