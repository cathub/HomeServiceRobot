#!/bin/sh
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find add_markers)/../map/MyOffice.world " &
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_navigation gmapping_demo.launch " &
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation_with_marker.launch " &
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch "