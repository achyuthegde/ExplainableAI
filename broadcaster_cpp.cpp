#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <visualization_msgs/Marker.h>
#include<stdio.h>

std::string frame_name;
void poseCallback(const visualization_msgs::Marker& msg){
 
  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped transformStamped;
  transformStamped.header.stamp = ros::Time::now();
  transformStamped.header.frame_id = "world";
  transformStamped.child_frame_id = msg.header.frame_id;
  transformStamped.transform.translation.x = msg.pose.position.x;
  transformStamped.transform.translation.y = msg.pose.position.y;
  transformStamped.transform.translation.z = msg.pose.position.z;
  transformStamped.transform.rotation.x  = msg.pose.orientation.x;
  transformStamped.transform.rotation.y  = msg.pose.orientation.y;
  transformStamped.transform.rotation.z  = msg.pose.orientation.z;
  transformStamped.transform.rotation.w  = msg.pose.orientation.w;

  br.sendTransform(transformStamped);

}

int main(int argc, char** argv){
  ros::init(argc, argv, "broadcaster_cpp");
  ros::NodeHandle private_node("~");
  frame_name = "my_frame1";
  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("visualization_marker", 1, &poseCallback);

  ros::spin();
  return 0;
};
