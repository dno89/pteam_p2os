/**
 * @file Behaviors.h
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief some behaviors implementation
 */

#ifndef	STAYINTHEMIDDLE_H
#define STAYINTHEMIDDLE_H

#include <base/CBehavior.h>
#include <pteam_p2os/Perception.h>
#include <pteam_p2os/RobotControl.h>

#include "base/gnuplot-iostream.h"


namespace pteam {
	
class StayInTheMiddle : public CBehavior<pteam_p2os::Perception, pteam_p2os::RobotControlRequest> {
	float m_threshold;
	int m_threshold_valley;
	std::vector<float> m_polar_histogram; 
	float m_alpha;
	
	///TEST
	Gnuplot m_gp;
	
public:	
	StayInTheMiddle(float threshold, int threshold_valley, float m_alpha);
	virtual pteam_p2os::RobotControlRequest operator() ( const pteam_p2os::Perception& in, bool* subsume = 0 );
	virtual ~StayInTheMiddle();

};

}

#endif	//STAYINTHEMIDDLE_H
