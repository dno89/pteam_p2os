/**
 * @file Common.h
 * @author Daniele Molinari -- 238168
 * @brief common struct and definition
 */

#ifndef	COMMON_H
#define COMMON_H

#include <stdexcept>
#include <pteam_p2os/RobotControl.h>

//macro to cnovert from degree to radians
#define DEG_TO_RAD(X) X * 0.01745329252
//macro to cnovert from radians to degree
#define RAD_TO_DEG(X) X * 57.29577951

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

/**
 * @fn ResetRobotControlRequest
 * @brief reset a robot control request
 */

template<typename ReqT>
void rstRobotControlRequest(ReqT* r);

template<>
void rstRobotControlRequest<pteam_p2os::RobotControlRequest> (pteam_p2os::RobotControlRequest* r) {
	r->angular_speed_set = false;
	r->angular_speed = 0.0;
	r->linear_speed_set = false;
	r->linear_speed = 0.0;
	r->gripper_move_set = false;
}

}

#endif	//COMMON_H 