/**
 * @file Behaviors.h
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief some behaviors implementation
 */

#ifndef	BEHAVIORS_H
#define BEHAVIORS_H

#include <base/CBehavior.h>
#include <pteam_p2os/Perception.h>
#include <pteam_p2os/RobotControl.h>

namespace pteam {
	
class TargetDetector : public CBehavior<pteam_p2os::Perception, pteam_p2os::RobotControlRequest> {
public:
        virtual pteam_p2os::RobotControlRequest operator() ( const pteam_p2os::Perception& in, bool* subsume = 0 );
        virtual ~TargetDetector();
};

}

#endif	//BEHAVIORS_H