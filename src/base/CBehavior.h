/**
 * @file CBehavior.h
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief abstract class for behaviors
 */

#ifndef	CBEHAVIOR_H
#define	CBEHAVIOR_H

#include <cstdlib>

namespace pteam {

template<typename InputT, typename OutputT>
class CBehavior {
protected:
public:
	
	/**
	 * @fn operator()
	 * @brief the actual function of the behavior
	 * @p in the input, often a processed output from a set of sensors
	 * @p subsume if not NULL, set to false if the following behaviors can be applied, true if they are subsumed
	 * @return an object representing a set of command for the robot
	 */
	virtual OutputT operator()(const InputT& in, bool* subsume = NULL) = 0;
	virtual ~CBehavior() = 0;
};

template<typename InputT, typename OutputT>
CBehavior<InputT, OutputT>::~CBehavior() {}

}

#endif	//CBEHAVIOR_H