/**
 * @file Circle.h
 * @author Ryu, Jae Hun ( ryu@geguri.kjist.ac.kr)
 */

#ifndef	CIRCLE_H
#define CIRCLE_H

////standard libs
#include <cmath>
#include <iostream>
////pteam
#include <base/Common.h>
#include <base/RANSAC.h>

namespace pteam {

class Circle {
public:
	
	typedef Point2d point_type;
	
	Circle(point_type &V1, point_type &V2, point_type &V3) { 	// p1, p2, p3 are co-planar
		std::vector<point_type> v;
		v.push_back(V1);
		v.push_back(V2);
		v.push_back(V3);
		CreateModel(v);
	}
	
	Circle(const std::vector<point_type>& v) {
		CreateModel(v);
	}
	
	Circle() {
		this->m_dRadius=-1;		// error checking 
	}
	
	virtual ~Circle() {}
	
	double GetRadius() const {
		return this->m_dRadius;
	}
	
	const Point2d& GetCenter() const {
		return this->m_Center;
	}
	
	void CreateModel(const std::vector< Point2d >& points) {
		assert(points.size() == 3);
		
		// p1, p2, p3 are co-planar
		this->m_dRadius=-1;		// error checking 
		
		point_type *pt1=new point_type();
		point_type *pt2=new point_type();
		point_type *pt3=new point_type();
		
		*pt1 = points[1];
		*pt2 = points[2];
		*pt3 = points[3];
		
		if (!this->IsPerpendicular(pt1, pt2, pt3) )			this->CalcCircle(pt1, pt2, pt3);	
		else if (!this->IsPerpendicular(pt1, pt3, pt2) )		this->CalcCircle(pt1, pt3, pt2);	
		else if (!this->IsPerpendicular(pt2, pt1, pt3) )		this->CalcCircle(pt2, pt1, pt3);	
		else if (!this->IsPerpendicular(pt2, pt3, pt1) )		this->CalcCircle(pt2, pt3, pt1);	
		else if (!this->IsPerpendicular(pt3, pt2, pt1) )		this->CalcCircle(pt3, pt2, pt1);	
		else if (!this->IsPerpendicular(pt3, pt1, pt2) )		this->CalcCircle(pt3, pt1, pt2);	
		else { 
			// 			TRACE("\nThe three pts are perpendicular to axis\n");
			//		pt1->trace();			pt2->trace();			pt3->trace();
			delete pt1;
			delete pt2;
			delete pt3;
			this->m_dRadius=-1;
			return ;
		}
		delete pt1;
		delete pt2;
		delete pt3;	
	}
	
	static int NPoints() { return 3; }
	
	

private:
	double CalcCircle(point_type *pt1, point_type *pt2, point_type *pt3) {
		double yDelta_a= pt2->y - pt1->y;
		double xDelta_a= pt2->x - pt1->x;
		double yDelta_b= pt3->y - pt2->y;
		double xDelta_b= pt3->x - pt2->x;
		
		if (fabs(xDelta_a) <= 0.000000001 && fabs(yDelta_b) <= 0.000000001){
// 			TRACE("Calc cirlce \n");
			this->m_Center.x= 0.5*(pt2->x + pt3->x);
			this->m_Center.y= 0.5*(pt1->y + pt2->y);
			this->m_Center.z= pt1->z;
			this->m_dRadius= length(m_Center,*pt1);		// calc. radius
			//		TRACE(" Center: %f %f %f\n", m_Center.x(), m_Center.y(), m_Center.z());
			//		TRACE(" radius: %f %f %f\n", length(&m_Center,pt1), length(&m_Center,pt2),length(&m_Center,pt3));
			
			return this->m_dRadius;
		}
		
		// IsPerpendicular() assure that xDelta(s) are not zero
		double aSlope=yDelta_a/xDelta_a; // 
		double bSlope=yDelta_b/xDelta_b;
		if (fabs(aSlope-bSlope) <= 0.000000001){	// checking whether the given points are colinear. 	
// 		TRACE("The three pts are colinear\n");
		return -1;
		}
		
		// calc center
		this->m_Center.x= (aSlope*bSlope*(pt1->y - pt3->y) + bSlope*(pt1->x + pt2 ->x)
		- aSlope*(pt2->x+pt3->x) )/(2* (bSlope-aSlope) );
		this->m_Center.y = -1*(m_Center.x - (pt1->x+pt2->x)/2)/aSlope +  (pt1->y+pt2->y)/2;
		this->m_Center.z= pt1->z;
		
		this->m_dRadius= length(m_Center,*pt1);		// calc. radius
		//	TRACE(" Center: %f %f %f\n", m_Center.x(), m_Center.y(), m_Center.z());
		//	TRACE(" radius: %f %f %f\n", length(&m_Center,pt1), length(&m_Center,pt2),length(&m_Center,pt3));
		return this->m_dRadius;
	}
	
	bool IsPerpendicular(point_type *pt1, point_type *pt2, point_type *pt3) {
		double yDelta_a= pt2->y - pt1->y;
		double xDelta_a= pt2->x - pt1->x;
		double yDelta_b= pt3->y - pt2->y;
		double xDelta_b= pt3->x - pt2->x;
		
		
		//	TRACE(" yDelta_a: %f xDelta_a: %f \n",yDelta_a,xDelta_a);
		//	TRACE(" yDelta_b: %f xDelta_b: %f \n",yDelta_b,xDelta_b);
		
		// checking whether the line of the two pts are vertical
		if (fabs(xDelta_a) <= 0.000000001 && fabs(yDelta_b) <= 0.000000001){
// 			TRACE("The points are pependicular and parallel to x-y axis\n");
			return false;
		}
		
		if (fabs(yDelta_a) <= 0.0000001){
			//		TRACE(" A line of two point are perpendicular to x-axis 1\n");
			return true;
		}
		else if (fabs(yDelta_b) <= 0.0000001){
			//		TRACE(" A line of two point are perpendicular to x-axis 2\n");
			return true;
		}
		else if (fabs(xDelta_a)<= 0.000000001){
			//		TRACE(" A line of two point are perpendicular to y-axis 1\n");
			return true;
		}
		else if (fabs(xDelta_b)<= 0.000000001){
			//		TRACE(" A line of two point are perpendicular to y-axis 2\n");
			return true;
		}
		else return false ;
	}
	
	double length(const point_type& p1, const point_type& p2) {
		return std::sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
	}
	
	double m_dRadius;
	Point m_Center;
};

std::ostream& operator<<(std::ostream& out, const Circle& c) {
	out << "Center x: " << c.GetCenter().x << ", y: " << c.GetCenter().y << "\nRadius: " << c.GetRadius();
	return out;
}

}

#endif //CIRCLE_H
