/**
 * @file Behaviors.cpp
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief implementation
 */

#include "MoveThroughwardGoal.h"
#include "base/Common.h"

using namespace pteam;

MoveThroughwardGoal::MoveThroughwardGoal(float threshold_angle) : m_threshold_angle(threshold_angle) {
 
}


pteam_p2os::RobotControlRequest MoveThroughwardGoal::operator() ( const pteam_p2os::Perception& in, bool* subsume) {
  *subsume = false;
  
  float ball_angle;		//angolo di orientazione della palla
  Point2d ball_coord;
  
  bool target_detected;
  
  pteam_p2os::RobotControlRequest req;
  rstRobotControlRequest(&req);

  
  //controllo se proprietà TARGET_DETECTED è stata settata nella mappa
  try {
    target_detected = ReadProperty<bool>("TARGET_DETECTED");
  }
  catch(...) {
    target_detected = false;
  }
  
  if(target_detected) {
    ball_coord = ReadProperty<Point2d>("TARGET_POSITION");
    ball_angle = RAD_TO_DEG(atan2(ball_coord.y, ball_coord.x));
    req.affinity = affinity();
    //controllo la posizione della palla
    if((ball_angle > m_threshold_angle) && (ball_angle < -m_threshold_angle)) {
      //la palla non è davanti a me
      req.linear_speed = 0.0;
      req.linear_speed_set = true;
    }
    req.angular_speed = sin(ball_angle);
    req.angular_speed_set = true;
  }
  
  return req;
  
}

MoveThroughwardGoal::~MoveThroughwardGoal() {

}
