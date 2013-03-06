/**
 * @file Behaviors.cpp
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief implementation
 */



#include "TakeTheBall.h"
#include "base/Common.h"

using namespace pteam;


TakeTheBall::TakeTheBall(float angle_threshold) : m_angle_threshold(angle_threshold) {
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
    float ball_angle;
    float distance;
    high_resolution_clock::time_point current_time;
    high_resolution_clock::duration interval;
    
    //leggiamo le coordinate della palla e ne calcoliamo l'angolo:
    ball_coord = ReadProperty<Point2d>("TARGET_POSITION");
    ball_angle = RAD_TO_DEG(atan2(ball_coord.y, ball_coord.x));
       
      
    //valuto se la forca è abbassata o no
    if(m_gripper_down) {
      //la forca è abbassata
	
      distance = sqrt(pow(ball_coord.x, 2) + pow(ball_coord.y, 2));
	
      if(distance < 0.2) {
	//la palla è inforcata:
	m_start_time = high_resolution_clock::now();
	  
	req.gripper_move_down = false;
	req.gripper_move_set = true;
	  
	m_gripper_down = false;
	m_take_ball = true;
      }
     } 
     else {
      if(!m_take_ball) {
	//valuto se si sta abbassando o se devo ancora dare il comando
	if(!m_command_requested) {
	  //il comando non è ancora stato dato
	  m_start_time = high_resolution_clock::now();
	
	  //facciamo scendere la forca
	  req.gripper_move_down = true;
	  req.gripper_move_set = true;
	  
	  //ci fermiamo
	  req.linear_speed = 0.0;
	  req.linear_speed_set = true;
	 } 
	 else {
	  //ho gia dato il comando: contollo se la forca ha finito di scendere
	  current_time = high_resolution_clock::now();
	
	  interval = current_time - m_start_time;
	  if(interval.count() > (4.5*10e-6)) {
	    //il gripper si è abbassato:
	    req.linear_speed = 0.2;
	    req.linear_speed_set = true; 
	    
	    m_gripper_down = true;
	  }
	}
      } 
      else {
	//ho preso la palla controllo se la forca si è alzata: se si è alzata mi fermo
	current_time = high_resolution_clock::now();
	  
	interval = current_time - m_start_time;
	if(interval.count() > (4.5*10e-6)) {
	  //il gripper si è abbassato:
	  req.linear_speed = 0.0;
	  req.linear_speed_set = true; 
	}
      }
    }
  }			//chiude il controllo su target_in_range
  return req;
}

TakeTheBall::~TakeTheBall() {

}