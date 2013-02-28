#include <iostream>
#include <cmath>
#include <string>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <boost/thread/mutex.hpp>

//this is a message format definition
#include <pteam_p2os/ProcessedLS.h>
#include <pteam_p2os/Perception.h>


#include "base/DMDebug.h"
#include "base/Common.h"



CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-sensing_node.log")

class SensingNode {
private:
	//the node handler
	ros::NodeHandle m_nh;
	
	//the scan subscriber
	ros::Subscriber m_scan_sub;
	//the last scan message
	sensor_msgs::LaserScan m_scan_msg;
	
	//the odometry subscriber
	ros::Subscriber m_odom_sub;
	//last odometry message
	nav_msgs::Odometry m_odom_msg;
	
	//mutex to read/write odometry and laser scan
	boost::mutex m_mutex;
	//flag that indicate a new scan or odometry to process
	bool m_new_flag;
	
	//processed input publisher
	ros::Publisher m_processed_ls_pub;
	
	//the campled value of the FOV > 0 in radians
	double m_clamp_angle;
	//the distance threshold to detect discontinuity
	double m_distance_threshold;
	//the size (in points) of the filtered segment
	int m_min_segment_lengh;
	
	void newLaserScan(const sensor_msgs::LaserScan& scan_msg) {
		m_mutex.lock();
			m_scan_msg = scan_msg;
			m_new_flag = true;
		m_mutex.unlock();
	}
	
	void newOdom(const nav_msgs::Odometry& odom_msg) {
		m_mutex.lock();
			m_odom_msg = odom_msg;
			m_new_flag = true;
		m_mutex.unlock();
	}
	
public:
	SensingNode(): m_nh("sensing_node"), m_new_flag(false) {
		std::string scan_topic;
		std::string odom_topic;
		std::string processed_ls_topic;
		
		// Reads params from file
		m_nh.param<std::string>("scan_topic", scan_topic, "scan_base");
		
		m_nh.param<std::string>("odom_topic", odom_topic, "odom");
		
		m_nh.param<std::string>("processed_ls_topic", processed_ls_topic, "/processed_ls");
		
		double clamp_angle_deg;
		m_nh.param<double>("clamp_angle_degree", clamp_angle_deg, 90.0);
		m_clamp_angle = DEG_TO_RAD(clamp_angle_deg);
		
		m_nh.param<double>("distance_threshold", m_distance_threshold, 0.1);
		
		m_nh.param<int>("min_segment_lenght", m_min_segment_lengh, 4);
		
		
		ROS_INFO("Subscribing to topic %s",scan_topic.c_str()); 
		m_scan_sub = m_nh.subscribe(scan_topic, 1, &SensingNode::newLaserScan, this);
		
		ROS_INFO("Subscribing to topic %s",odom_topic.c_str()); 
		m_odom_sub = m_nh.subscribe(odom_topic, 1, &SensingNode::newOdom, this);
		
		ROS_INFO("Advertising topic %s",processed_ls_topic.c_str()); 
		m_processed_ls_pub = m_nh.advertise<pteam_p2os::Perception>(processed_ls_topic, 1);
		
		
	}
	
	~SensingNode() { /* do nothing*/ }
	
	void ProcessInput() {
		sensor_msgs::LaserScan scan_msg;
		nav_msgs::Odometry odom_msg;
		bool new_flag;
		
		m_mutex.lock();
			new_flag = m_new_flag;
			if(new_flag) {
				scan_msg = m_scan_msg;
				odom_msg = m_odom_msg;
				m_new_flag = false;
			}
		m_mutex.unlock();
		
		if(!new_flag) {
			//no new input to process
			return;
		}
		
		//there's input to process
		pteam_p2os::Perception percept;
		
		//do some senseless shit with scan_msg and fill pls ....
		///TODO: inserire qua il codice per processare scan_msg e riempire pls

		
		
		/************************************************************/
		
#ifdef ON_SIMULATION
#warning ##SIMULATION ENABLED##

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();  
		std::default_random_engine generator (seed);
		std::normal_distribution<double>distribution(0.0, 0.01);   
		
		//Mi riporto al caso del robot
		std::reverse(scan_msg.ranges.begin(),scan_msg.ranges.end());    
		
		//Aggiunta rumore gaussiano alle misure del simulatore
		for (int i=0; i<scan_msg.ranges.size(); ++i)
		{
			if(generator() % 1000 == 0) {
				//unlucky scan
				scan_msg.ranges[i] = 0.0;
			} else {
				scan_msg.ranges[i] = scan_msg.ranges[i] + distribution(generator); 
			}
		}
		
#endif	//ON_SIMULATION
		
		//ROBOT
		
		//flip the scan
		std::reverse(scan_msg.ranges.begin(),scan_msg.ranges.end());
		
		//clamp the FOV
		if(scan_msg.angle_max > m_clamp_angle) {
			int min_index = (-m_clamp_angle - scan_msg.angle_min) / scan_msg.angle_increment;
			int max_index = (m_clamp_angle - scan_msg.angle_min) / scan_msg.angle_increment;
			//clamp the value
			scan_msg.ranges = sensor_msgs::LaserScan::_ranges_type(scan_msg.ranges.begin()+min_index, scan_msg.ranges.begin()+max_index+1);
			//set the bound
			scan_msg.angle_min = -m_clamp_angle;
			scan_msg.angle_max = m_clamp_angle;
		}
		
		//outlier and isolated segment filtering
		int count = 0;
		int first_index = 0;
		for(int ii = 0; ii < scan_msg.ranges.size()-1; ++ii) {
			if(scan_msg.ranges[ii] < scan_msg.range_min || scan_msg.ranges[ii] > scan_msg.range_max) {
				scan_msg.ranges[ii] = NAN;
				continue;
			}
			
			if(std::abs(scan_msg.ranges[ii] - scan_msg.ranges[ii+1]) > m_distance_threshold) {
				if(count < m_min_segment_lengh) {
					for(int jj = first_index; jj <= ii; ++jj) {
						scan_msg.ranges[jj] = NAN;
					}
					count = 0;
				} else {
					count = 1;
				}
				first_index = ii+1;
			} else {
				++count;
			}
		}
		//check the last element
		if(scan_msg.ranges.back() < scan_msg.range_min || scan_msg.ranges.back() > scan_msg.range_max) {
			scan_msg.ranges.back() = NAN;
		}
		
		
		
		/************************************************************/
		
		
// 		std::copy(scan_msg.ranges.begin(), scan_msg.ranges.end(), std::ostream_iterator<float>(std::cout, ", "));
		percept.laser.data = scan_msg;
		percept.odometry = odom_msg;
		
		//ok, done? then publish a new message
		
		//publish a new message
		m_processed_ls_pub.publish(boost::shared_ptr<pteam_p2os::Perception> (new pteam_p2os::Perception(percept)));
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


