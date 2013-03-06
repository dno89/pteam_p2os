/**
 * @file Behaviors.h
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief some behaviors implementation
 */

#ifndef	TAKETHEBALL_H
#define TAKETHEBALL_H

#include <base/CBehavior.h>
#include <pteam_p2os/Perception.h>
#include <pteam_p2os/RobotControl.h>

#include <chrono>

using namespace std::chrono;

namespace pteam {
	
class TakeTheBall : public CBehavior<pteam_p2os::Perception, pteam_p2os::RobotControlRequest> {
  float m_angle_threshold;
  bool m_command_requested;
  bool m_gripper_down;
  bool m_take_ball;
  high_resolution_clock::time_point m_start_time;
public:
	TakeTheBall(float angle_threshold = 2.0);
        virtual pteam_p2os::RobotControlRequest operator() ( const pteam_p2os::Perception& in, bool* subsume = 0 );
        virtual ~TakeTheBall();
};

}

#endif	//TAKETHEBALL_H