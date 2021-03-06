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
#include <base/Common.h>

// #include <base/OutputMerger.h>
// #include "base/Common.h"

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-debug_node.log")

using namespace std;

class DebugNode  {
private:	
	//the node handler
	ros::NodeHandle m_nh;
	
	//the Perception subscriber
	ros::Subscriber m_perc_sub;
	//the Laser scanner messages
	ros::Subscriber m_ls_sub;
	
	//the last processed input
	pteam_p2os::Perception m_perc_msg;
	//the last scan
	sensor_msgs::LaserScan m_ls_scan;
	
	//mutex to read/write the message
// 	boost::mutex m_perc_mutex;
	//flag that indicate a new scan to process
	bool m_new_flag;
	
	//drawing
	Gnuplot m_gp1/*, m_gp2*/;
	
	
	void newPerception(const pteam_p2os::Perception& pls_msg) {
// 		m_perc_mutex.lock();
			m_perc_msg = pls_msg;
			m_new_flag = true;
// 		m_perc_mutex.unlock();
	}
	
	void newLS(const sensor_msgs::LaserScan& ls_scan) {
		m_ls_scan = ls_scan;
	}
	
public:
	DebugNode(): m_nh("behaviors_node"), m_new_flag(false) {
		std::string perception_topic;
		std::string ls_topic;
		
		// Reads params from file
		m_nh.param<std::string>("processed_ls_topic", perception_topic, "processed_ls");
		ROS_INFO("Subscribing to topic %s",perception_topic.c_str()); 
		m_perc_sub = m_nh.subscribe(perception_topic, 1, &DebugNode::newPerception, this);
		
		m_nh.param<std::string>("scan_topic", ls_topic, "/robot_0/base_scan");
		ROS_INFO("Subscribing to topic %s",ls_topic.c_str()); 
		m_ls_sub = m_nh.subscribe(ls_topic, 1, &DebugNode::newLS, this);
	}
	
	~DebugNode() { /* do nothing*/ }
	
	void Update() {
		//new perception update the drawing
		vector<pair<double, double>> processed_points, points;
		for(int ii = 0; ii < m_perc_msg.laser.data.ranges.size(); ++ii) {
			if(isnan(m_perc_msg.laser.data.ranges[ii])) {
				continue;
			}
			
			double theta = /*m_perc_msg.laser.data.angle_min + */ii*m_perc_msg.laser.data.angle_increment;
			double x = m_perc_msg.laser.data.ranges[ii]*sin(theta);
			double y = -m_perc_msg.laser.data.ranges[ii]*cos(theta);
			
			processed_points.push_back(make_pair(-y, x));
		}
		
// 		m_gp << "plot '-' binary " << m_gp.binfmt(points) << "w points notitle\n";
// 		m_gp.sendBinary(points);
// 		m_gp.flush();
// 		m_gp1 << "set xrange [" << perc_msg.laser.data.range_max << " : " << -perc_msg.laser.data.range_max << "]\n";
		m_gp1 << "set xrange [-2:2]\n";
		m_gp1 << "set yrange [0:5]\n";
// 		m_gp1 << "set yrange [" << perc_msg.laser.data.range_max << " : " << -perc_msg.laser.data.range_max << "]\n";
// 		m_gp1 << "plot '-' with points linecolor rgb \"red\" title 'unfiltered data'\n";
// 		m_gp1.send(points);
// 		if(ReadProperty<bool>("TARGET_DETECTED")) {
// 			Point2d target = ReadProperty<Point2d>("TARGET_POSITION");
// 			std::vector<std::pair<double, double>> tv;
// 			tv.push_back(make_pair(-target.y, target.x));
// 			m_gp1 << m_gp1 << "plot '-' with points linecolor rgb \"green\" title 'filtered data', '-' with points linecolor rgb \"red\"\n";
// 			m_gp1.send(processed_points).send(tv);
// 		} else {
			m_gp1 << "plot '-' with points linecolor rgb \"green\" title 'filtered data'\n";
			m_gp1.send(processed_points);
// 		}
		m_gp1.flush();
		
// 		m_gp2 << "plot '-' with points linecolor rgb \"green\" title 'filtered data'\n";
// 		m_gp2.flush();
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