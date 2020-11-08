#!/bin/sh
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_world.launch " &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch gmapping_demo.launch" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch view_navigation.launch" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch keyboard_teleop.launch"