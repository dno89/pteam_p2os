/**
 * @file Common.h
 * @author Daniele Molinari -- 238168
 * @brief common struct and definition
 */

#ifndef	COMMON_H
#define COMMON_H

#include <stdexcept>

namespace pteam {

/**
 * @class Value
 * @p T the type to hold
 * 
 * A simple class that hold a value, but can represent the absence of a proper value.
 * Once declared is used as a normal variable of type @p T (except for some complicated operation), but remain "unset" until a value is assigned.
 * The presence of a value can be tested with IsSet() or with the comparision against UndefinedValue.
 * The value can be reset with Reset() or with the assignment of UndefinedValue
 */
//struct used for comparision
struct _UndefinedValue {};
#define UndefinedValue _UndefinedValue()

template<typename T>
struct Value {
private:
	bool set;
	T value;
public:
	//constructors
	Value() : set(false) {}
	Value(const T& ref) : set(true), value(ref) {}
	template<typename R>
	Value(const R& ref) : set(true), value(ref) {}
	//copy constructor
	template<typename R>
	Value(const Value<R>& ref) : set(ref.set), value(ref.value) {}
	//functions
	bool IsSet() {return set;}
	void Reset() {set = false;}
	//some operators
	template<typename R>
	Value<T>& operator=(const R& rval) {
		value = (T)rval;
		set = true;
		return *this;
	}
	Value<T>& operator=(const _UndefinedValue&) {
		set = false;
		return *this;
	}
	//comparision return always false is set==false
	template<typename R>
	bool operator==(const R& rval) {
		return (value == (const T&)rval) && set;
	}
	bool operator==(const _UndefinedValue&) {
		return !set;
	}
	//automatic conversion
	operator T(){
		if(!set) {
			throw std::runtime_error("Value<> ERROR: value not set!\n");
		}
		return value;
	}
};

}

#endif	//COMMON_H 