/**
 * @file Behaviors.h
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief some behaviors implementation
 */

#ifndef	MOVETOWARDTHEGOAL_H
#define MOVETOWARDTHEGOAL_H

#include <base/CBehavior.h>
#include <pteam_p2os/Perception.h>
#include <pteam_p2os/RobotControl.h>

namespace pteam {
	
class MoveThroughwardGoal : public CBehavior<pteam_p2os::Perception, pteam_p2os::RobotControlRequest> {
   float m_threshold_angle;
   
   ////magic numbers
   static double affinity() { return 2.0; }
   
public:
	MoveThroughwardGoal(float threshold_angle = 2.0);
	virtual pteam_p2os::RobotControlRequest operator() ( const pteam_p2os::Perception& in, bool* subsume = 0 );
	virtual ~MoveThroughwardGoal();
};

}

#endif	//MOVETOWARDTHEGOAL_H