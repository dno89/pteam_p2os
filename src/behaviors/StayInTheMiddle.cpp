/**
 * @file Behaviors.cpp
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief implementation
 */

#include <cmath>

#include "StayInTheMiddle.h"
#include "base/Common.h"
#include "base/DMDebug.h"
#define PI 3.14159265

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-behavior-StayInTheMiddle.log")

using namespace pteam;
using namespace std;

StayInTheMiddle::StayInTheMiddle(float threshold, int threshold_valley, float alpha) : m_threshold(threshold), m_threshold_valley(threshold_valley), m_alpha(alpha) {
//   size_t vSize = 180;
//   polar_histogram.resize(vSize);
  
}

pteam_p2os::RobotControlRequest StayInTheMiddle::operator() ( const pteam_p2os::Perception& in, bool* subsume ) {
  *subsume = false;
	
  int i;				//indice per i for
  
  m_polar_histogram.clear();
  m_polar_histogram.resize(in.laser.data.ranges.size());
  
 /* float last_value = 0, avg_value;		//last_value è l'ultimo valore valido che ho trovato prima di una sequenza di nan, avg_value è la media pesata dei due estremi (validi) di una sequenza di nan
  bool find_nan = false;		//true se ho trovato almeno un nan, false se non ho trovato nan
  int last_index = 0;
  //facciamo la scansione di tutti i settori del laser scanner per calcolare il relativo valore nel polar histogram
  /*for(i = 0; i < in.laser.data.ranges.size(); ++i) {
    if(isnan(in.laser.data.ranges[i])) {
      //se trovo un valore nan setto momentaneamente il valore nel polar histogram a 0
      find_nan = true;
      m_polar_histogram[i] = NAN;
    }
    else {
      polar_histogram[i] = in.laser.data.range_max - in.laser.data.ranges[i];
      
      if(find_nan) {
	//calcolo il valore medio da assegnare ai settori nan
	avg_value = (last_value + polar_histogram[i]) / 2;	//TODO: media pesata in base all'indice
	for(int j = last_index + 1; j < i; ++j) {
	  polar_histogram[j] = avg_value;
	}
	find_nan = false;
      }
      
      last_value = polar_histogram[i];
      last_index = i;
      
    }
  }*/
  
  for(i = 0; i < m_polar_histogram.size(); ++i) {
    if(isnan(in.laser.data.ranges[i])) {
      m_polar_histogram[i] = NAN;
      continue;
    }
    
    m_polar_histogram = 1.0 / (1.0 + pow((in.laser.data.ranges[i] - in.laser.data.range_min), m_alpha));
  }
  
//   for(i = 0; i < m_polar_histogram.size(); ++i) {
//     DEBUG_T(in.laser.data.ranges[i],)
//     DEBUG_T(m_polar_histogram[i],)
//   }
  
  
  /*for(i = 0; i < polar_histogram.size(); ++i) {
    if(polar_histogram[i] < threashold)
	polar_histogram[i] = 0;
  }*/
  
  
  bool find_valley = false;		//true se ho trovato una valle, false se non ho trovato una valle
  int first_index = 0;			//primo indice della valle
  int max_width = 0;			//ampiezza della valle con ampiezza massima
  int valley_first_index = 0, valley_last_index = 0;	//indici iniziale e finale della valley con ampiezza maggiore
  int width = 0;
  
  //cerchiamo gli avvallamenti e vonsideriamo come percorribile la valley con ampiezza maggiore
  for(i = 0; i < m_polar_histogram.size(); ++i) {
    if(isnan(m_polar_histogram[i])) {
      continue;
    }
    if(m_polar_histogram[i] < m_threshold) {
      if(!find_valley) {
	find_valley = true;
	first_index = i;
      }
    }
    else {
      if(find_valley) {
	width = i - first_index;
	if(width > m_threshold_valley && width > max_width) {
	  max_width = width;
	  valley_first_index = first_index;
	  valley_last_index = i - 1;
	}
      }
    }
  }
  
   float free_direction;			//direzione in cui ci muoviamo
  
  if(max_width == 0) {
      free_direction = DEG_TO_RAD(90.0);
  } else {
    free_direction = ((valley_first_index + valley_last_index) / 2)*in.laser.data.angle_increment + in.laser.data.angle_min;
  }
  
  /*DEBUG_T(RAD_TO_DEG(in.laser.data.angle_increment),)
  DEBUG_T(RAD_TO_DEG(in.laser.data.angle_min),) */
  
  DEBUG_T(RAD_TO_DEG(free_direction),)
  
  pteam_p2os::RobotControlRequest req;
  rstRobotControlRequest(&req);
  
  ///TODO: imposta velocità
  req.affinity = 1.0;
  
  req.angular_speed = sin(free_direction);	
  req.angular_speed_set = true;
  
  float vel_limit = 0.0;
  
  float angle_width = max_width * in.laser.data.angle_increment;
  
  DEBUG_T(max_width,)
  DEBUG_T(valley_first_index,)
  DEBUG_T(valley_last_index,)
  DEBUG_T(angle_width,)
  
  if(angle_width < DEG_TO_RAD(45.0)) {
    vel_limit = 0.1;
  } else {
    vel_limit = 0.7;
  }
  
  req.linear_speed = cos(free_direction)*vel_limit;
  req.linear_speed_set = true;
  
  DEBUG_T(req.linear_speed,)
  DEBUG_T(req.angular_speed,)
  
  return req;
}

StayInTheMiddle::~StayInTheMiddle() {

}
