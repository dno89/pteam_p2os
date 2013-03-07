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

TargetDetector::TargetDetector ( double range_thr, double target_radius, double target_radius_toll, double accept_threshold ) : m_range_threshold(range_thr), m_target_radius(target_radius), m_target_radius_tolerance(target_radius_toll), m_have_hypothesis(false), m_ghost_mode(false), m_hage(0), m_gage(0), m_last_pose(), m_hypothesis(), m_accept_threshold2(accept_threshold), m_RANSAC(max_RANSAC_iteration(), min_consensus(), RANSAC_distance_threshold(), 100) {
	//add property to the shared map
	base_type::AddProperty("TARGET_DETECTED", bool(false));
	base_type::AddProperty("TARGET_POSITION", Point2d());
	base_type::AddProperty("TARGET_IN_RANGE", bool(false));
	
#ifndef NDEBUG
	m_gp.set_style("points");
	m_gp.set_xrange(-6, 6);
	m_gp.set_yrange(0, 6);
#endif
}


pteam_p2os::RobotControlRequest TargetDetector::operator() ( const pteam_p2os::Perception& in, bool* subsume ) {
	
// 	DEBUG_T(in.odometry.pose.pose, )
// 	SimplePose sp = OdomToSimplePose(in.odometry.pose.pose);
// 	DEBUG_T(sp.x,)
// 	DEBUG_T(sp.y,)
// 	DEBUG_T(RAD_TO_DEG(sp.theta),);
#ifndef NDEBUG
	m_gp.reset_plot();
#endif

	///TODO: localize and track here!!
	Target t;
	SimplePose cur_pose = OdomToSimplePose(in.odometry.pose.pose);
// 	if(detectCircle(in, &t)) {
	if(RANSACdetect(in, &t)) {
		DEBUG_P("Circle detected!", ####)
		
#ifndef NDEBUG
		{
			std::vector<double> x, y;
			x.push_back(-t.y);
			y.push_back(t.x);
			m_gp.plot_xy(x, y, "detected circle");
		}
#endif
		
		//a circle detected
		if(m_have_hypothesis) {
			//circle detected and hypothesis
			if(TargetDistance2(t, RotateTarget(m_hypothesis, m_last_pose, cur_pose)) <= m_accept_threshold2) {
				//hypothesis confirmed
				DEBUG_P("Hypothesis confirmed!",####)
				
				m_ghost_mode = false;
				m_gage = 0;
				++m_hage;
				m_hypothesis = t;
				m_last_pose = cur_pose;
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
				} else if(m_hage >= min_age_to_ghost()) {
					
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
			} else if(m_hage >= min_age_to_ghost()) {
				
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

	if(m_have_hypothesis && m_hage > min_age_to_confirm()) {
		//set and update the flags
		SetProperty("TARGET_DETECTED", bool(false));
		
		//the current (estimated) position
		Point2d pos;
		
		if(!m_ghost_mode) {
			//the last perception has a valid position
			pos = m_hypothesis;
		} else {
			//ghost mode, we need to rotate the last position
			pos = RotateTarget(m_hypothesis, m_last_pose, cur_pose);
		}
		
		//publish the pose
		SetProperty("TARGET_POSITION", Point2d(pos));
		
#ifndef NDEBUG
		{
			std::vector<double> x, y;
			
			x.push_back(-pos.y);
			y.push_back(pos.x);
			m_gp.plot_xy(x, y, "current hypothesis");
		}
#endif
		
	} else {
		//clear the flag
		SetProperty("TARGET_DETECTED", bool(false));
		SetProperty("TARGET_IN_RANGE", bool(false));
	}
	
	///TEST
	if(m_have_hypothesis || m_ghost_mode) {
		DEBUG_T(m_have_hypothesis,)
		DEBUG_TL(m_hypothesis,)
		DEBUG_TL(m_last_pose,)
		DEBUG_T(m_hage,)
		DEBUG_T(m_ghost_mode,)
		DEBUG_T(m_gage,)
		DEBUG_P("",)
	}
	DEBUG_T(ReadProperty<bool>("TARGET_DETECTED"),)
	DEBUG_T(ReadProperty<bool>("TARGET_IN_RANGE"),)
	DEBUG_T(ReadProperty<Point2d>("TARGET_POSITION"),)
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
// 	ROS_INFO("\nFound %d intervals",intervals.size());
	
	// Visits all intervals 
	geometry_msgs::Point center_best;
	double r_best;
	interval_vector::iterator beg = intervals.begin();
	interval_vector::iterator end = intervals.end();
	for (; beg != end; ++beg) {
		geometry_msgs::Point center;
		double r;
		extractCircle2(in, *beg,center,r);
// 				ROS_INFO("interval %d,%d: center (%f,%f), radius %f", beg->first,beg->second,center.x,center.y,r);
		if (::fabs(r - m_target_radius) < ::fabs(r_best - m_target_radius)) {
			center_best = center;
			r_best = r;
		}
	}
	
	if (::fabs(r_best - m_target_radius) < m_target_radius_tolerance * m_target_radius) {
// 		ROS_INFO("Best target\n best center (%f,%f), radius %f",center_best.x,center_best.y,r_best);
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
			if (::fabs(in.laser.data.ranges.at(i) - rangePrev) > m_range_threshold) {
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
	// 	res = (A.transpose() * A).inverse() * A.transpose() * b;
	res = A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);;
	//    std::cout << "\ninterval " << ip.first << "," << ip.second << std::endl;
	//    std::cout << "mean " << center.x/num << "," << center.y/num << std::endl;
	//    std::cout << "res:\n" << res << std::endl;
	center.x = 0.5 * res(X);
	center.y = 0.5 * res(Y);
	center.z = 0.0;
	r = ::sqrt(res(R) + center.x*center.x + center.y*center.y);
	//    std::cout << "center " << center.x << "," << center.y << std::endl;
}

////support function
//function to sort model with relative consensus perc
bool cmp(const std::pair<Circle, double>& t1, const std::pair<Circle, double>& t2) {
	return (t1.second > t2.second);
}

bool TargetDetector::RANSACdetect(const pteam_p2os::Perception& in, Target* t)  {
	interval_vector intervals;
	//split scan into intervals
	splitScan(intervals, in);
	
	DEBUG_T(intervals.size(),)
	
// 	Circle best_model;
	std::vector<std::pair<Circle, double>> models;
	
	//for each scan interval
	for(int ii = 0; ii < intervals.size(); ++ii) {
		std::vector<Point2d> points;
		
		for(int jj = intervals[ii].first; jj <= intervals[ii].second; ++jj) {
			if(isnan(in.laser.data.ranges[jj])) {
				continue;
			}
			
			double theta = jj*in.laser.data.angle_increment + in.laser.data.angle_min;
			points.push_back(Point2d(in.laser.data.ranges[jj]*cos(theta), in.laser.data.ranges[jj]*sin(theta)));
		}
		
		int total_points = points.size();
		
		if(total_points < min_consensus()) {
			//the interval doesn't contain enough points
			continue;
		}
		
		//load point in RANSAC
		m_RANSAC.LoadPoints(points.begin(), points.end());
		
		points.clear();
		Circle ransac_model;
		try {
			ransac_model = m_RANSAC.Run(&points);
		} catch(...) {
			continue;
		}
		//now points contain only the consensus points
		
		DEBUG_T(ransac_model,)
		
		//validity check
		if(	ransac_model.GetRadius() != -1 &&
			points.size() >= consensus_perc()*total_points &&
			ransac_model.GetCenter().x >= 0.0 &&
			std::abs(ransac_model.GetRadius()-m_target_radius) < m_target_radius_tolerance * m_target_radius ) {
			
			//this is a valid model
			models.push_back(std::make_pair(ransac_model, points.size()/double(total_points)));
		}
	}
	
	if(models.size()) {
		//models contain the candidate models
		DEBUG_P("The found models are: ",)
		for(auto it = models.begin(); it != models.end(); ++it) {
			DEBUG_T(it->first,)
		}
		DEBUG_P("",)
		
		std::sort(models.begin(), models.end(), cmp);
		
		DEBUG_T(models.front().first, )
		
		t->radius = models.front().first.GetRadius();
		t->x = models.front().first.GetCenter().x;
		t->y = models.front().first.GetCenter().y;
		
		return true;
		
	} else {
		
		return false;
		
	}
}