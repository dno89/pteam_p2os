/**
 * @file BehaviorManager.h
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief a simple behavior manager that implement a subsumption-like policy
 */

#ifndef	BEHAVIORMANAGER_H
#define	BEHAVIORMANAGER_H

#include <vector>
#include <string>
#include <stdexcept>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "CBehavior.h"

namespace pteam {

template<typename InputT, typename OutputT, template<class> class OutputMergerT>
class BehaviorManager {
public:
	/**
	 * @fn AddBehaviorsLevel
	 * @brief add another level in the behavior hierarchy
	 * @return the number of the current behavior (the higher the level the lower the priority)
	 */
	unsigned int AddBehaviorsLevel();
	
	/**
	 * @fn AddBehavior
	 * @brief add a new behavior on the specified level 
	 * @p level the level at which insert the behavior
	 */
	void AddBehavior(unsigned int level, CBehavior<InputT, OutputT>* new_behavior);
	
	/**
	 * @fn RunBehaviors
	 * @brief execute the hierarchy of behaviors and return the resulting output
	 * @return the resulting output obtained from the proper combination of single behaviors' output
	 */
	OutputT RunBehaviors(const InputT& in);
	
private:
	typedef CBehavior<InputT, OutputT> behavior_t;
	typedef boost::shared_ptr<behavior_t > shared_prt_t;
	
	//the behavior in a multilevel architecture (with multiple behavior on the same level)
	std::vector<std::vector<shared_prt_t> > m_behaviors;
	//the output merger
	OutputMergerT<OutputT> m_merger;
};

template<typename InputT, typename OutputT, template<class> class OutputMergerT>
unsigned int BehaviorManager<InputT, OutputT, OutputMergerT>::AddBehaviorsLevel() {
	m_behaviors.push_back(std::vector<shared_prt_t>());
	return m_behaviors.size()-1;
}

template<typename InputT, typename OutputT, template<class> class OutputMergerT>
void BehaviorManager<InputT, OutputT, OutputMergerT>::AddBehavior(unsigned int level, CBehavior<InputT, OutputT>* new_behavior) {
	if(level >= m_behaviors.size()) {
		//level out of range
		throw std::runtime_error("BehaviorManager<>::AddBehavior ERROR: level = " + boost::lexical_cast<std::string, int>(level) + ", out of range!\n");
	}
	
	m_behaviors[level].push_back(shared_prt_t(new_behavior));
}

template<typename InputT, typename OutputT, template<class> class OutputMergerT>
OutputT BehaviorManager<InputT, OutputT, OutputMergerT>::RunBehaviors(const InputT& in) {
	std::vector<std::vector<OutputT> > outputs;
	
	bool subsume = false;
	for(typename std::vector<std::vector<boost::shared_ptr<CBehavior<InputT, OutputT> > > >::iterator it = m_behaviors.begin(); it != m_behaviors.end(); ++it) {
		//for each level
		outputs.push_back(std::vector<OutputT>());
		for(typename std::vector<boost::shared_ptr<CBehavior<InputT, OutputT> > >::iterator bit = it->begin(); bit != it->end(); ++bit) {
			//for each behavior in this level
			bool f;
			//store the output
			outputs[outputs.size()-1].push_back((*bit)->operator()(in, &f));
			subsume = subsume || f;
		}
		
		//if subsume, do not propagate to higher level
		if(subsume) break;
	}
	
	return m_merger.Merge(outputs);
}

}

#endif	//BEHAVIORMANAGER_H