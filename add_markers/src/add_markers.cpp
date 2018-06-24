#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

#define Robo_Marker_DIST_TOLERANCE 0.7

ros::Publisher marker_pub;
visualization_msgs::Marker marker;

bool obj_onboard = false;

// call back function for adometry check
void odomCallback(const nav_msgs::Odometry::ConstPtr& msg){

  float current_x = msg->pose.pose.position.x;
  float current_y = msg->pose.pose.position.y;

  float pick_up_dist = (current_x - 4.0) * (current_x - 4.0) + (current_y - 2.0) * (current_y - 2.0);
  float drop_off_dist = (current_x + 3.0) * (current_x + 3.0) + (current_y - 2.0) * (current_y - 2.0);

  // if reach pick location
  if(pick_up_dist < Robo_Marker_DIST_TOLERANCE * Robo_Marker_DIST_TOLERANCE){
    // hide the marker
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Object loaded");
    obj_onboard = true;
  }

  // if reach drop off location
  if(drop_off_dist < Robo_Marker_DIST_TOLERANCE * Robo_Marker_DIST_TOLERANCE){

    marker.pose.position.x = -3.0;
    marker.pose.position.y = 2.0;
    marker.pose.position.z = 0.0;
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    obj_onboard = false;
    ROS_INFO("Object dropped");
  }

  if(obj_onboard){
    ROS_INFO("moving object");
  }

  return;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;


  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  uint32_t shape = visualization_msgs::Marker::CUBE;

  marker.header.frame_id = "/map";
  marker.ns = "basic_shapes";
  marker.id = 0;
  marker.header.stamp = ros::Time::now();
  marker.type = shape;
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.
  marker.pose.position.x = 4.0;
  marker.pose.position.y = 2.0;
  marker.pose.position.z = 0.0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // size of the marker
  marker.scale.x = 0.25;
  marker.scale.y = 0.25;
  marker.scale.z = 0.25;

  // color fo the marker
  marker.color.r = 0.1f;
  marker.color.g = 0.1f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  ros::Duration(1.0).sleep();

  // show the marker
  ROS_INFO("Pick up marker added");
  marker_pub.publish(marker);

  // // hide the marker
  // sleep(5);
  // marker.action = visualization_msgs::Marker::DELETE;
  // marker_pub.publish(marker);
  // ROS_INFO("Object loaded");

  // // show marker at drop off location
  // sleep(5);
  // marker.pose.position.x = -3.0;
  // marker.pose.position.y = 2.0;
  // marker.pose.position.z = 0.0;
  // marker.action = visualization_msgs::Marker::ADD;
  // marker_pub.publish(marker);
  // ROS_INFO("Show the Marker at drop off location");




  ros::Subscriber odom_sub = n.subscribe("/odom", 1, odomCallback);


  ros::Rate r(10.0); // 10 Hz
  while (ros::ok()) {
      ros::spinOnce();
      r.sleep();
  }

  return 0;

}
