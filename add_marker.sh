#!/bin/sh
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch " & 
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation_with_marker.launch " &
sleep 10
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch add_markers simple_add_markers.launch "