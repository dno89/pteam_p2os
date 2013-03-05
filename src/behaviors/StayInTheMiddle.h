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
	////data
	//threshold for free direction
	float m_threshold;
	//minimum size (in sector) of a valley
	int m_threshold_valley;
	//polar value
	std::vector<float> m_polar_histogram;
	//exponent for the polar value
	float m_alpha;
	//exponent base for the non-linear weighted average
	int m_nl_n;
#ifndef	NDEBUG
	Gnuplot m_gp;
#endif
	float m_last_angular_speed;
	bool m_memory_effect;
	float m_learning_rate;
	
	////magic constant
	static double weight_exponent() { return 2.5; }
public:	
	StayInTheMiddle(float threshold, int threshold_valley, float alpha, int nl_n, bool memory_effect = false, double learning_rate = 0.8);
	virtual pteam_p2os::RobotControlRequest operator() ( const pteam_p2os::Perception& in, bool* subsume = 0 );
	virtual ~StayInTheMiddle();

};

}

#endif	//STAYINTHEMIDDLE_H
