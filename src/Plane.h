#ifndef PLANE_H
#define PLANE_H

#include "Point.h"
#include "Ray.h"
#include "Vector.h"

class Plane {
public:
	Plane(void);
	Plane(const Plane&);
	Plane(Point, Point, Point, Vector, float);
	Plane(Point, Vector, Vector, Vector, float);
	~Plane(void);
	void getPoints(Point&);
	void setNormal(Vector);
	Vector getNormal(void);
	void setHeight(float);
	float getHeight(void);
	Point rayIntersection(Ray);
private:
	float _D;
	Point _p0, _p1, _p2;
	Vector _norm;
};

#endif