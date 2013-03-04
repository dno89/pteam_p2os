/**
 * @file Behaviors.h
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief some behaviors implementation
 */

#ifndef	COLLISIONAVOIDANCE_H
#define COLLISIONAVOIDANCE_H

#include <base/CBehavior.h>
#include <pteam_p2os/Perception.h>
#include <pteam_p2os/RobotControl.h>

namespace pteam {
	
class CollisionAvoidance : public CBehavior<pteam_p2os::Perception, pteam_p2os::RobotControlRequest> {
	double m_alpha, m_threshold;
public:
	CollisionAvoidance(double alpha = 0.2, double threshold = 0.2);
	virtual pteam_p2os::RobotControlRequest operator() ( const pteam_p2os::Perception& in, bool* subsume = 0 );
	virtual ~CollisionAvoidance();
};

}

#endif	//COLLISIONAVOIDANCE_H