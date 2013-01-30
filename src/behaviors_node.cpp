#include <iostream>
#include <cmath>
#include <string>

#include <boost/thread/mutex.hpp>

#include <ros/ros.h>
#include <pteam_p2os/ProcessedLS.h>
#include <pteam_p2os/RobotControl.h>
#include <geometry_msgs/Twist.h>


#include <behaviors/CollisionAvoidance.h>
#include <merger/SimpleMerger.h>
#include <base/DMDebug.h>
#include <base/CBehavior.h>
#include <base/BehaviorManager.h>
// #include <base/OutputMerger.h>
// #include "base/Common.h"

CREATE_DEBUG_LOG("/tmp/behaviors_node.log",)

///TODO: definire il tipo per la richiesta al robot control server nel file srv/RobotControl.srv

class DummyBehavior : public pteam::CBehavior<double, double> {
public:
    ~DummyBehavior() {};
    double operator() ( const double& in, bool* subsume = 0 ) {
		*subsume = true;
		return std::pow(in, 3);
	}
};

class BehaviorsNode {
private:
	//the node handler
	ros::NodeHandle m_nh;
	
	//the Processed Laser Scanner (PLS) subscriber
	ros::Subscriber m_pls_sub;
	//the last processed input
	pteam_p2os::ProcessedLS m_pls_msg;
	//mutex to read/write the message
	boost::mutex m_pls_mutex;
	//flag that indicate a new scan to process
	bool m_new_flag;
	
	//the client for RobotControl service
	ros::ServiceClient m_rc_client;
	
	//behaviors manager
	///TODO: tolgo il DummyMerger e ne definisco uno vero!!
	pteam::BehaviorManager<pteam_p2os::ProcessedLS, pteam_p2os::RobotControlRequest, pteam::SimpleMerger> m_behaviors_manager;
	
	
	void newLaserScan(const pteam_p2os::ProcessedLS& pls_msg) {
		m_pls_mutex.lock();
			m_pls_msg = pls_msg;
			m_new_flag = true;
		m_pls_mutex.unlock();
	}
	
public:
	BehaviorsNode(): m_nh("behaviors_node"), m_new_flag(false) {
		std::string processed_ls_topic;
		std::string robot_control_service;
		
		// Reads params from file
		m_nh.param<std::string>("processed_ls_topic", processed_ls_topic, "processed_ls");
		m_nh.param<std::string>("robot_control_service", robot_control_service, "robot_control_service");
		
		ROS_INFO("Subscribing to topic %s",processed_ls_topic.c_str()); 
		m_pls_sub = m_nh.subscribe(processed_ls_topic, 1, &BehaviorsNode::newLaserScan, this);
		
		
		ROS_INFO("Using service %s",robot_control_service.c_str()); 
		m_rc_client = m_nh.serviceClient<pteam_p2os::RobotControl>(robot_control_service);
		
		///TODO: costruisco la catena dei behaviors!!!
	}
	
	~BehaviorsNode() { /* do nothing*/ }
	
	void ExecuteBehaviors() {
		bool new_flag;
		pteam_p2os::ProcessedLS pls_msg;
		
		m_pls_mutex.lock();
			new_flag = m_new_flag;
			if(new_flag) {
				pls_msg = m_pls_msg;
				m_new_flag = false;
			}
		m_pls_mutex.unlock();
		
		if(!new_flag) {
			//no new data to process
			return;
		}
		
		//there's a new processed input
		pteam_p2os::RobotControl rc_server;
		//obtain a request
		rc_server.request = m_behaviors_manager.RunBehaviors(pls_msg);
		
		//submit the request to the server
		if(!m_rc_client.call(rc_server)) {
			ROS_ERROR("BehaviorsNode ERROR: invalid response from server!");
		}
		
		//done
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
	pteam::CollisionAvoidance ca;
	ros::init (argc, argv, "behaviors_node");
	BehaviorsNode bn;  
	ros::Rate loop_rate(10);
	while (ros::ok()) {
		ros::spinOnce();
		bn.ExecuteBehaviors();
		loop_rate.sleep();
	}
	return (0);
}

