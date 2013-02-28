/**
 * @file OutputMerger.h
 * @author Daniele Molinari -- 238168 ()
 * @version 1.0
 * @brief template object that merge output command from different levels
 */

#ifndef OUTPUTMERGER_H
#define OUTPUTMERGER_H

template<typename OutputT>
class SimplePriorityMerger {
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

template<typename OutputT>
class DummyMerger {
public:
	template<template<class> class ContainerT>
	OutputT Merge(const ContainerT<ContainerT<OutputT> >& outputs);
};

template<>
class DummyMerger<double> {
public:
	template<template<class> class ContainerT>
	double Merge( const ContainerT< ContainerT< double> >& outputs ) {
		return outputs[0][0];
    }
};

#endif	//OUTPUTMERGER_H