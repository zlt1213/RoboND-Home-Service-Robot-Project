#!/bin/sh
xterm  -e  "export TURTLEBOT_GAZEBO_WORLD_FILE=~/catkin_ws/src/World/MyWorld.world; source ~/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm  -e  "source ~/catkin_ws/devel/setup.bash; roslaunch turtlebot_navigation gmapping_demo.launch" &
sleep 5
xterm  -e  "source ~/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e  "source ~/catkin-ws/devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch" &
