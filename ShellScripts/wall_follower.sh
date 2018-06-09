#!/bin/sh
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/ubuntu/catkin_ws/src/World/SimpleBuilding.world" &
sleep 7
xterm  -e  " roslaunch turtlebot_gazebo gmapping_demo.launch" & 
sleep 7
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 8
xterm  -e  " rosrun wall_follower wall_follower_node"
