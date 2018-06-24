#!/bin/sh
xterm  -e  "export TURTLEBOT_GAZEBO_WORLD_FILE=~/catkin_ws/src/World/MyWorld.world; source ~/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm  -e  "source ~/catkin_ws/devel/setup.bash; roslaunch home_service_robot amcl_demo.launch" &
sleep 5
xterm  -e  "source ~/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e  "source ~/catkin_ws/devel/setup.bash; rosrun pick_objects pick_objects" &
sleep 5
xterm  -e  "source ~/catkin_ws/devel/setup.bash; rosrun add_markers add_markers" &
