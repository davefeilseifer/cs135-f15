#include <ros/ros.h>


int main( int argc, char* argv[] )
{
	ros::init(argc,argv,"robot_commander");
	ros::NodeHandle nh;
	ros::Rate loop_rate(10);

	while( ros::ok() )
	{
		ros::spinOnce();
	}

	return 0;
}
