#include <ros/ros.h>
#include <std_msgs/String.h>
#include <visualization_msgs/Marker.h>

class Marker {
 private:
  ros::Publisher marker_pub_;
  ros::NodeHandle* handler_;
 public:
  Marker(ros::NodeHandle* h) {
    handler_ = h;
    marker_pub_ = handler_->advertise<visualization_msgs::Marker>("add_markers", 1);
  }
  
  visualization_msgs::Marker create_cube_marker() {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
  
    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;
  
    marker.type = visualization_msgs::Marker::CUBE;;
  
    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
 
    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.25;
    marker.scale.y = 0.25;
    marker.scale.z = 0.25;
 
    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
  
    marker.lifetime = ros::Duration();
    return marker;
  }

  void draw_cube() {
    visualization_msgs::Marker marker = create_cube_marker();
    marker.pose.position.x = 1;
    marker.pose.position.y = 1;
    marker.pose.position.z = 0;
    marker.action = visualization_msgs::Marker::ADD;
  
    // Publish the marker
    while (marker_pub_.getNumSubscribers() < 1){
      if (!ros::ok()){
        return;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    ROS_INFO("publish the cube!");
    marker_pub_.publish(marker);
  }
  
  void reachPickupZoneCallback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("I heard: [%s]", msg->data.c_str());
    ROS_INFO("reach the pickup zone!");
    visualization_msgs::Marker marker = create_cube_marker();
    marker.pose.position.x = 1;
    marker.pose.position.y = 1;
    marker.pose.position.z = 0;
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub_.publish(marker);
  }
  
  void reachDropOffZoneCallback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("I heard: [%s]", msg->data.c_str());
    ROS_INFO("reach the dropoff zone!");
    visualization_msgs::Marker marker = create_cube_marker();
    marker.pose.position.x = -1;
    marker.pose.position.y = -2;
    marker.pose.position.z = 0;
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub_.publish(marker);
  }
};

int main( int argc, char** argv ) {
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  
  Marker marker(&n);
  marker.draw_cube();
  
  ros::Subscriber pickup_sub = n.subscribe("reach_pickup_zone", 1000, &Marker::reachPickupZoneCallback, &marker);
  ros::Subscriber dropoff_sub = n.subscribe("reach_dropoff_zone", 1000, &Marker::reachDropOffZoneCallback, &marker);
  ros::spin();
  return 0;
}