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

  
  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup zone...");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("It reached pickup zone!");
    ROS_INFO("Wait for 5 seconds...");
    // Wait 5 second to simulate pickup.
    ros::Duration(5.0).sleep();
  } else {
    ROS_INFO("The base failed to reach pickup zone for some reason");
  }

  goal.target_pose.header.stamp = ros::Time::now();

  // Second set the target of drop off zone.
  goal.target_pose.pose.position.x = -1.0;
  goal.target_pose.pose.position.y = -2.0;
  goal.target_pose.pose.orientation.w = 1.0;
  
  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off zone...");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("It reached drop off zone!");
    ros::Duration(5.0).sleep();
  } else {
    ROS_INFO("The base failed to reach drop off zone for some reason");
  }

  ros::spin();
  return 0;
}