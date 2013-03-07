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
	////enum
	enum eState {
		eSFirstCall = 0,	//il gripper è alto, devo abbassarlo
		eSWaitingDown,		//il gripper si sta abbassando
		eSMoveForwad,		//il gripper è giu, mi avvicino al target fino a ditance_ball
		eSWaitingUp,		//aspetto che il gripper si sia alzato completamente
		eSWinning			//faccio cose a caso (molto stupide)
	};
	
//   bool m_command_requested;	//se è a true: ho richisto alla forca di abbassarsi, se è a false: non ho richiesto alla forca di abbassarsi
//   bool m_gripper_down;		//se è a true: la forca è giu se a false no
//   bool m_take_ball;		//se è a true la palla è inforcata se è a false no
	
	high_resolution_clock::time_point m_start_time;	//istante iniziale del transitorio della forca
	eState m_state;
  
	////magic numbers
	static double interval_gripper()	{ return 2.0 * 1e+6; }	//Restituisce il tempo impiegato dalla forca per abbassarsi/alzarsi
	static double distance_ball()		{ return 0.25; }		//Restituisce la massima distanza dalla palla dopo la quale possiamo iniziare ad inforcarla
	static double closing_speed()		{
#ifdef	TURBO_MODE
		return 0.2;
#else
		return 0.1;
#endif	//TURB+
	}
  
public:
	TakeTheBall();
	virtual pteam_p2os::RobotControlRequest operator() ( const pteam_p2os::Perception& in, bool* subsume = 0 );
	virtual ~TakeTheBall();
};

}

#endif	//TAKETHEBALL_H