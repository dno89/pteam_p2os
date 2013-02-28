#include <iostream>
#include <cmath>
#include <string>
#include <vector>

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
#include <base/gnuplot-iostream.h>
// #include <base/OutputMerger.h>
// #include "base/Common.h"

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-debug_node.log")

using namespace std;

class DebugNode {
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
	
	//drawing
	Gnuplot m_gp;
	
	
	void newPerception(const pteam_p2os::Perception& pls_msg) {
		m_perc_mutex.lock();
			m_perc_msg = pls_msg;
			m_new_flag = true;
		m_perc_mutex.unlock();
	}
	
public:
	DebugNode(): m_nh("behaviors_node"), m_new_flag(false), m_gp("gnuplot") {
		std::string perception_topic;
		
		// Reads params from file
		m_nh.param<std::string>("processed_ls_topic", perception_topic, "processed_ls");
		
		ROS_INFO("Subscribing to topic %s",perception_topic.c_str()); 
		m_perc_sub = m_nh.subscribe(perception_topic, 1, &DebugNode::newPerception, this);
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
		vector<pair<double, double>> points;
		for(int ii = 0; ii < perc_msg.laser.data.ranges.size(); ++ii) {
			double theta = perc_msg.laser.data.angle_min + ii*perc_msg.laser.data.angle_increment;
			double x = perc_msg.laser.data.ranges[ii]*cos(theta);
			double y = perc_msg.laser.data.ranges[ii]*sin(theta);
			
			points.push_back(make_pair(x, y));
		}
		
// 		m_gp << "plot '-' binary " << m_gp.binfmt(points) << "w points notitle\n";
// 		m_gp.sendBinary(points);
// 		m_gp.flush();
		m_gp << "plot '-' w points notitle\n";
		m_gp.send(points);
		m_gp.flush();
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