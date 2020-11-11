#!/bin/sh
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find add_markers)/../map/MyOffice.world " &
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find add_markers)/../map/map.yaml " & 
sleep 5
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation_with_marker.launch " &
sleep 10
xterm  -e  " catkin_make; source devel/setup.bash; roslaunch add_markers simple_add_markers.launch "