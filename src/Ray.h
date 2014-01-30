#ifndef RAY_H
#define RAY_H

#include "Point.h"
#include "Vector.h"

class Ray {
public:
	Ray();
	Ray(const Ray&);
	Ray(Point, Vector);
	~Ray();
	Point getOrigin(void);
	Vector getDirection(void);
	void setPoint(Point);
	void setDirection(Vector);
private:
	Point _p;
	Vector _v;
};

#endif