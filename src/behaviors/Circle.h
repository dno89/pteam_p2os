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
	////typedef
	typedef Point3d Point;
	typedef Point2d reduced_point_type;
	
	double GetRadius() const {
		return this->m_dRadius;
	}
	const reduced_point_type GetCenter() const {
		return reduced_point_type(m_Center.x, m_Center.y);
	}
	
	Circle(Point &V1, Point &V2, Point &V3) { 	// p1, p2, p3 are co-planar
		create_model(V1, V2, V3);
	}
	
	Circle(const std::vector<reduced_point_type>& points) {
		CreateModel(points);
	}
	
	void CreateModel(const std::vector<reduced_point_type>& points) {
		assert(points.size() == 3);
		Point p1(points[0].x, points[0].y, 0.0), p2(points[1].x, points[1].y, 0.0), p3(points[2].x, points[2].y, 0.0);
		
		create_model(p1, p2, p3);
	}
	
	Circle() {
		this->m_dRadius=-1;		// error checking 
	}
	
	~Circle() {}
	
	static int NPoints() { return 3; }
	
	double operator()(const reduced_point_type& p) {
		return std::abs(std::sqrt((p.x - m_Center.x)*(p.x - m_Center.x) + (p.y - m_Center.y)*(p.y - m_Center.y)) - m_dRadius);
	}

private:
	double length(const Point& p1, const Point& p2) {
		return std::sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z));
	}
	
	double CalcCircle(Point *pt1, Point *pt2, Point *pt3) {
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
	
	bool IsPerpendicular(Point *pt1, Point *pt2, Point *pt3) {
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
	
	void create_model(Point &V1, Point &V2, Point &V3) {
		this->m_dRadius=-1;		// error checking 
		
		Point *pt1=new Point();
		Point *pt2=new Point();
		Point *pt3=new Point();
		
		*pt1 = V1;
		*pt2 = V2;
		*pt3 = V3;
		
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
	
	
	double m_dRadius;
	Point m_Center;
};

std::ostream& operator<<(std::ostream& out, const Circle& c) {
	out << "Center x: " << c.GetCenter().x << ", y: " << c.GetCenter().y << "\nRadius: " << c.GetRadius();
	return out;
}

}

#endif //CIRCLE_H
