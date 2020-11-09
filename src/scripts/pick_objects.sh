#!/bin/sh
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch " & 
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch pick_objects simple_pick_objects.launch "