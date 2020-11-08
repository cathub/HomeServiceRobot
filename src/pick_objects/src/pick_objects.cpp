#include <ros/ros.h>
#include <std_msgs/String.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  // First set the target of pickup zone.
  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 1.0;
  goal.target_pose.pose.position.y = 1.0;
  goal.target_pose.pose.orientation.w = 1.0;

  // publisher for the reach pickup zone.
  ros::Publisher reach_pickup_pub = n.advertise<std_msgs::String>("reach_pickup_zone", 1000);
  while(reach_pickup_pub.getNumSubscribers() <=0 ) {
    sleep(1); 
  }
  
  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup zone...");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    std_msgs::String msg;
    std::stringstream ss;
    ss << "It reached pickup zone!";
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());

    ROS_INFO("Wait for 5 seconds...");
    // Wait 5 second to simulate pickup.
    ros::Duration(5.0).sleep();
    reach_pickup_pub.publish(msg);
  } else {
    ROS_INFO("The base failed to reach pickup zone for some reason");
  }

  goal.target_pose.header.stamp = ros::Time::now();

  // Second set the target of drop off zone.
  goal.target_pose.pose.position.x = -1.0;
  goal.target_pose.pose.position.y = -2.0;
  goal.target_pose.pose.orientation.w = 1.0;

  // publisher for the reach pickup zone.
  ros::Publisher reach_dropoff_pub = n.advertise<std_msgs::String>("reach_dropoff_zone", 1000);
  while(reach_dropoff_pub.getNumSubscribers() <=0 ) {
    sleep(1); 
  }
  
  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off zone...");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    std_msgs::String msg;
    std::stringstream ss;
    ss << "It reached drop off zone!";
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());

    reach_dropoff_pub.publish(msg);
    ros::Duration(5.0).sleep();
  } else {
    ROS_INFO("The base failed to reach drop off zone for some reason");
  }

  ros::spin();
  return 0;
}