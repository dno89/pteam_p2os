#include <iostream>
#include <cmath>
#include <string>

#include <boost/thread/mutex.hpp>

#include <ros/ros.h>
#include <pteam_p2os/RobotControl.h>
#include <geometry_msgs/Twist.h>


#include "base/DMDebug.h"
// #include "base/CBehavior.h"
// #include "base/BehaviorManager.h"
// #include "base/OutputMerger.h"
// #include "base/Common.h"

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-control_node.log")

class ControlNode {
private:
	//the node handler
	ros::NodeHandle m_nh;
	
	//the server for RobotControl service
	ros::ServiceServer m_rc_server;
	
	//the last request
	pteam_p2os::RobotControlRequest m_last_request;
	//mutex for mutual exclusion
	boost::mutex m_lr_mutex;
	
	//a publisher to actually control the robot
	ros::Publisher m_rc_publisher;
	
	bool handleRequest(pteam_p2os::RobotControlRequest& req, pteam_p2os::RobotControlResponse& res) {
		///TODO: handle the response here
		///TODO: se si accede a qualche dato sicuramente serve anche un bel mutex
		
		DEBUG_P("handleRequest called",)
		DEBUG_T(req.angular_speed,)
		DEBUG_T(req.linear_speed,)
		
		m_lr_mutex.lock();
			m_last_request = req;
		m_lr_mutex.unlock();
		
		return true;
	}
	
public:
	ControlNode(): m_nh("control_node") {
		std::string robot_control_service;
		std::string robot_control_topic;
		
		// Reads params from file
		m_nh.param<std::string>("robot_control_service", robot_control_service, "robot_control_service");
		
		boost::function<bool (pteam_p2os::RobotControlRequest&, pteam_p2os::RobotControlResponse&)> fp;
		fp = boost::bind(&ControlNode::handleRequest, this, _1, _2);
		
		m_rc_server = m_nh.advertiseService(robot_control_service, fp);
		
		ROS_INFO("Providing service %s",robot_control_service.c_str()); 
		
		m_nh.param<std::string>("robot_control_topic", robot_control_topic, "robot_control");
		
		ROS_INFO("Advertising topic %s",robot_control_topic.c_str()); 
		m_rc_publisher = m_nh.advertise<geometry_msgs::Twist>(robot_control_topic, 1);
		
		//reset the command
		m_last_request.linear_speed = 0.0f;
		m_last_request.angular_speed = 0.0f;
	}
	
	~ControlNode() { /* do nothing*/ }
	
	void Update() {
		///TODO il controllo si fa dove riceviamo la risposta o da un altra parte???
		
		pteam_p2os::RobotControlRequest last_request;
		
		m_lr_mutex.lock();
			last_request = m_last_request;
		m_lr_mutex.unlock();
		
		geometry_msgs::Twist control_input;
		
		control_input.angular.x = control_input.angular.y = 0.0;
		control_input.angular.z = last_request.angular_speed;
		
		control_input.linear.x = last_request.linear_speed;
		control_input.linear.y = control_input.linear.z = 0.0;
		
		m_rc_publisher.publish(control_input);
	}
	
	// 	void stayInTheMiddleDummy() {
		// 		double turn = 0.0;
		// 		int left = 0.0;
		// 		int right = scan_.ranges.size() / 2 + 1;
		// 		
		// 		// Finds the minimum range on left 
		// 		for (int i = 0; i < scan_.ranges.size() / 2; ++i) {
			// 			if (scan_.ranges[i] < scan_.ranges[left]) {
				// 				left = i;
				// 			}
				// 		} 
				// 		// Finds the minimum range on right 
				// 		for (int i = scan_.ranges.size()/2 + 1; i < scan_.ranges.size(); ++i) {
					// 			if (scan_.ranges[i] < scan_.ranges[right]) {
						// 				right = i;
						// 			}
						// 		}
						// 		
						// 		if(!scan_.ranges.empty()!=0) {
							// 			turn = 0.1 * (scan_.ranges[right] - scan_.ranges[left]);
							// 		}
							// 		cmd.linear.x = 0.2;
							// 		cmd.linear.y = 0.0;
							// 		cmd.angular.z = turn;
							// 		vel_pub_.publish(cmd); 
							// 	}
};


int main (int argc, char** argv)
{
	ros::init (argc, argv, "behaviors_node");
	ControlNode cn;  
	ros::Rate loop_rate(100);
	while (ros::ok()) {
		ros::spinOnce();
		cn.Update();
		loop_rate.sleep();
	}
	return (0);
}


