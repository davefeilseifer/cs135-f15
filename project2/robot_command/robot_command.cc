#include <ros/ros.h> 
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>
#include <stdio.h>

double robot_x, robot_y, robot_theta; // global variables that store the robot's state

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg); // cs135 can ignore, prototype for the odometry function

int main( int argc, char* argv[] )
{
	/************************************/
		// cs135: this code is used to intilize a connection to the simulator
		// you can ignore this block
	ros::init(argc,argv,"robot_commander");
	ros::NodeHandle nh;
	ros::Rate loop_rate(10);

	ros::Publisher cmd_vel = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1000);
	ros::Subscriber odom_sub = nh.subscribe("/base_pose_ground_truth",1000,odomCallback);
	geometry_msgs::Twist cmd_vel_msg;


	/************************************/


	double lvel = 0.0, rvel = 0.0; // changing these variables will change the linear and angular velocity of the robot

	// cs135: hmmm, how might we use these variables???
	char selection = ' ';
	int first_time = 0;

	double initial_x, initial_y;
	double initial_theta;
	double hyp;

	
	// this loop keeps going as long as the connection to the simulator still works
	// and we have not hit ctrl-c to quit

	while( ros::ok() ) 
	{





		/************************************/
			// cs135: this code is used to send data to the simulator to drive the robot
			// you can ignore this block

		// build a message with lvel as linear velocity, and rvel as angular velocity
		cmd_vel_msg.linear.x = lvel;
		cmd_vel_msg.angular.z = rvel;
		
		// publish message
		cmd_vel.publish(cmd_vel_msg);

		// send/receive/sleep
		ros::spinOnce();
		loop_rate.sleep();
	
		/************************************/
	} // while( ros::ok() )

	return 0;
}

// turns a quaternion into a yaw angle for the robot
// cs135: you can ignore this function
double getRotationFromMsg( geometry_msgs::Quaternion q )
{
  double yaw;
  yaw = tf::getYaw(q);
  return yaw;
}

// this function is called whenever odometry information is received from the simulator
// cs135: you can ignore this function
void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  robot_x = msg->pose.pose.position.x;
  robot_y = msg->pose.pose.position.y;
  robot_theta = getRotationFromMsg(msg->pose.pose.orientation);
}
