#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(20000);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::SPHERE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker1;
    visualization_msgs::Marker marker2;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker1.header.frame_id = "/my_frame1";
    marker2.header.frame_id = "/my_frame2";
    marker1.header.stamp = ros::Time::now();
    marker2.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker1.ns = "basic_shapes";
    marker1.id = 0;
    marker2.ns = "basic_shapes";
    marker2.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker1.type = shape;
    marker2.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker1.action = visualization_msgs::Marker::ADD;
    marker2.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    float randomx1 = (rand() % 10) + 1;
    float randomy1 = (rand() % 10) + 1;
    float randomx2 = (rand() % 10) + 1;
    float randomy2 = (rand() % 10) + 1;

    marker1.pose.position.x = randomx1;
    marker1.pose.position.y = randomy1;
    marker1.pose.position.z = 0;
    marker1.pose.orientation.x = 0.0;
    marker1.pose.orientation.y = 0.0;
    marker1.pose.orientation.z = 0.0;
    marker1.pose.orientation.w = 1.0;

    marker2.pose.position.x = randomx2;
    marker2.pose.position.y = randomy2;
    marker2.pose.position.z = 0;
    marker2.pose.orientation.x = 0.0;
    marker2.pose.orientation.y = 0.0;
    marker2.pose.orientation.z = 0.0;
    marker2.pose.orientation.w = 1.0;
    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker1.scale.x = 1.0;
    marker1.scale.y = 1.0;
    marker1.scale.z = 1.0;

    marker2.scale.x = 1.0;
    marker2.scale.y = 1.0;
    marker2.scale.z = 1.0;
    // Set the color -- be sure to set alpha to something non-zero!
    marker1.color.r = 0.0f;
    marker1.color.g = 1.0f;
    marker1.color.b = 0.0f;
    marker1.color.a = 1.0;

    marker2.color.r = 0.0f;
    marker2.color.g = 1.0f;
    marker2.color.b = 0.0f;
    marker2.color.a = 1.0;
    marker1.lifetime = ros::Duration();
    marker2.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker1);
    marker_pub.publish(marker2);
  /*  
    r.sleep();
     Cycle between different shapes
    switch (shape)
    {
    case visualization_msgs::Marker::CUBE:
      shape = visualization_msgs::Marker::SPHERE;
      break;
    case visualization_msgs::Marker::SPHERE:
      shape = visualization_msgs::Marker::ARROW;
      break;
    case visualization_msgs::Marker::ARROW:
      shape = visualization_msgs::Marker::CYLINDER;
      break;
    case visualization_msgs::Marker::CYLINDER:
      shape = visualization_msgs::Marker::CUBE;
      break;
    }*/

    r.sleep();
  }
}
