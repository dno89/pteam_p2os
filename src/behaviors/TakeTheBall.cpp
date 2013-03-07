/**
 * @file Behaviors.cpp
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief implementation
 */



#include "TakeTheBall.h"
#include "base/Common.h"
#include "base/DMDebug.h"

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-behavior-taketheball.log");

using namespace pteam;


TakeTheBall::TakeTheBall() {
  m_command_requested = false;
  m_gripper_down = false;
  m_take_ball = false;
}


pteam_p2os::RobotControlRequest TakeTheBall::operator() ( const pteam_p2os::Perception& in, bool* subsume ) {
  *subsume = true;
  
  bool target_in_range;
  
  
  pteam_p2os::RobotControlRequest req;
  rstRobotControlRequest(&req);
  
  try {
    target_in_range = ReadProperty<bool>("TARGET_IN_RANGE");
  }
  catch(...) {
    target_in_range = false;
  }
  
  if(target_in_range) {
    Point2d ball_coord;
    float distance;
    high_resolution_clock::time_point current_time;
    high_resolution_clock::duration interval;
    
    //leggiamo le coordinate della palla:
    ball_coord = ReadProperty<Point2d>("TARGET_POSITION");
       
    DEBUG_P("TARGET IN RANGE",)
    
    //valuto se la forca è abbassata o no
    if(m_gripper_down) {
      //la forca è abbassata
	
      distance = sqrt(pow(ball_coord.x, 2) + pow(ball_coord.y, 2));
      DEBUG_P("GRIPPER DOWN",)
      
      if(distance < 0.2) {
      if(distance < distance_ball()) {
	//la palla è sufficientemente vicina: la inforco e inizio ad alzare la forca sempre andando avanti:
	DEBUG_P("GRIPPER START TAKE THE BALL AND MOVE UP",)
	
	m_start_time = high_resolution_clock::now();
	  
	//do il comando al gripper di alzare
	req.gripper_move_down = false;
	req.gripper_move_set = true;
	  
	m_gripper_down = false;
	m_take_ball = true;
      }
     } 
     else {		//no il gripper non è giu
      if(m_take_ball) {
	//ho preso la palla controllo se la forca si è alzata: se si è alzata mi fermo
	current_time = high_resolution_clock::now();
	  
	DEBUG_P("GRIPPER IS MOVING UP WITH THE BALL",)
	
	interval = current_time - m_start_time;
	if(interval.count() > (interval_gripper())) {
	  //il gripper si è alzato, quindi ci fermiamo:
	  req.linear_speed = 0.0;
	  req.linear_speed_set = true;
	  
	  DEBUG_P("GRIPPER UP WITH THE BALL!!!!!!!!!!",)
	  
	  ///HAPPY WIN =) SEEEEEE!!!	
	}
      } 
      else {	//no ho preso la palla
	//valuto se il gripper si sta abbassando o se devo ancora dare il comando
	if(m_command_requested) {
	  //ho gia dato il comando: contollo se la forca ha finito di scendere
	  DEBUG_P("GRIPPER IS MOVING DOWN",)
	  //ho gia dato il comando: controllo se la forca ha finito di scendere
	  current_time = high_resolution_clock::now();
	
	  interval = current_time - m_start_time;
	  if(interval.count() > (interval_gripper())) {
	    //il gripper si è abbassato:
	    DEBUG_P("GRIPPER DOWN",)
	    
	    req.linear_speed = 0.2;
	    req.linear_speed_set = true; 
	     
	    m_gripper_down = true;  
	  }
	}
	else {
	  //il comando non è ancora stato dato
	  DEBUG_P("GRIPPER START MOVING DOWN",)
	  
	  m_start_time = high_resolution_clock::now();
	
	  //facciamo scendere la forca
	  req.gripper_move_down = true;
	  req.gripper_move_set = true;
	  
	  //ci fermiamo
	  req.linear_speed = 0.0;
	  req.linear_speed_set = true;
	  
	  m_command_requested = true;
	}
      }
    }
  }			//chiude il controllo su target_in_range
  return req;
}
}

TakeTheBall::~TakeTheBall() {

}