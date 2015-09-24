#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main( int argc, char* argv[] )
{
	ros::init(argc,argv,"robot_commander");
	ros::NodeHandle nh;
	ros::Rate loop_rate(10);

	ros::Publisher cmd_vel = nh.advertise<geometry_msgs::Twist>("/robot_0/cmd_vel",1000);
	geometry_msgs::Twist cmd_vel_msg;

	double lvel = 0.0, rvel = 0.0;

	while( ros::ok() )
	{




		// build a message with lvel as linear velocity, and rvel as angular velocity
		cmd_vel_msg.linear.x = lvel;
		cmd_vel_msg.angular.z = rvel;
		
		// publish message
		cmd_vel.publish(cmd_vel_msg);

		// send/receive/sleep
		ros::spinOnce();
		loop_rate.sleep();

	}

	return 0;
}
