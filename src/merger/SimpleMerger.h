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
		
		///TODO:
		
		return final_output;
	}
	
	
	///WORKING
// 	template<template<class, class> class ContainerT>
// 	pteam_p2os::RobotControlRequest Merge(const ContainerT< ContainerT< pteam_p2os::RobotControlRequest, std::allocator<pteam_p2os::RobotControlRequest> >, std::allocator<ContainerT< pteam_p2os::RobotControlRequest, std::allocator<pteam_p2os::RobotControlRequest> > > >& outputs) {
// 		///TODO:
// 	}
};

}

#endif	//SIMPLEMERGER_H