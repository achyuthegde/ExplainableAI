#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>
using namespace std;
bool pcoin = false;
bool ecoin = false;
bool abut = false;
bool away = false;
void calculate_relations(geometry_msgs::TransformStamped T1, geometry_msgs::TransformStamped T2) {

    //printf("Getting the tranforms here");
    float x1 = T1.transform.translation.x;
    float y1 = T1.transform.translation.y;
    float z1 = T1.transform.translation.z;
    float x2 = T2.transform.translation.x;
    float y2 = T2.transform.translation.y;
    float z2 = T2.transform.translation.z;
    float d; 
    d = sqrt(pow(x2 - x1, 2) +  
                pow(y2 - y1, 2) +  
                pow(z2 - z1, 2) * 1.0); 
    //std::cout << std::fixed; 
    //std::cout << std::setprecision(2); 
    //cout<< "Distance is" << d << "\n";
    if (d == 0.0 ) {
        if(not ecoin){
    	cout<< "Markers are exactly coincining" << d << "\n";
    	ecoin = true;
	abut = false;
	pcoin = false;
	away = false;
	}
    }
    else if (d == 1.0 ){
        if(not abut){
    	cout << "Markers are Abut" << d<< "\n";
    	abut = true;
	ecoin = false;
	pcoin = false;
	away = false;
	}
    }
    else if(d<1.0 and (not pcoin)){
        cout << " Markers are partially coinciding " << d<< "\n";
        pcoin = true;
        abut = false;
        ecoin = false;
        away = false;
    }
    else if(d > 1.0 and (not away)) {
        cout << "Markers are away from each other" << d << "\n";
        pcoin = false;
        abut = false;
        ecoin = false;
        away = true;
    }

}
int main(int argc, char** argv){
  ros::init(argc, argv, "listener");

  ros::NodeHandle node;

  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);

  ros::Rate rate(10000.0);
  while (node.ok()){
    geometry_msgs::TransformStamped transformStamped1;
    geometry_msgs::TransformStamped transformStamped2;
    try{
      transformStamped1 = tfBuffer.lookupTransform("my_frame1", "world",
                               ros::Time(0));
      transformStamped2 = tfBuffer.lookupTransform("my_frame2", "world",
                               ros::Time(0));
    }
    catch (tf2::TransformException &ex) {
      ROS_WARN("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }


    
    calculate_relations(transformStamped1, transformStamped2);
    rate.sleep();
  }
  return 0;
};
