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


TakeTheBall::TakeTheBall() : m_state(eSFirstCall) , m_enabled(false) {
	// 	m_command_requested = false;
	// 	m_gripper_down = false;
	// 	m_take_ball = false;
}


// pteam_p2os::RobotControlRequest TakeTheBall::operator() ( const pteam_p2os::Perception& in, bool* subsume ) {
// 	bool target_in_range;
// 
// 
// 	pteam_p2os::RobotControlRequest req;
// 	rstRobotControlRequest(&req);
// 
// 	try {
// 		target_in_range = ReadProperty<bool>("TARGET_IN_RANGE");
// 	} catch(...) {
// 		target_in_range = false;
// 	}
// 
// 	if(target_in_range) {
// 		*subsume = true;
// 		Point2d ball_coord;
// 		float distance;
// 		high_resolution_clock::time_point current_time;
// 		high_resolution_clock::duration interval;
// 
// 		//leggiamo le coordinate della palla:
// 		ball_coord = ReadProperty<Point2d>("TARGET_POSITION");
// 
// 		DEBUG_P("TARGET IN RANGE",)
// 
// 		//valuto se la forca è abbassata o no
// 		if(m_gripper_down) {
// 			//la forca è abbassata
// 
// 			distance = sqrt(pow(ball_coord.x, 2) + pow(ball_coord.y, 2));
// 			DEBUG_P("GRIPPER DOWN",)
// 
// 			if(distance < distance_ball()) {
// 				//la palla è sufficientemente vicina: la inforco e inizio ad alzare la forca sempre andando avanti:
// 				DEBUG_P("GRIPPER START TAKE THE BALL AND MOVE UP",)
// 
// 				m_start_time = high_resolution_clock::now();
// 
// 				//do il comando al gripper di alzare
// 				req.gripper_move_down = false;
// 				req.gripper_move_set = true;
// 
// 				m_gripper_down = false;
// 				m_take_ball = true;
// 
// 			} else {
// 				//no il gripper non è giu
// 				if(m_take_ball) {
// 					//ho preso la palla controllo se la forca si è alzata: se si è alzata mi fermo
// 					current_time = high_resolution_clock::now();
// 
// 					DEBUG_P("GRIPPER IS MOVING UP WITH THE BALL",)
// 
// 					interval = current_time - m_start_time;
// 					if(interval.count() > (interval_gripper())) {
// 						//il gripper si è alzato, quindi ci fermiamo:
// 						req.linear_speed = 0.0;
// 						req.linear_speed_set = true;
// 
// 						DEBUG_P("GRIPPER UP WITH THE BALL!!!!!!!!!!",)
// 
// 						///HAPPY WIN =) SEEEEEE!!!
// 					}
// 				} else {	//no ho preso la palla
// 					//valuto se il gripper si sta abbassando o se devo ancora dare il comando
// 					if(m_command_requested) {
// 						//ho gia dato il comando: contollo se la forca ha finito di scendere
// 						DEBUG_P("GRIPPER IS MOVING DOWN",)
// 						//ho gia dato il comando: controllo se la forca ha finito di scendere
// 						current_time = high_resolution_clock::now();
// 
// 						interval = current_time - m_start_time;
// 						if(interval.count() > (interval_gripper())) {
// 							//il gripper si è abbassato:
// 							DEBUG_P("GRIPPER DOWN",)
// 
// 							req.linear_speed = 0.2;
// 							req.linear_speed_set = true;
// 
// 							m_gripper_down = true;
// 						}
// 					} else {
// 						//il comando non è ancora stato dato
// 						DEBUG_P("GRIPPER START MOVING DOWN",)
// 
// 						m_start_time = high_resolution_clock::now();
// 
// 						//facciamo scendere la forca
// 						req.gripper_move_down = true;
// 						req.gripper_move_set = true;
// 
// 						//ci fermiamo
// 						req.linear_speed = 0.0;
// 						req.linear_speed_set = true;
// 
// 						m_command_requested = true;
// 					}
// 				}
// 			}
// 		}			//chiude gripper down
// 	} else {	//target in range
// 		*subsume = false;
// 	}
// 
// 
// 	return req;
// }


