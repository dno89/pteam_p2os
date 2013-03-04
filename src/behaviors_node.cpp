#include <iostream>
#include <cmath>
#include <string>

#include <boost/thread/mutex.hpp>

#include <ros/ros.h>
#include <pteam_p2os/Perception.h>
#include <pteam_p2os/RobotControl.h>
#include <geometry_msgs/Twist.h>


////behaviors
#include <behaviors/CollisionAvoidance.h>
#include <behaviors/StayInTheMiddle.h>
////merger
#include <merger/SimpleMerger.h>
////common
#include <base/DMDebug.h>
#include <base/CBehavior.h>
#include <base/BehaviorManager.h>
// #include <base/OutputMerger.h>
// #include "base/Common.h"

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-behaviors_node.log")

///TODO: definire il tipo per la richiesta al robot control server nel file srv/RobotControl.srv

class DummyBehavior : public pteam::CBehavior<pteam_p2os::Perception, pteam_p2os::RobotControlRequest> {
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
	ros::Subscriber m_perc_sub;
	//the last processed input
	pteam_p2os::Perception m_perc_msg;
	//mutex to read/write the message
	boost::mutex m_perc_mutex;
	//flag that indicate a new scan to process
	bool m_new_flag;
	
	//the client for RobotControl service
	ros::ServiceClient m_rc_client;
	
	//behaviors manager
	///TODO: tolgo il DummyMerger e ne definisco uno vero!!
	pteam::BehaviorManager<pteam_p2os::Perception, pteam_p2os::RobotControlRequest, pteam::SimpleMerger> m_behaviors_manager;
// 	pteam::BehaviorManager<double, double, pteam::SimpleMerger> m_behaviors_manager;
	
	
	void newLaserScan(const pteam_p2os::Perception& pls_msg) {
		m_perc_mutex.lock();
			m_perc_msg = pls_msg;
			m_new_flag = true;
		m_perc_mutex.unlock();
	}
	
public:
	BehaviorsNode(): m_nh("behaviors_node"), m_new_flag(false) {
		std::string processed_ls_topic;
		std::string robot_control_service;
		
		// Reads params from file
		m_nh.param<std::string>("processed_ls_topic", processed_ls_topic, "processed_ls");
		m_nh.param<std::string>("robot_control_service", robot_control_service, "robot_control_service");
		
		ROS_INFO("Subscribing to topic %s",processed_ls_topic.c_str()); 
		m_perc_sub = m_nh.subscribe(processed_ls_topic, 1, &BehaviorsNode::newLaserScan, this);
		
		
		ROS_INFO("Using service %s",robot_control_service.c_str()); 
		m_rc_client = m_nh.serviceClient<pteam_p2os::RobotControl>(robot_control_service);
		
		///TODO: costruisco la catena dei behaviors!!!
		m_behaviors_manager.AddBehaviorsLevel();
 		m_behaviors_manager.AddBehaviorsLevel();
		
		m_behaviors_manager.AddBehavior(0, new pteam::CollisionAvoidance(1.0, 0.4));
		//TODO add target detector
		
		m_behaviors_manager.AddBehavior(1, new pteam::StayInTheMiddle(4, 10)); 	///TODO: impostare le soglie!!!!!!
	}
	
	~BehaviorsNode() { /* do nothing*/ }
	
	void ExecuteBehaviors() {
		bool new_flag;
		pteam_p2os::Perception perc_msg;
		
		m_perc_mutex.lock();
			new_flag = m_new_flag;
			if(new_flag) {
				perc_msg = m_perc_msg;
				m_new_flag = false;
			}
		m_perc_mutex.unlock();
		
		if(!new_flag) {
			//no new data to process
			return;
		}
		
		//there's a new processed input
		pteam_p2os::RobotControl rc_server;
		//obtain a request
		rc_server.request = m_behaviors_manager.RunBehaviors(perc_msg);
		
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


