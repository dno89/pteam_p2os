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
	
class StayInTheMiddle : public CBehavior<pteam_p2os::Perception, pteam_p2os::RobotControlRequest> {
	float m_threshold, m_threshold_valley;
public:	
	StayInTheMiddle(float threshold, float threshold_valley);
	pteam_p2os::RobotControlRequest stay_in_the_middle(const pteam_p2os::Perception& in, float threashold, int threashold_valley);
	virtual pteam_p2os::RobotControlRequest operator() ( const pteam_p2os::Perception& in, bool* subsume = 0 );
	virtual ~StayInTheMiddle();
	
private:
   std::vector<float> polar_histogram; 
};

}

#endif	//BEHAVIORS_H
