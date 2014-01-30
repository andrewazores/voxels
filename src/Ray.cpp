#include "Ray.h"

// Constructor for an uninitialized ray
Ray::Ray() {
	_p = Point();
	_v = Vector();
}


// Copy constructor
Ray::Ray(const Ray &b) {
	_p = b._p;
	_v = b._v;
}

// Create a ray given a point and vector
Ray::Ray(Point p, Vector v) {
	_p = p;
	_v = v;
}

// Destructor, don't do anything special
Ray::~Ray() { }

// Return the origin of this ray
Point Ray::getOrigin() {
	return _p;
}

// Return the direction vector of this ray
Vector Ray::getDirection() {
	return _v;
}

// Set the origin of this ray
void Ray::setPoint(Point p) {
	_p = p;
}

// Set the direcetion vector of this ray
void Ray::setDirection(Vector v) {
	_v = v;
}
