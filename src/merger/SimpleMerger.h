/**
 * @file SimpleMerger.h
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief output merger
 */

#ifndef SIMPLEMERGER_H
#define SIMPLEMERGER_H

#include <pteam_p2os/RobotControl.h>
#include <base/Common.h>

namespace pteam {
	
template<typename OutputT>
class SimpleMerger {
public:
	/**
	 * @fn Merge
	 * @brief merge the output coming from different level of behaviors
	 * @p outputs the different outputs organized on a multilevel hierarchy
	 * 
	 * The structure of @p outputs is the same in which the behaviors are organized in the BehaviorManager.
	 * The lower the level the higher the priority
	 */
	template<template<class> class ContainerT>
	OutputT Merge(const ContainerT<ContainerT<OutputT> >& outputs);
};

template<>
class SimpleMerger<pteam_p2os::RobotControlRequest> {
	
public:
	/**
	 * @fn Merge
	 * @brief merge the output coming from different level of behaviors
	 * @p outputs the different outputs organized on a multilevel hierarchy
	 * 
	 * The structure of @p outputs is the same in which the behaviors are organized in the BehaviorManager.
	 * The lower the level the higher the priority
	 */
	template<typename T1, typename T2, template<class, class> class ContainerT>
	pteam_p2os::RobotControlRequest Merge(const ContainerT< ContainerT< pteam_p2os::RobotControlRequest, T1>, T2> & outputs) {
		
		pteam_p2os::RobotControlRequest final_output;
		pteam::rstRobotControlRequest(&final_output);
		
		for(auto it = outputs.begin(); it != outputs.end(); ++it) {
			//linear speed
			if(!final_output.linear_speed_set) {
				bool set = false;
				float total_affinity = 0.0f, linear_speed_acc = 0.0f;
				for(auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
					set = set || it2->linear_speed_set;
					if(it2->linear_speed_set) {
						linear_speed_acc += it2->linear_speed * it2->affinity;
						total_affinity += it2->affinity;
					}
				}
				
				if(set) {
					final_output.linear_speed_set = true;
					final_output.linear_speed = linear_speed_acc / total_affinity;
				}
			}
			
			//angular speed
			if(!final_output.angular_speed_set) {
				bool set = false;
				float total_affinity = 0.0f, angular_speed_acc = 0.0f;
				for(auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
					set = set || it2->angular_speed_set;
					if(it2->angular_speed_set) {
						angular_speed_acc += it2->angular_speed * it2->affinity;
						total_affinity += it2->affinity;
					}
				}
				
				if(set) {
					final_output.angular_speed_set = true;
					final_output.angular_speed = angular_speed_acc / total_affinity;
				}
			}
			
			//gripper movement
			if(!final_output.gripper_move_set) {
				for(auto it2 = it->begin(); it2 != it->end(); ++it2) {
					if(it2->gripper_move_set) {
						final_output.gripper_move_set = true;;
						final_output.gripper_move_down = it2->gripper_move_down;
					}
				}
			}
		}
		
		return final_output;
	}
	
	
	///WORKING
// 	template<template<class, class> class ContainerT>
// 	pteam_p2os::RobotControlRequest Merge(const ContainerT< ContainerT< pteam_p2os::RobotControlRequest, std::allocator<pteam_p2os::RobotControlRequest> >, std::allocator<ContainerT< pteam_p2os::RobotControlRequest, std::allocator<pteam_p2os::RobotControlRequest> > > >& outputs) {
// 	}
};

}

#endif	//SIMPLEMERGER_H