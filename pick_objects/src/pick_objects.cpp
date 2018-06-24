#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


// function to send the goal to the robot and check if goal is reached
bool target_to(float x, float y, float w){
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = w;

  // Send the goal position and orientation for the robot to reach
 ROS_INFO("Sending goal");
 ac.sendGoal(goal);

 // Wait an infinite time for the results
 ac.waitForResult();

 // Check if the robot reached its goal
 if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   return true;
 }else{
   return false;
 }


}


int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "simple_navigation_goals");

  bool reach_check;

  // send the first goal to the robot
  reach_check = target_to(4.0, 2.0, 1.0);

  if(reach_check){
    ROS_INFO("Pickup zone reached");
  }else{
    ROS_INFO("Robot failed to reach the pickup zone");
  }

  ROS_INFO("Wait for pickup");


  // send the dropoff goal to the robot
  reach_check = target_to(-3.0, 2.0, 1.0);

  if(reach_check){
    ROS_INFO("Dropoff zone reached");
  }else{
    ROS_INFO("Robot failed to reach the dropoff zone");
  }

  return 0;
}
