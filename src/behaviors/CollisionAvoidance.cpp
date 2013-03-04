/**
 * @file Behaviors.cpp
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief implementation
 */

#include "CollisionAvoidance.h"
#include <cmath>

using namespace pteam;
using namespace std;

CollisionAvoidance::CollisionAvoidance(double alpha) : m_alpha(alpha){
	
}


pteam_p2os::RobotControlRequest CollisionAvoidance::operator() ( const pteam_p2os::Perception& in, bool* subsume ) {
// 	double speed = 
	double k = in.odometry.twist.twist.angular.z / in.odometry.twist.twist.linear.x;
// 	double beta_min = atan2(-(0.2 + m_alpha*), 0.2);
}

CollisionAvoidance::~CollisionAvoidance() {

}
