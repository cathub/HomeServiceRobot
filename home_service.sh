#!/bin/sh
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch " & 
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation_with_marker.launch " &
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch pick_objects pick_objects.launch " &
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch add_markers add_markers.launch "