#ifndef POINT_H
#define POINT_H

#include "Vector.h"

class Point {
public:
	Point(void);
	Point(const Point&);
	Point(float, float, float);
	~Point(void);
	float getX(void);
	float getY(void);
	float getZ(void);
	void setX(float);
	void setY(float);
	void setZ(float);
	bool operator==(Point);
	bool operator!=(Point);
	Point operator+(Point);
	Point operator+(Vector);
private:
	float _x, _y, _z;
};

#endif