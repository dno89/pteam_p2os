/**
 * @file Behaviors.cpp
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief implementation
 */
////standard lib
#include <cstdlib>
#include <cmath>
////pteam lib
#include "StayInTheMiddle.h"
#include "base/Common.h"
#include "base/DMDebug.h"
#define PI 3.14159265

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-behavior-StayInTheMiddle.log")

using namespace pteam;
using namespace std;

StayInTheMiddle::StayInTheMiddle( float threshold, int threshold_valley, float alpha, int nl_n, bool memory_effect, double learning_rate ) : m_threshold(threshold), m_threshold_valley(threshold_valley), m_alpha(alpha), m_nl_n(nl_n), m_memory_effect(memory_effect), m_learning_rate(learning_rate) {
	m_last_angular_speed = NAN;
}

pteam_p2os::RobotControlRequest StayInTheMiddle::operator() ( const pteam_p2os::Perception& in, bool* subsume ) {
	*subsume = false;

	int i;		//indice per i for

	m_polar_histogram.clear();
	m_polar_histogram.resize(in.laser.data.ranges.size());

	for(i = 0; i < m_polar_histogram.size(); ++i) {
		if(isnan(in.laser.data.ranges[i])) {
			m_polar_histogram[i] = NAN;
			continue;
		}

		m_polar_histogram[i] = 1.0 / (1.0 + pow((in.laser.data.ranges[i] - in.laser.data.range_min), m_alpha));
	}

#ifndef	NDEBUG
	vector<double> phvector;
	for(int ii = 0; ii < m_polar_histogram.size(); ++ii) {
		if(isnan(m_polar_histogram[ii])) {
			phvector.push_back(0.0);
			continue;
		}

		phvector.push_back(m_polar_histogram[ii]);
	}
	
	m_gp << "set yrange [0:1]\n";

	m_gp << "plot '-' with lines linecolor rgb \"red\" notitle\n";
	m_gp.send(phvector);
	m_gp.flush();
	
#endif	//NDEBUG

	bool find_valley = false;		//true se ho trovato una valle, false se non ho trovato una valle
	int first_index = -1;			//primo indice della valle
	int max_width = -1;			//ampiezza della valle con ampiezza massima
	int valley_first_index = -1, valley_last_index = -1;	//indici iniziale e finale della valley con ampiezza maggiore
	int width = -1;

	//cerchiamo gli avvallamenti e vonsideriamo come percorribile la valley con ampiezza maggiore
	///FIXME: è buggato perchè se la valle finisce con la fine dell'array non la rileva!!
	for(i = 0; i < m_polar_histogram.size(); ++i) {
		if(isnan(m_polar_histogram[i])) {
			continue;
		}

		if(m_polar_histogram[i] < m_threshold) {
			if(!find_valley) {
				find_valley = true;
				first_index = i;
			}
		} else {
			if(find_valley) {
				find_valley = false;

				width = i - first_index;

				if(width > m_threshold_valley && width > max_width) {

					max_width = width;
					valley_first_index = first_index;
					valley_last_index = i - 1;

// 					DEBUG_T(max_width,)
// 					DEBUG_T(valley_first_index,)
// 					DEBUG_T(valley_last_index,)
				}
			}
		}
	}
	if(find_valley) {
		find_valley = false;
		
		width = i - first_index;
		
		if(width > m_threshold_valley && width > max_width) {
			
			max_width = width;
			valley_first_index = first_index;
			valley_last_index = i - 1;
		}
	}

	float free_direction;			//direzione in cui ci muoviamo

	if(max_width == 0) {
		free_direction = DEG_TO_RAD(90.0);
	} else {
		/**
		 * Il motivo di tutta questa roba complicata è che non sempre voglio andare IN MEZZO alla valle..
		 * in particolare, se un estremo della valle ha un valore polare molto alto e l'altro basso, significa che da una parte ho un ostacolo vicino, dall'altra no.
		 * In quei casi è ragionevole stare più vicino alla parte libera.
		 * Quindi agli estremi della valle si associa un peso uguale al reciproco del valore polare.. poi c'è un po' di magia per fare una media non lineare..che mi riporti spesso al caso in cui prendo il valore in mezzo..tranne appunto quando c'è tanta differenza tra i pesi..spero funzioni :)
		 */
		
		//index before and after the valley
		int fi = max<int>(0, valley_first_index-1);
		int li = min<int>(m_polar_histogram.size()-1, valley_last_index+1);
		
		float num;
		
		//first non nan value before fi
		if(fi == 0) {
			//default value for free enviroment
			num = 0.2;
		} else {
			num = first_number_before(m_polar_histogram, fi);
			if(isnan(num)) num = .2f;
		}
		//weight first index
		float w_fi = 1.0f / (num);
		w_fi = pow(w_fi, weight_exponent());
		
		//first non nan value after li
		if(li == m_polar_histogram.size()-1) {
			//default value for free enviroment
			num = 0.2;
		} else {
			num = first_number_after(m_polar_histogram, li);
			if(isnan(num)) num = .2f;
		}
		//weight of the last index
		float w_li = 1.0f / (num);
		w_li = pow(w_li, weight_exponent());
		
		//the weight parameter
		free_direction = NLWAverage(fi, li, w_fi, w_li, m_nl_n) * in.laser.data.angle_increment + in.laser.data.angle_min;
		
// 		if(m_memory_effect && !isnan(m_last_free_direction)) {
// 			//memory effect: low pass filter to ammortize the oscillations
// 			free_direction = m_learning_rate*free_direction + (1.0 - m_learning_rate) * m_last_free_direction;
// 		}
		
		DEBUG_P("Finding the free direction",)
		DEBUG_T(fi,)
		DEBUG_T(li,)
		DEBUG_T(m_polar_histogram[fi],)
		DEBUG_T(m_polar_histogram[li],)
		DEBUG_T(w_fi,)
		DEBUG_T(w_li,)
		DEBUG_T(NLWAverage(fi, li, w_fi, w_li, m_nl_n),)
		DEBUG_T(RAD_TO_DEG(free_direction),)
		
// 		free_direction = ((valley_first_index + valley_last_index) / 2)*in.laser.data.angle_increment + in.laser.data.angle_min;
	}
	
// 	if(m_memory_effect) {
// 		m_last_free_direction = free_direction;
// 	}

// 	DEBUG_T(RAD_TO_DEG(in.laser.data.angle_increment),)
// 	DEBUG_T(RAD_TO_DEG(in.laser.data.angle_min),)

// 	DEBUG_T(RAD_TO_DEG(free_direction),)

	pteam_p2os::RobotControlRequest req;
	rstRobotControlRequest(&req);

	///TODO: imposta velocità
	req.affinity = 1.0;

	req.angular_speed = sin(free_direction);
	req.angular_speed_set = true;
	
	if(m_memory_effect) {
		if(!isnan(m_last_angular_speed)) {
			req.angular_speed = req.angular_speed * m_learning_rate + m_last_angular_speed * (1-m_learning_rate);
		}
		m_last_angular_speed = req.angular_speed;
	}
	
	float vel_limit = 0.0;

	float angle_width = max_width * in.laser.data.angle_increment;

// 	DEBUG_T(max_width,)
// 	DEBUG_T(valley_first_index,)
// 	DEBUG_T(valley_last_index,)
// 	DEBUG_T(angle_width,)
#ifdef	TURBO_MODE
	if(angle_width >= DEG_TO_RAD(45.0)) {
		vel_limit = 0.7;
	} else if(angle_width >= DEG_TO_RAD(30.0)) {
		vel_limit = 0.4;
	} else {
		vel_limit = 0.2;
	}
#else
	if(angle_width >= DEG_TO_RAD(45.0)) {
		vel_limit = 0.4;
	} else if(angle_width >= DEG_TO_RAD(30.0)) {
		vel_limit = 0.2;
	} else {
		vel_limit = 0.1;
	}
#endif	//TURBO_MODE

	req.linear_speed = cos(free_direction)*vel_limit;
	req.linear_speed_set = true;

	DEBUG_T(req.linear_speed,)
	DEBUG_T(req.angular_speed,)
	DEBUG_P("",)

	return req;
}

StayInTheMiddle::~StayInTheMiddle() {

}
