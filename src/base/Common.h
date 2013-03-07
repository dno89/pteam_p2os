/**
 * @file Common.h
 * @author Daniele Molinari -- 238168
 * @brief common struct and definition
 */

#ifndef	COMMON_H
#define COMMON_H

#include <stdexcept>
#include <iostream>
#include <pteam_p2os/RobotControl.h>
#include <geometry_msgs/Pose.h>
#include <Eigen/Dense>

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


/**
 * Find non NAN value in an array like container (accessed through operator[])
 */
template<typename ContainerT>
inline typename ContainerT::value_type first_number_after(const ContainerT& v, int index) {
	while(isnan(v[index])) {
		++index;
		if(index == v.size()) {
			//end of container
			return NAN;
		}
	}
	return v[index];
}
template<typename ContainerT>
inline typename ContainerT::value_type first_number_before(const ContainerT& v, int index) {
	while(isnan(v[index])) {
		--index;
		if(index < 0) {
			//end of container
			return NAN;
		}
	}
	return v[index];
}


/**
 * @fn NLWAverage
 * Non-linear weighted average
 * 
 * @param a the first value
 * @param b the second value
 * @param Wb the weight of a
 * @param Wb the weight of b
 * 
 * Return a weighted average.
 * alpha the weight ratio: W_a / (W_a + W_b)
 * alpha = 1 --> @p a
 * alpha = 0 --> @p b
 * 
 * In between the value is close to (@p a + @p b) / 2
 * The higher n, the closer it resemble a    \__
 * 												\
 */
inline double NLWAverage(double a, double b, double Wa, double Wb, int n) {
	double alpha = Wa / (Wa + Wb);
	return (b-a)/2.0 * std::pow(-(2*alpha - 1), 2*n+1) + (a+b)/2.0;
}

/******************************************************************************
 * 							POINTS												*
 * ****************************************************************************/
/**
 * @struct Point2
 * 
 * Template to hold a point in a 2D space
 */
template<typename T>
struct Point2 {
	////typedef
	typedef T base_type;
	////data
	T x, y;
	////functions
	Point2(T x_ = T(0), T y_ = T(0)) : x(x_), y(y_) {}
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Point2<T>& p) {
	out << "x: " << p.x << "\ny: " << p.y;
	return out;
}

typedef Point2<double> Point2d;
typedef Point2<float> Point2f;

template<typename T>
double Lenght(const Point2<T>& p) {
	return std::sqrt(p.x*p.x + p.y*p.y);
}


template<typename T>
struct Point3 {
	typedef T base_type;
	
	Point3(base_type x_ = base_type(0), base_type y_ = base_type(0), base_type z_ = base_type(0)) :
	x(x_), y(y_), z(z_) {}
	
	////data
	T x, y, z;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Point3<T>& p) {
	out << "x: " << p.x << "\ny: " << p.y << "\nz: " << p.z;
	return out;
}

typedef Point3<double> Point3d;
typedef Point3<float> Point3f;

/******************************************************************************
 * 							TARGET												*
 * ****************************************************************************/

struct Target : public Point2d {
	////data
	base_type radius;
	
	Target ( base_type x_ = base_type( 0 ), base_type y_ = base_type( 0 ), base_type radius_ = base_type(0) ) : radius(radius_), Point2d(x_, y_) {}
};

double TargetDistance2(const Target& t1, const Target& t2) {
	return std::pow(t1.x-t2.x, 2) + std::pow(t1.y-t2.y, 2) + std::pow(t1.radius-t2.radius, 2);
}

std::ostream& operator<<(std::ostream& out, const Target& t) {
	out << "x: " << t.x << "\ny: " << t.y << "\nradius: " << t.radius;
	return out;
}

/******************************************************************************
 * 							POSE												*
 * ****************************************************************************/

struct SimplePose : Point2d {
	////data
	base_type theta;
	
	SimplePose ( base_type x_ = base_type ( 0 ), base_type y_ = base_type ( 0 ), base_type theta_ = base_type(0)  ) : Point2d(x_, y_), theta(theta_) {}
};

std::ostream& operator<<(std::ostream& out, const SimplePose& t) {
	out << "x: " << t.x << "\ny: " << t.y << "\ntheta: " << t.theta;
	return out;
}

/******************************************************************************
 * 							SUPPORT FUNCTIONS									*
 * ****************************************************************************/
SimplePose OdomToSimplePose(const geometry_msgs::Pose& pose) {
// 	double theta = atan2(2.0*(pose.orientation.x*pose.orientation.w + pose.orientation.y*pose.orientation.z), 1.0 - 2.0*(pose.orientation.z*pose.orientation.z + pose.orientation.w*pose.orientation.w));
	double theta = asin(2.0*pose.orientation.z*pose.orientation.w);
	return SimplePose(pose.position.x, pose.position.y, theta);
}

Target RotateTarget(const Target& t, const SimplePose& old_pose, const SimplePose& new_pose) {
	double dx = old_pose.x - new_pose.x, dy = old_pose.y - new_pose.y, dt = old_pose.theta - new_pose.theta;
	Eigen::Matrix3d rot_matrix;
	
	double c = std::cos(dt);
	double s = std::sin(dt);
	
	//constant terms
	rot_matrix(2, 0) = 0.0;
	rot_matrix(2, 1) = 0.0;
	rot_matrix(2, 2) = 1.0;
	
	//rotation matrix
	rot_matrix(0, 0) = c;
	rot_matrix(1, 0) = s;
	rot_matrix(0, 1) = -s;
	rot_matrix(1, 1) = c;
	
	//translation terms
	rot_matrix(0, 2) = dx;
	rot_matrix(1, 2) = dy;
	
	Eigen::Vector3d p;
	p << t.x, t.y, 1.0;
	
	Eigen::Vector3d new_t = rot_matrix*p;
	
	return Target(new_t[0], new_t[1], t.radius);
}

}

#endif	//COMMON_H 