pteam_p2os::RobotControlRequest TakeTheBall::operator()(const pteam_p2os::Perception& in, bool* subsume) {
	bool tir;
	
	try {
		tir = ReadProperty<bool>("TARGET_IN_RANGE");
	} catch(...) {
		tir = false;
	}
	
	pteam_p2os::RobotControlRequest req;
	rstRobotControlRequest(&req);
	req.affinity = 1.0;
	
	if(tir || m_enabled) {
		
		m_enabled = true;
		
		DEBUG_P("Target in range",)
		
		//subsume other behaviors
		*subsume = true;
		
		DEBUG_T(m_state,)
		
		////used below (così la fRA è contenta)
		auto t = high_resolution_clock::now();
		high_resolution_clock::duration dt;
		Point2d tp;
		double theta;
		
		//state switch
		switch(m_state) {
			case eSFirstCall:
				
				DEBUG_P("First Call!",)
				
				//stop the robot
				req.linear_speed = 0.0;
				req.linear_speed_set = true;
// 				req.angular_speed = 0.0;
// 				req.angular_speed_set = true;
				
				tp = ReadProperty<Point2d>("TARGET_POSITION");
				theta = atan2(tp.y, tp.x);
				
				DEBUG_T(theta, )
				
				if(std::abs(theta) > angular_threshold()) {
					DEBUG_P("Aligning the robot...", )
					//align the robot
					req.angular_speed = sin(theta);
					req.angular_speed_set = true;
					
				} else {
					//stop it
					req.angular_speed = 0.0;
					req.angular_speed_set = true;
					
					
					//lower the gripper
					req.gripper_move_set = true;
					req.gripper_move_down = true;
					//save current time
					m_start_time = high_resolution_clock::now();
					//go to the nex state
					m_state = eSWaitingDown;
				}
				break;
				
			case eSWaitingDown:
				DEBUG_P("Waiting Down!",)
				
				//Stop the robott
				req.angular_speed = 0.0;
				req.angular_speed_set = true;
				req.linear_speed = 0.0;
				req.linear_speed_set = true;
				
				dt = t - m_start_time;
				
				if(dt.count() >= interval_gripper()) {
					m_state = eSMoveForwad;
				}
				break;
				
			case eSMoveForwad:
				DEBUG_P("Move Forward",)
				
// 				tp = ReadProperty<Point2d>("TARGET_POSITION");
// 				theta = atan2(tp.y, tp.x);
				
				if(nearest_scan(in, -angular_fov(), angular_fov()) >= distance_ball()) {
					//angular speed
					req.linear_speed = closing_speed()/**cos(theta)*/;
					req.linear_speed_set = true;
					
// 					req.angular_speed = sin(theta);
// 					req.angular_speed_set = true;
				} else {
					//lift the gripper
					req.gripper_move_set = true;
					req.gripper_move_down = false;
					
					//save start time
					m_start_time = high_resolution_clock::now();
					
					m_state = eSWaitingUp;
				}
				break;
				
			case eSWaitingUp:
				DEBUG_P("Waiting Up!",)
				
				//stop the robot
// 				req.linear_speed = 0.0;
// 				req.linear_speed_set = true;
				req.angular_speed = 0.0;
				req.angular_speed_set = true;
				
// 				t = high_resolution_clock::now();
				
				dt = t - m_start_time;
				
				if(dt.count() <= interval_gripper()) {
					//still waiting
					//TODO: move a little forwad??
					req.linear_speed = 0.0/*closing_speed()*/;
					req.linear_speed_set = true;
				} else {
					req.linear_speed = 0.0;
					req.linear_speed_set = true;
					
					m_state = eSWinning;
				}
				
				break;
				
			case eSWinning:
				DEBUG_P("FUCK YEAHHHHH!!!!! WINNING!!!",)
				
				///TODO
				/*
				req.angular_speed = 1.0;
				req.angular_speed_set = true;*/
				
				//stop the robot
				req.linear_speed = 0.0;
				req.linear_speed_set = true;
				req.angular_speed = 0.0;
				req.angular_speed_set = true;
				break;
		};
		
		req.behavior_name = "TakeTheBall";
		
		DEBUG_T(req.affinity,)
		DEBUG_T(req.angular_speed,)
		DEBUG_T(bool(req.angular_speed_set), )
		DEBUG_T(req.linear_speed,)
		DEBUG_T(bool(req.linear_speed_set), )
		DEBUG_T(bool(req.gripper_move_down), )
		DEBUG_T(bool(req.gripper_move_set), )
		DEBUG_T(req.behavior_name, )
		
	} else {
		//no target in range
		*subsume = false;
	}
	
	return req;
}

double TakeTheBall::nearest_scan(const pteam_p2os::Perception& in, double angle_min, double angle_max) {
	int imin = (angle_min - in.laser.data.angle_min)/in.laser.data.angle_increment;
	int imax = (angle_max - in.laser.data.angle_min)/in.laser.data.angle_increment;
	
	double min_scan = std::numeric_limits<double>::max();
	
	for(int ii = imin; ii <= imax; ++ii) {
		if(isnan(in.laser.data.ranges[ii])) {
			continue;
		}
		
		if(in.laser.data.ranges[ii] < min_scan) {
			min_scan = in.laser.data.ranges[ii];
		}
	}
	
	return min_scan;
}


TakeTheBall::~TakeTheBall() {

}