#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <visualization_msgs/Marker.h>
#include<stdio.h>

std::string frame_name;
void poseCallback(const visualization_msgs::Marker& msg){
 
  static tf2_ros::TransformBroadcaster br;
 /*
  //geometry_msgs::TransformStamped transformStamped;
  visualization_msgs::Marker marker;
  marker.header.stamp = ros::Time::now();  
  //transformStamped.header.stamp = ros::Time::now();
  marker.header.frame_id = "world";
  marker.child_frame_id = "/my_frame";
  marker.pose.position.x = msg->pose.position.x;
  marker.pose.position.y = msg->pose.position.y;
  marker.pose.position.z = msg->pose.position.z;
  marker.pose.orientation.x  = msg->pose.orientation.x;
  marker.pose.orientation.x  = msg->pose.orientation.y;
  marker.pose.orientation.x  = msg->pose.orientation.z;
  marker.pose.orientation.x  = msg->pose.orientation.w;

  br.sendTransform(marker);
 
  */
geometry_msgs::TransformStamped transformStamped;
  transformStamped.header.stamp = ros::Time::now();
  //transformStamped.header.stamp = ros::Time::now();
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
 /* if (! private_node.hasParam("my_frame"))
  {
if (argc != 2){ROS_ERROR("need frame name as argument"); return -1;};
   frame_name = argv[1];
  }
  else
  {
    private_node.getParam("my_frame", frame_name);
  }
*/
  
  //std::cout<< frame_name;
  frame_name = "my_frame1";
  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("visualization_marker", 1, &poseCallback);

  ros::spin();
  return 0;
};
