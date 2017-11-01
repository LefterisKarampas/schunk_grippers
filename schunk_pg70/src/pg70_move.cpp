#include <ros/ros.h>
#include <schunk_pg70/set_position.h>
#include <cstdlib>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "pg70_set_position");
	if (argc != 4)
	{
		ROS_ERROR("usage: Goal_position->[0,68]mm, Velocity->[0,82]mm/s, Acceleration->[0,319]");
		return 1;
	}

	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<schunk_pg70::set_position>("schunk_pg70/set_position");
	schunk_pg70::set_position srv;
	double pos = atof(argv[1]);
	if(pos >69 || pos < 0){
		ROS_ERROR("Goal request respects position limits <0-68> mm");
		return 1;
	}
	srv.request.goal_position = pos;
	double vel = atof(argv[2]);
	if(vel >83 || vel < 0){
		ROS_ERROR("Goal request respects velocity limits <0-82> mm/s");
		return 1;
	}
	srv.request.goal_velocity = vel;
	double acc = atof(argv[3]);
	if(acc >320 || vel < 0){
		ROS_ERROR("Goal request respects acceleration limits <0-319> mm/s2 ");
		return 1;
	}
	srv.request.goal_acceleration = acc;  
	if (client.call(srv))
	{
		ROS_INFO("schunk_pg70 is moving to goal position!");
	}
	else
	{
		ROS_ERROR("Failed to call service for pg70 moving");
		return 1;
	}

	return 0;
} 
