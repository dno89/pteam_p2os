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
#include <behaviors/TargetDetector.h>
#include <behaviors/MoveThroughwardGoal.h>
#include <behaviors/TakeTheBall.h>
////merger
#include <merger/SimpleMerger.h>
////common
#include <base/DMDebug.h>
#include <base/CBehavior.h>
#include <base/BehaviorManager.h>
// #include <base/OutputMerger.h>
// #include "base/Common.h"

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-behaviors_node.log")

#ifdef	TURBO_MODE
#warning ## TURBO MODE ENABLED ##
#endif	//TURBO_MODE

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
	pteam::BehaviorManager<pteam_p2os::Perception, pteam_p2os::RobotControlRequest, pteam::SimpleMerger> m_behaviors_manager;
	
	bool m_first_time;
	
	void newLaserScan(const pteam_p2os::Perception& pls_msg) {
		m_perc_mutex.lock();
			m_perc_msg = pls_msg;
			m_new_flag = true;
		m_perc_mutex.unlock();
	}
	
public:
	BehaviorsNode(): m_nh("behaviors_node"), m_new_flag(false), m_first_time(true) {
		std::string processed_ls_topic;
		std::string robot_control_service;
		
		// Reads params from file
		m_nh.param<std::string>("processed_ls_topic", processed_ls_topic, "processed_ls");
		m_nh.param<std::string>("robot_control_service", robot_control_service, "robot_control_service");
		
		ROS_INFO("Subscribing to topic %s",processed_ls_topic.c_str()); 
		m_perc_sub = m_nh.subscribe(processed_ls_topic, 1, &BehaviorsNode::newLaserScan, this);
		
		
		ROS_INFO("Using service %s",robot_control_service.c_str()); 
		m_rc_client = m_nh.serviceClient<pteam_p2os::RobotControl>(robot_control_service);
		
		m_behaviors_manager.AddBehaviorsLevel();
		m_behaviors_manager.AddBehaviorsLevel();
		m_behaviors_manager.AddBehaviorsLevel();
		
		m_behaviors_manager.AddBehavior(0, new pteam::TakeTheBall());
		
		double TD_ball_radius;
		m_nh.param<double>("TD_ball_radius", TD_ball_radius, double(0.1));
		m_behaviors_manager.AddBehavior(0, new pteam::TargetDetector(0.2, 0.1, 0.3, 0.1));
		
		double CA_alpha, CA_threshold;
		m_nh.param<double>("CA_alpha", CA_alpha, double(0.01));
// 		ROS_INFO("CA_alpha read, %f", CA_alpha);
		m_nh.param<double>("CA_threshold", CA_threshold, double(0.3));
// 		ROS_INFO("CA_threshold read, %f", CA_threshold);
		DEBUG_T(CA_alpha,)
		DEBUG_T(CA_threshold,)
		m_behaviors_manager.AddBehavior(1, new pteam::CollisionAvoidance(CA_alpha, CA_threshold));
		
		
		
		
		double SITM_threshold, SITM_alpha, SITM_learning_rate;
		int SITM_valley_threshold, SITM_nl_n;
		m_nh.param<double>("SITM_threshold", SITM_threshold, double(0.2));
		m_nh.param<double>("SITM_alpha", SITM_alpha, double(2.0));
		m_nh.param<double>("SITM_learning_rate", SITM_learning_rate, double(1.0));
		m_nh.param<int>("SITM_nl_n", SITM_nl_n, int(2));
		m_nh.param<int>("SITM_valley_threshold", SITM_valley_threshold, double(50));
		DEBUG_T(SITM_alpha,)
		DEBUG_T(SITM_threshold,)
		DEBUG_T(SITM_valley_threshold,)
		DEBUG_T(SITM_nl_n,)
		m_behaviors_manager.AddBehavior(2, new pteam::StayInTheMiddle(SITM_threshold, SITM_valley_threshold, SITM_alpha, SITM_nl_n, true, SITM_learning_rate));
		
		
		m_behaviors_manager.AddBehavior(2, new pteam::MoveThroughwardGoal(DEG_TO_RAD(2.0)));
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
		
		if(!new_flag && m_first_time) {
			//no new data to process
			
			DEBUG_P("EXITING BECAUSE OF NO VALID INPUT",)
			
			return;
		}
		
		if(!new_flag) {
			DEBUG_P("No new input!",)
		}
		
		m_first_time = false;
		
		//there's a new processed input
		pteam_p2os::RobotControl rc_server;
		//obtain a request
		rc_server.request = m_behaviors_manager.RunBehaviors(perc_msg);
		
		DEBUG_T(rc_server.request.angular_speed,)
		DEBUG_T(bool(rc_server.request.angular_speed_set), )
		DEBUG_T(rc_server.request.linear_speed,)
		DEBUG_T(bool(rc_server.request.linear_speed_set), )
		DEBUG_T(bool(rc_server.request.gripper_move_down), )
		DEBUG_T(bool(rc_server.request.gripper_move_set), )
		
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


