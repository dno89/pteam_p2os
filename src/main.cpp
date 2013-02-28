#include <iostream>
#include <cmath>
#include <string>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

#include "base/DMDebug.h"

CREATE_DEBUG_LOG("/tmp/pteam-debug.log",)

#include "base/CBehavior.h"
#include "base/BehaviorManager.h"
#include "base/OutputMerger.h"
#include "base/Common.h"

class DummyBehavior : public CBehavior<double, double> {
public:
    ~DummyBehavior() {};
    double operator() ( const double& in, bool* subsume = 0 ) {
		*subsume = true;
		return std::pow(in, 3);
	}
};

class HelloP2os
{
public:
	ros::NodeHandle nh_;
	ros::Subscriber scan_sub_;
	sensor_msgs::LaserScan scan_;
	ros::Publisher vel_pub_;
	geometry_msgs::Twist cmd;
	
	HelloP2os(): nh_ ("~")
	{
		std::string scan_topic;
		std::string cmd_vel_topic;
		
		// Reads params from file
		nh_.param<std::string>("scan_topic", scan_topic, "/scan");
		nh_.param<std::string>("cmd_vel_topic", cmd_vel_topic, "/cmd_vel");
		
		ROS_INFO("Subscribing to topic %s",scan_topic.c_str()); 
		scan_sub_ = nh_.subscribe (scan_topic, 1, &HelloP2os::newLaserScan, this);
		cmd.linear.x=0;
		cmd.linear.y=0;
		cmd.linear.z=0;
		cmd.angular.x=0;
		cmd.angular.y=0;
		cmd.angular.z=0;
		ROS_INFO("Advertising topic %s",cmd_vel_topic.c_str()); 
		vel_pub_ = nh_.advertise<geometry_msgs::Twist>(cmd_vel_topic, 1);
	}
	
	~HelloP2os() { /* do nothing*/ }
	
	void newLaserScan(const sensor_msgs::LaserScan& scan_msg) 
	{
		scan_ = scan_msg;
	}
	
	void stayInTheMiddleDummy() {
		double turn = 0.0;
		int left = 0.0;
		int right = scan_.ranges.size() / 2 + 1;
		
		// Finds the minimum range on left 
		for (int i = 0; i < scan_.ranges.size() / 2; ++i) {
			if (scan_.ranges[i] < scan_.ranges[left]) {
				left = i;
			}
		} 
		// Finds the minimum range on right 
		for (int i = scan_.ranges.size()/2 + 1; i < scan_.ranges.size(); ++i) {
			if (scan_.ranges[i] < scan_.ranges[right]) {
				right = i;
			}
		}
		
		if(!scan_.ranges.empty()!=0) {
			turn = 0.1 * (scan_.ranges[right] - scan_.ranges[left]);
		}
		cmd.linear.x = 0.2;
		cmd.linear.y = 0.0;
		cmd.angular.z = turn;
		vel_pub_.publish(cmd); 
	}
};


int main (int argc, char** argv)
{
	///SECTION BehaviorManager test
	BehaviorManager<double, double, DummyMerger> bm;
	bm.AddBehaviorsLevel();
	bm.AddBehavior(0, new DummyBehavior());
	
	///SECTION Value test
	Value<int> i = 0.0;
	DEBUG_T(i == UndefinedValue,)
	DEBUG_T(i,)
	DEBUG_T(i < 5,)
	i = 9;
	int j = 4;
	DEBUG_T(i >= j,)
	
	ros::init (argc, argv, "hello_p2os");
	HelloP2os hp;  
	ros::Rate loop_rate(10);
	while (ros::ok()) {
		ros::spinOnce();
		hp.stayInTheMiddleDummy();
		loop_rate.sleep();
	}
	return (0);
}


