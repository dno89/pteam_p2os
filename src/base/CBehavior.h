/**
 * @file CBehavior.h
 * @author Daniele Molinari -- 238168
 * @version 1.0
 * @brief abstract class for behaviors
 */

#ifndef	CBEHAVIOR_H
#define	CBEHAVIOR_H


#include <boost/any.hpp>
#include <cstdlib>
#include <map>
#include <string>
#include <stdexcept>

namespace pteam {

template<typename InputT, typename OutputT>
class CBehavior {
	static std::map<std::string, boost::any> shared_map;
protected:
	template<typename T>
	void AddProperty(const std::string& ID, const T& default_value) {
		shared_map.insert(std::make_pair(ID, boost::any(default_value)));
	}
	
	template<typename T>
	void SetProperty(const std::string& ID, const T& value) {
		//check whether the property exists
		if(shared_map.count(ID) == 0) {
			//the property doesn't exist
			throw std::runtime_error("CConfigurable::SetProperty ERROR: property "+ID+" doesn't exist!\n");
		}
		
		//type check
		if(typeid(T) != shared_map[ID].type()) {
			//type are different
			throw std::runtime_error("CConfigurable::SetProperty ERROR: \"value\" has type " + 
			std::string(typeid(value).name()) + 
			", but \"" + ID + "\" has type " + std::string(shared_map[ID].type().name()) + "!\n");
		}
		
		//everything is fine, do the assignment
		shared_map[ID] = value;
	}
	
	template<typename T>
	T ReadProperty(const std::string& ID) const {
		//check whether the property exists
		if(shared_map.count(ID) == 0) {
			//the property doesn't exist
			throw std::runtime_error("CBehavior::ReadProperty ERROR: property "+ID+" doesn't exist!\n");
		}
		
		//type check
		if(typeid(T) != shared_map[ID].type()) {
			//type are different
			throw std::runtime_error("CBehavior::ReadProperty ERROR: function called with type " + 
			std::string(typeid(T).name()) + 
			", but \"" + ID + "\" has type " + std::string(shared_map[ID].type().name()) + "!\n");
		}
		
		//everything is fine, read the property
		return boost::any_cast<T>(shared_map[ID]);
	}
	
	template<typename T>
	void ReadProperty(const std::string& ID, T* value) const {
		//check whether the property exists
		if(shared_map.count(ID) == 0) {
			//the property doesn't exist
			throw std::runtime_error("CConfigurable::ReadProperty ERROR: property "+ID+" doesn't exist!\n");
		}
		
		//type check
		if(typeid(T) != shared_map[ID].type()) {
			//type are different
			throw std::runtime_error("CConfigurable::ReadProperty ERROR: \"value\" has type " + 
			std::string(typeid(value).name()) + 
			", but \"" + ID + "\" has type " + std::string(shared_map[ID].type().name()) + "!\n");
		}
		
		//everything is fine, read the property
		*value = boost::any_cast<T>(shared_map[ID]);
	}
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