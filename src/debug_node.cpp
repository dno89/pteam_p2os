#include <iostream>
#include <cmath>
#include <string>

#include <boost/thread/mutex.hpp>

#include <ros/ros.h>
#include <pteam_p2os/Perception.h>
#include <pteam_p2os/RobotControl.h>
#include <geometry_msgs/Twist.h>


#include <behaviors/CollisionAvoidance.h>
#include <merger/SimpleMerger.h>
#include <base/DMDebug.h>
#include <base/CBehavior.h>
#include <base/BehaviorManager.h>
// #include <base/OutputMerger.h>
// #include "base/Common.h"

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-debug_node.log")

class DebugNode {
private:
	//the node handler
	ros::NodeHandle m_nh;
	
	//the Processed Laser Scanner (PLS) subscriber
	ros::Subscriber m_pls_sub;
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
	
	
	void newPerception(const pteam_p2os::Perception& pls_msg) {
		m_perc_mutex.lock();
			m_perc_msg = pls_msg;
			m_new_flag = true;
		m_perc_mutex.unlock();
	}
	
public:
	DebugNode(): m_nh("behaviors_node"), m_new_flag(false) {
		std::string perception_topic;
		
		// Reads params from file
		m_nh.param<std::string>("processed_ls_topic", perception_topic, "processed_ls");
		
		ROS_INFO("Subscribing to topic %s",processed_ls_topic.c_str()); 
		m_pls_sub = m_nh.subscribe(processed_ls_topic, 1, &DebugNode::newPerception, this);
	}
	
	~DebugNode() { /* do nothing*/ }
	
	void Update() {
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
		
		//new perception update the drawing
	}
};


int main (int argc, char** argv)
{
	ros::init (argc, argv, "behaviors_node");
	DebugNode bn;  
	ros::Rate loop_rate(10);
	while (ros::ok()) {
		ros::spinOnce();
		bn.Update();
		loop_rate.sleep();
	}
	return (0);
}