/**
 * @file Behaviors.cpp
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief implementation
 */

#include "MoveThroughwardGoal.h"

#include "base/Common.h"
#include "base/DMDebug.h"

//CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-behavior-movetowardgoal.log");

#include <base/DMDebug.h>

#include <string>

CREATE_PRIVATE_DEBUG_LOG("/tmp/pteam-behavior-move_toward_goal.log")


using namespace pteam;

MoveThroughwardGoal::MoveThroughwardGoal(float threshold_angle) : m_threshold_angle(threshold_angle) {
 
}


pteam_p2os::RobotControlRequest MoveThroughwardGoal::operator() ( const pteam_p2os::Perception& in, bool* subsume) {
  *subsume = false;
  
  
  pteam_p2os::RobotControlRequest req;
  rstRobotControlRequest(&req);

  
  //controllo se proprietà TARGET_DETECTED è stata settata nella mappa
  bool target_detected;
  try {
    target_detected = ReadProperty<bool>("TARGET_DETECTED");
  }
  catch(...) {
    target_detected = false;
  }
  
  if(target_detected) {
    //DEBUG_P("TARGET DETECTED")
    
    Point2d ball_coord;

    ball_coord = ReadProperty<Point2d>("TARGET_POSITION");
	
    DEBUG_T(ball_coord,)
	
    double ball_angle;		//angolo di orientazione della palla
    ball_angle = atan2(ball_coord.y, ball_coord.x);
	
    DEBUG_T(ball_angle,)
	
    req.affinity = affinity();
	
    //controllo la posizione della palla
    if(std::abs(ball_angle) > m_threshold_angle/*(ball_angle > m_threshold_angle) && (ball_angle < -m_threshold_angle)*/) {
      //la palla non è davanti a me
      //DEBUG_P("BALL IS NOT IN FRONT OF ME")
      
      req.linear_speed = 0.0;
    } else {
		//la palla è davanti
		req.linear_speed = std::cos(ball_angle) * max_speed();
	}
	req.linear_speed_set = true;
	
	//set the angular speed
    req.angular_speed = sin(ball_angle);
    req.angular_speed_set = true;
  }
  
  req.behavior_name = "MoveThroughwardGoal";
  
  return req;
  
}

MoveThroughwardGoal::~MoveThroughwardGoal() {

}
