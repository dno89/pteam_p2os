/**
 * @file Behaviors.cpp
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief implementation
 */

#include <cmath>

#include "StayInTheMiddle.h"
#include "base/Common.h"
#define PI 3.14159265

using namespace pteam;
using namespace std;

StayInTheMiddle::StayInTheMiddle(float threshold, int threshold_valley) : m_threshold(threshold), m_threshold_valley(threshold_valley) {
  size_t vSize = 180;
  polar_histogram.resize(vSize);
  
}

pteam_p2os::RobotControlRequest StayInTheMiddle::operator() ( const pteam_p2os::Perception& in, bool* subsume ) {
	*subsume = false;
	return stay_in_the_middle(in, m_threshold, m_threshold_valley);
}

pteam_p2os::RobotControlRequest StayInTheMiddle::stay_in_the_middle(const pteam_p2os::Perception& in, float threashold, int threashold_valley) {
  int i;				//indice per i for
  float last_value, avg_value;		//last_value è l'ultimo valore valido che ho trovato prima di una sequenza di nan, avg_value è la media pesata dei due estremi (validi) di una sequenza di nan
  bool find_nan;		//true se ho trovato almeno un nan, false se non ho trovato nan
  int last_index;			//indice dell'ultimo valore valido che ho trovato prima di una sequenza di nan
  
  bool find_valley;		//true se ho trovato una valle, false se non ho trovato una valle
  int first_index;			//primo indice della valle
  
  int max_width;			//ampiezza della valle con ampiezza massima
  int valley_first_index, valley_last_index;	//indici iniziale e finale della valley con ampiezza maggiore
  int width;
  
  float free_direction;			//direzione in cui ci muoviamo
  
  find_nan = false;
  find_valley = false;
  max_width = 0;
  
  //facciamo la scansione di tutti i settori del laser scanner per calcolare il relativo valore nel polar histogram
  for(i = 0; i < in.laser.data.ranges.size(); i++) {
    if(isnan(in.laser.data.ranges[i])) {
      //se trovo un valore nan setto momentaneamente il valore nel polar histogram a 0
      find_nan = true;
      polar_histogram[i] = 0;
    }
    else {
      polar_histogram[i] = in.laser.data.range_max - in.laser.data.ranges[i];
      
      //se è minore di una certa soglia lo setto a 0
      if(polar_histogram[i] < threashold)
	polar_histogram[i] = 0;
      
      if(find_nan) {
	//calcolo il valore medio da assegnare ai settori nan
	avg_value = (last_value - polar_histogram[i]) / 2;	//TODO: media pesata in base all'indice
	for(int j = last_index + 1; j < i; j ++) {
	  polar_histogram[j] = avg_value;
	}
	find_nan = false;
      }
      
      last_value = polar_histogram[i];
      last_index = i;
      
    }
  }
  
  //cerchiamo gli avvallamenti e vonsideriamo come percorribile la valley con ampiezza maggiore
  for(i = 0; i < polar_histogram.size(); i++) {
    if(polar_histogram[i] == 0) {
      if(!find_valley) {
	find_valley = true;
	first_index = i;
      }
    }
    else {
      if(find_valley) {
	width = i - first_index;
	if(width > threashold_valley && width > max_width) {
	  max_width = width;
	  valley_first_index = first_index;
	  valley_last_index = i - 1;
	}
      }
    }
  }
  free_direction = ((valley_first_index + valley_last_index) / 2) - 90;
  
  
  pteam_p2os::RobotControlRequest req;
  rstRobotControlRequest(&req);
  
  ///TODO: imposta velocità
  req.affinity = 1;
  req.linear_speed = cos(free_direction*PI/180);
  req.linear_speed_set = true;
  req.angular_speed = sin(free_direction*PI/180);	
  req.angular_speed_set = true;
  
  return req;
}

StayInTheMiddle::~StayInTheMiddle() {

}
