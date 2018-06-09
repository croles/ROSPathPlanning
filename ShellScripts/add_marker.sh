#!/bin/sh
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/ubuntu/catkin_ws/src/World/SimpleBuilding.world" &
sleep 7
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/ubuntu/catkin_ws/src/World/SimpleBuilding.yaml" & 
sleep 7
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 6
xterm  -e  " rosrun add_markers add_markers"
