/**
 * @file Behaviors.cpp
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief implementation
 */

#include "TargetDetector.h"
#include <base/DMDebug.h>
#include <Eigen/Dense>

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-behavior-target_detector.log")

using namespace pteam;

TargetDetector::TargetDetector ( double range_thr, double target_radius, double target_radius_toll, double accept_threshold ) : range_thr_(range_thr), target_radius_(target_radius), target_radius_toll_(target_radius_toll), m_have_hypothesis(false), m_ghost_mode(false), m_hage(0), m_gage(0), m_last_pose(), m_hypothesis(), m_accept_threshold2(accept_threshold) {
	
}


pteam_p2os::RobotControlRequest TargetDetector::operator() ( const pteam_p2os::Perception& in, bool* subsume ) {
	
// 	DEBUG_T(in.odometry.pose.pose, )
// 	SimplePose sp = OdomToSimplePose(in.odometry.pose.pose);
// 	DEBUG_T(sp.x,)
// 	DEBUG_T(sp.y,)
// 	DEBUG_T(RAD_TO_DEG(sp.theta),);

	///TODO: localize and track here!!
	Target t;
	SimplePose pose = OdomToSimplePose(in.odometry.pose.pose);
	if(detectCircle(in, &t)) {
		DEBUG_P("Circle detected!", ####)
		
		//a circle detected
		if(m_have_hypothesis) {
			//circle detected and hypothesis
			if(TargetDistance2(t, RotateTarget(m_hypothesis, m_last_pose, pose)) <= m_accept_threshold2) {
				//hypothesis confirmed
				DEBUG_P("Hypothesis confirmed!",####)
				
				m_ghost_mode = false;
				m_gage = 0;
				++m_hage;
				m_hypothesis = t;
				m_last_pose = pose;
			} else {
				//hypothesis and observation doesn't match
				
				DEBUG_P("Hypothesis and observation doesn't match!",####)
				if(m_ghost_mode) {
					++m_gage;
					
					if(m_gage > max_ghost_age()) {
						DEBUG_P("Clearing hypothesis due to ghost age expiration!",####)
						
						//clear the hypothesis
						m_have_hypothesis = false;
						m_gage = 0;
						m_hage = 0;
						m_ghost_mode = false;
					}
				} else if(m_hage >= min_age()) {
					
					DEBUG_P("Entering ghost mode!",####)
					
					m_ghost_mode = true;
					m_gage = 1;
				} else {
					DEBUG_P("Clearing hypothesis due to low age!",####)
					
					//clear the hypothesis
					m_have_hypothesis = false;
					m_gage = 0;
					m_hage = 0;
					m_ghost_mode = false;
				}
			}
			
		} else {
			//circle detected but no hypothesis
			
			DEBUG_P("New hypothesis!!",####)
			
			//new hypothesis
			m_have_hypothesis = true;
			//hypothesis age
			m_hage = 1;
			//pose in corrispondece of the hypothesis
			m_last_pose = OdomToSimplePose(in.odometry.pose.pose);
			//hypothesis
			m_hypothesis = t;
			//no ghost
			m_ghost_mode = false;
			m_gage = 0;
		}
	} else {
		DEBUG_P("--", ####)
		
		//no circle detected
		if(m_have_hypothesis) {
			//no circle detected and hypothesis
			if(m_ghost_mode) {
				++m_gage;
				
				if(m_gage > max_ghost_age()) {
					DEBUG_P("Clearing hypothesis due to ghost age expiration!",####)
						
					//clear the hypothesis
					m_have_hypothesis = false;
					m_gage = 0;
					m_hage = 0;
					m_ghost_mode = false;
				}
			} else if(m_hage >= min_age()) {
				
				DEBUG_P("Entering ghost mode!",####)
				
				m_ghost_mode = true;
				m_gage = 1;
			} else {
				DEBUG_P("Clearing hypothesis due to low age!",####)
				
				//clear the hypothesis
				m_have_hypothesis = false;
				m_gage = 0;
				m_hage = 0;
				m_ghost_mode = false;
			}		
		}  else {
			//no circle detected but no hypothesis
			//nothing to do
		}
	}
	
	if(m_have_hypothesis && m_ghost_mode) {
		DEBUG_T(m_have_hypothesis,)
		DEBUG_TL(m_hypothesis,)
		DEBUG_TL(m_last_pose,)
		DEBUG_T(m_hage,)
		DEBUG_T(m_ghost_mode,)
		DEBUG_T(m_gage,)
		DEBUG_P("",)
		DEBUG_P("",)
	}
	DEBUG_P("",)

	*subsume = false;
	pteam_p2os::RobotControlRequest req;
	rstRobotControlRequest(&req);
	//alway return an empty request
	return req;
}

TargetDetector::~TargetDetector() {

}

bool TargetDetector::detectCircle ( const pteam_p2os::Perception& in, Target* t ) {
	// Searches all candidate range intervals 
	// 	ROS_INFO("Searching intervals");
	interval_vector intervals;
	splitScan(intervals, in); 
	// 	ROS_INFO("\nNew scan: found %d intervals",intervals.size());
	
	// Visits all intervals 
	geometry_msgs::Point center_best;
	double r_best;
	interval_vector::iterator beg = intervals.begin();
	interval_vector::iterator end = intervals.end();
	for (; beg != end; ++beg) {
		geometry_msgs::Point center;
		double r;
		extractCircle2(in, *beg,center,r);
		// 		ROS_INFO("interval %d,%d: center (%f,%f), radius %f",
		// 				 beg->first,beg->second,center.x,center.y,r);
		if (::fabs(r - target_radius_) < ::fabs(r_best - target_radius_)) {
			center_best = center;
			r_best = r;
		}
	}
	
	if (::fabs(r_best - target_radius_) < target_radius_toll_ * target_radius_) {
		ROS_INFO("Best target\n best center (%f,%f), radius %f",center_best.x,center_best.y,r_best);
		t->x = center_best.x;
		t->y = center_best.y;
		t->radius = r_best;
		return true;
	}
	else {
		return false;
	}
}


/** Splits the scan into intervals where range discontinuities occur.
 */
void TargetDetector::splitScan(interval_vector& intervals, const pteam_p2os::Perception& in) 
{
	if (in.laser.data.ranges.empty()) return;
	
// 	unsigned int imin = (unsigned int)((angle_min_ - scan_.angle_min) / scan_.angle_increment);
	unsigned int imin = 0;
// 	unsigned int imax = (unsigned int)((angle_max_ - scan_.angle_min) / scan_.angle_increment);  
	unsigned int imax = in.laser.data.ranges.size();
	
	double rangePrev = 0.0;
	interval_type tmp;
	tmp.first = 0;
	if (imin < in.laser.data.ranges.size()) {
		rangePrev = in.laser.data.ranges.at(imin);
		tmp.first = imin;
	}
// 	ROS_INFO("  scanning ranges from %d to %d",imin,imax);
	for (unsigned int i = imin; i < in.laser.data.ranges.size() && i < imax; ++i) {
		if (!isnan(in.laser.data.ranges.at(i))) {    
			if (::fabs(in.laser.data.ranges.at(i) - rangePrev) > range_thr_) {
				tmp.second = i;
				intervals.push_back(tmp);
// 				std::cout << "range discontinuity at " << i << ": " << in.laser.data.ranges.at(i) 
// 				<< " -" << rangePrev << std::endl;
				tmp.first = i;
			}
			rangePrev = in.laser.data.ranges.at(i);
		}
	}
	tmp.second = in.laser.data.ranges.size();
	intervals.push_back(tmp);
}

void TargetDetector::extractCircle2(const pteam_p2os::Perception& in, const interval_type& ip,geometry_msgs::Point& center,double& r) 
{
	unsigned int num = ip.second-ip.first;
	Eigen::MatrixXd A(num,3);
	Eigen::VectorXd b(num);
	Eigen::Vector3d res;
	center.x = center.y = 0.0;
	for (unsigned int i = ip.first; i < in.laser.data.ranges.size() && i < ip.second; ++i) {
		double t = in.laser.data.angle_min + i * in.laser.data.angle_increment;
		double x = in.laser.data.ranges.at(i) * ::cos(t);
		double y = in.laser.data.ranges.at(i) * ::sin(t);
		unsigned int j = i - ip.first;
		A(j,0) = x;
		A(j,1) = y;
		A(j,2) = 1.0;
		b(j) = x*x + y*y;
		center.x += x;
		center.y += y;
	}
	res = (A.transpose() * A).inverse() * A.transpose() * b;
	//    std::cout << "\ninterval " << ip.first << "," << ip.second << std::endl;
	//    std::cout << "mean " << center.x/num << "," << center.y/num << std::endl;
	//    std::cout << "res:\n" << res << std::endl;
	center.x = 0.5 * res(X);
	center.y = 0.5 * res(Y);
	center.z = 0.0;
	r = ::sqrt(res(R) + center.x*center.x + center.y*center.y);
	//    std::cout << "center " << center.x << "," << center.y << std::endl;
}
