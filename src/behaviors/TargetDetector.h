/**
 * @file Behaviors.h
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief some behaviors implementation
 */

#ifndef	TARGETDETECTOR_H
#define TARGETDETECTOR_H

#include <base/CBehavior.h>
#include <base/Common.h>
#include "Circle.h"
#include <pteam_p2os/Perception.h>
#include <pteam_p2os/RobotControl.h>
#include <geometry_msgs/Pose.h>
#include <base/RANSAC.h>

#ifndef NDEBUG
#include <base/gnuplot-iostream.h>
#endif

namespace pteam {
	
class TargetDetector : public CBehavior<pteam_p2os::Perception, pteam_p2os::RobotControlRequest> {
/********************************************************************
* 						DARIO'S STUFF								*
********************************************************************/
	////typedefs
	typedef std::pair<int,int> interval_type;
	typedef std::vector<interval_type> interval_vector;
	////data
	double m_range_threshold;          // threshold to split scan into segments
// 	double range_min_;          // minimum value of a valid range
// 	double range_max_;          // maximum value of a valid range
// 	double angle_min_;          // first angle of the considered FoV
// 	double angle_max_;          // last angle of the considered FoV
	double m_target_radius;      // approximate radius of circular target
	double m_target_radius_tolerance; // relative tollerance on target radius
	////enum
	enum Index {X = 0, Y = 1, R = 2};
	bool detectCircle(const pteam_p2os::Perception& in, Target* t);
	void splitScan(interval_vector& intervals, const pteam_p2os::Perception& in);
	void extractCircle2(const pteam_p2os::Perception& in, const interval_type& ip,geometry_msgs::Point& center,double& r) ;
	
/********************************************************************
* 						MY	STUFF									*
********************************************************************/
	////typedef
	typedef CBehavior<pteam_p2os::Perception, pteam_p2os::RobotControlRequest> base_type;
	////tracking
	bool m_have_hypothesis;	//whether there is a current hypothesis
	Target m_hypothesis;		//the last position detected for target
	SimplePose m_last_pose;	//pose associated with last hypothesis
	unsigned int m_hage;				//hypothesis age
	bool m_ghost_mode;		//ghost mode
	unsigned int m_gage;				//ghost age
	const double m_accept_threshold2;	//sqared distance threshold to accept an observation
	
	////magic numbers
	static int min_age_to_ghost() { return 0; }
	static int min_age_to_confirm() { return 5; }
	static int max_ghost_age() { return 10; }
	
	////detection
	RANSAC<Point2d, Circle> m_RANSAC;
	////functions
	bool RANSACdetect(const pteam_p2os::Perception& in, Target* t);
	
	////debug
#ifndef	NDEBUG	
#warning @ TargetDetector DRAWING ENABLED
	Gnuplot m_gp1;
#endif
	
	////magic numbers
	static int min_consensus() { return 10; }
	static int max_RANSAC_iteration() { return 100; }
	static double RANSAC_distance_threshold() {
#ifdef ON_SIMULATION
		return 0.1;
#else
		return 0.02; 
#endif	//ON_SIMULATION
	}
	static double consensus_perc() { return 0.9; }
	static double in_range_distance() { return 0.7; }
public:
	TargetDetector(double range_thr, double taget_radius, double target_radius_toll, double accpet_threshold);
	virtual pteam_p2os::RobotControlRequest operator() ( const pteam_p2os::Perception& in, bool* subsume = 0 );
	virtual ~TargetDetector();
};

}

#endif	//TARGETDETECTOR_H