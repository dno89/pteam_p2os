/**
 * @file Behaviors.cpp
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief implementation
 */

#include "CollisionAvoidance.h"
#include "base/Common.h"
#include "base/DMDebug.h"
#include <pteam_p2os/RobotControl.h>
#include <cmath>
#include <limits>

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-behavior-collision_avoidance.log")

using namespace pteam;
using namespace std;

CollisionAvoidance::CollisionAvoidance(double alpha, double threshold) : m_alpha(alpha), m_threshold(threshold) {
	
}


pteam_p2os::RobotControlRequest CollisionAvoidance::operator() ( const pteam_p2os::Perception& in, bool* subsume ) {
// 	DEBUG_P("CollisionAvoidance::operator() called",)
	
	double beta_min, beta_max;
	
// 	if(in.odometry.twist.twist.linear.x > 0.01) {
// 		double k = in.odometry.twist.twist.angular.z / in.odometry.twist.twist.linear.x;
// 		///TODO: check 
// 		beta_min = atan2(-0.2 + m_alpha*k, 0.2);
// 		beta_max = atan2(0.2 + m_alpha*k, 0.2);
// 	} else {
		beta_min = atan2(-m_threshold, .2);
		beta_max = atan2(m_threshold, .2);
// 	}
	
	DEBUG_T(RAD_TO_DEG(beta_min), )
	DEBUG_T(RAD_TO_DEG(beta_max), )
	
	int imin = (beta_min - in.laser.data.angle_min) / in.laser.data.angle_increment;
	int imax = (beta_max - beta_min) / in.laser.data.angle_increment;
	
// 	DEBUG_T(imin, )
// 	DEBUG_T(imax, )
	
	double min_scan = numeric_limits<double>::max();
	
	for(int ii = imin; ii <= imax; ++ii) {
		if(isnan(in.laser.data.ranges[ii])) {
			continue;
		}
		
		if(in.laser.data.ranges[ii] < min_scan) {
			min_scan = in.laser.data.ranges[ii];
		}
	}
	
	pteam_p2os::RobotControlRequest req;
	rstRobotControlRequest(&req);
	
// 	DEBUG_T(min_scan,)
// 	DEBUG_T(m_threshold,)
	
	if(min_scan < m_threshold) {
		req.affinity = 1000.0;
		req.linear_speed = 0.0f;
		req.linear_speed_set = true;
	}
	
	*subsume = false;
	return req;
}

CollisionAvoidance::~CollisionAvoidance() {

}
