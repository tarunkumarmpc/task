
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
using namespace std;
 // float  x [5] = { 0.833, -0.833, -0.833, 0.833}; 
 // float y [5] = {0.25, 0.25, 0.25, -0.25};
 // float w[5] = {0.87, 0.87, 0.87, 0.87};

 float  x [5] = { 10, -10, -10, 10}; 
 float y [5] = {3, 3, -3, -3};
 float w[5] = {0.87, 0.87, 0.87, 0.87};

int lenght0f_Array = sizeof(x) / sizeof(x[0]);


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");
   ros::NodeHandle nh;
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("tb3_0/move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

bool status = true;
while(status) {
  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
   for( int i = 0; i < lenght0f_Array; i = i + 1 ) {
   goal.target_pose.pose.position.x = x[i]/12;
        goal.target_pose.pose.position.y = y[i]/10;
          goal.target_pose.pose.orientation.z = w[i];
     std::cout << "sending goal number " << i << std::endl;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("goal reached  %d", i);
  else
    ROS_INFO("goal failed  some reason");
}
if(!ros::ok()) {
        status = false;
    }  
}
  
  return 0;

}