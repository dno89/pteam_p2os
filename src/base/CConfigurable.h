/**
 * @file CConfigurable.h
 * @author Daniele Molinari (daniele.molinari2@studenti.unipr.it)
 * @brief configuration through arbitrary-value properties with names
 * @version 1.1
 */

#ifndef CCONFIGURABLE_H
#define CCONFIGURABLE_H

#include <boost/any.hpp>
#include <typeinfo>
#include <map>
#include <vector>
#include <stdexcept>

/**
 * @class CConfigurable
 * @brief this class can be inherited by object that need a dynamic configuration without specific function calls.
 * 
 * This class store a map of property of any type which can be refered by their name.
 * Type checking is done at runtime, so you must know what is the type of the property you are setting/reading (no automatic conversion can be used, so is your responsability to cast to a proper type).
 */
class CConfigurable {
public:
	/**
	 * @fn ReadProperty
	 * @brief read the value of the property ID
	 * 
	 * This template-function's template argument, must be explicitly defined because no type deduction is possible.
	 * An exception is thrown if the type @p T doesn't match the type of the property @p ID, or if the property @p ID doesn't exist.
	 */
	template<typename T>
	T ReadProperty(const std::string& ID) const {
		//check whether the property exists
		if(m_properties.count(ID) == 0) {
			//the property doesn't exist
			throw std::runtime_error("CConfigurable::ReadProperty ERROR: property "+ID+" doesn't exist!\n");
		}
		
		//type check
		if(typeid(T) != m_properties[ID].type()) {
			//type are different
			throw std::runtime_error("CConfigurable::ReadProperty ERROR: function called with type " + 
			std::string(typeid(T).name()) + 
			", but \"" + ID + "\" has type " + std::string(m_properties[ID].type().name()) + "!\n");
		}
		
		//everything is fine, read the property
		return boost::any_cast<T>(m_properties[ID]);
	}
	
	/**
	 * @fn ReadProperty
	 * @brief read the value of the property ID
	 * 
	 * An exception is thrown if the type @p T doesn't match the type of the property @p ID, or if the property @p ID doesn't exist.
	 */
	template<typename T>
	void ReadProperty(const std::string& ID, T* value) const {
		//check whether the property exists
		if(m_properties.count(ID) == 0) {
			//the property doesn't exist
			throw std::runtime_error("CConfigurable::ReadProperty ERROR: property "+ID+" doesn't exist!\n");
		}
		
		//type check
		if(typeid(T) != m_properties[ID].type()) {
			//type are different
			throw std::runtime_error("CConfigurable::ReadProperty ERROR: \"value\" has type " + 
			std::string(typeid(value).name()) + 
			", but \"" + ID + "\" has type " + std::string(m_properties[ID].type().name()) + "!\n");
		}
		
		//everything is fine, read the property
		*value = boost::any_cast<T>(m_properties[ID]);
	}
	
	/**
	 * @fn SetProperty
	 * @brief set the value of the property ID
	 * 
	 * An exception is thrown if the type @p T doesn't match the type of the property @p ID, or if the property @p ID doesn't exist.
	 */
	template<typename T>
	void SetProperty(const std::string& ID, const T& value) {
		//check whether the property exists
		if(m_properties.count(ID) == 0) {
			//the property doesn't exist
			throw std::runtime_error("CConfigurable::SetProperty ERROR: property "+ID+" doesn't exist!\n");
		}
		
		//type check
		if(typeid(T) != m_properties[ID].type()) {
			//type are different
			throw std::runtime_error("CConfigurable::SetProperty ERROR: \"value\" has type " + 
			std::string(typeid(value).name()) + 
			", but \"" + ID + "\" has type " + std::string(m_properties[ID].type().name()) + "!\n");
		}
		
		//everything is fine, do the assignment
		m_properties[ID] = value;
	}
	
	/**
	 * @fn Properties
	 * @brief return the name of all properties
	 * @return a vector with the name of all properties
	 */
	std::vector<std::string> Properties() const {
		std::vector<std::string> names;
		for(typename std::map<std::string, boost::any>::const_iterator it = m_properties.begin(); it != m_properties.end(); ++it) {
			names.push_back(it->first);
		}
		
		return names;
	}
	
	/**
	 * @fn PropertiesWTypes
	 * @brief return the name of all properties with the relative type
	 * @return a vector of pair, containing the name of all properties and the relative type
	 */
// 	std::vector<std::pair<std::string, std::type_info> > PropertiesWTypes() const;
	
	/**
	 * @fn PropertiesWValues
	 * @brief return the name of all properties with the relative value
	 * @return a vector of pair, containing the name of all properties and the relative value
	 */
// 	std::vector<std::pair<std::string, boost::any> > PropertiesWValues() const;
protected:
	
	/**
	 * @fn AddProperty
	 * @brief add a new property
	 * @note in case the property @p ID already exists, this call has no effect
	 * 
	 * Add a new property with id @p ID, type @p T and value @p default_value
	 */
	template<typename T>
	void AddProperty(const std::string& ID, const T& default_value) {
		m_properties.insert(std::make_pair<std::string, boost::any>(ID, default_value));
	}
	
private:
	mutable std::map<std::string, boost::any> m_properties;
};

#endif	//CCONFIGURABLE_H
