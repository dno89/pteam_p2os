#include <iostream>
#include <cmath>
#include <string>
#include <iterator>
#include <algorithm>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <boost/thread/mutex.hpp>

//this is a message format definition
#include <pteam_p2os/ProcessedLS.h>


#include "base/DMDebug.h"
// #include "base/Common.h"

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-sensing_node.log")

///TODO: definire il formato del messaggio ProcessedLS nel file msg/ProcessedLS.msg! Consultare la wiki per i tipi disponibili!

class SensingNode {
private:
	//the node handler
	ros::NodeHandle m_nh;
	
	//the scan subscriber
	ros::Subscriber m_scan_sub;
	//the last scan message
	sensor_msgs::LaserScan m_scan_msg;
	//mutex to read/write the message
	boost::mutex m_scan_mutex;
	//flag that indicate a new scan to process
	bool m_new_flag;
	
	
	//processed input publisher
	ros::Publisher m_processed_ls_pub;
	
	void newLaserScan(const sensor_msgs::LaserScan& scan_msg) {
		m_scan_mutex.lock();
			m_scan_msg = scan_msg;
			m_new_flag = true;
		m_scan_mutex.unlock();
	}
	
public:
	SensingNode(): m_nh("sensing_node"), m_new_flag(false) {
		std::string scan_topic;
		std::string processed_ls_topic;
		
		// Reads params from file
		m_nh.param<std::string>("scan_topic", scan_topic, "/scan");
		m_nh.param<std::string>("processed_ls_topic", processed_ls_topic, "/processed_ls");
		
		ROS_INFO("Subscribing to topic %s",scan_topic.c_str()); 
		m_scan_sub = m_nh.subscribe(scan_topic, 1, &SensingNode::newLaserScan, this);
		
		ROS_INFO("Advertising topic %s",processed_ls_topic.c_str()); 
		m_processed_ls_pub = m_nh.advertise<pteam_p2os::ProcessedLS>(processed_ls_topic, 1);
	}
	
	~SensingNode() { /* do nothing*/ }
	
	void ProcessInput() {
		sensor_msgs::LaserScan scan_msg;
		bool new_flag;
		
		m_scan_mutex.lock();
			new_flag = m_new_flag;
			if(new_flag) {
				scan_msg = m_scan_msg;
				m_new_flag = false;
			}
		m_scan_mutex.unlock();
		
		if(!new_flag) {
			//no new input to process
			return;
		}
		
		//there's input to process
		pteam_p2os::ProcessedLS pls;
		
		//do some senseless shit with scan_msg and fill pls ....
		///TODO: inserire qua il codice per processare scan_msg e riempire pls
		
// 		std::copy(scan_msg.ranges.begin(), scan_msg.ranges.end(), std::ostream_iterator<float>(std::cout, ", "));
		pls.data = scan_msg;
		
		//ok, done? then publish a new message
		
		//publish a new message
		m_processed_ls_pub.publish(boost::shared_ptr<pteam_p2os::ProcessedLS> (new pteam_p2os::ProcessedLS(pls)));
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
	ros::init (argc, argv, "sensing_node");
	
	SensingNode sn;
	
	ros::Rate loop_rate(10);
	
	while (ros::ok()) {
		ros::spinOnce();
			sn.ProcessInput();
		loop_rate.sleep();
	}
	return (0);
}


