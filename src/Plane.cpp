#include "Plane.h"

// Constructor for an uninitialized plane
Plane::Plane() {
	_p0 = Point();
	_p1 = Point();
	_p2 = Point();
	_D = 0.0f;
	_norm = Vector();
}

// Copy constructor
Plane::Plane(const Plane &b) {
	_p0 = b._p0;
	_p1 = b._p1;
	_p2 = b._p2;
	_D = b._D;
	_norm = b._norm;
}

// Construct a plane given three points, the normal of the plane, and its height offset
Plane::Plane(Point p0, Point p1, Point p2, Vector n, float b) {
	_p0 = p0;
	_p1 = p1;
	_p2 = p2;
	_D = b;
	// We can't just determine the normal from the points given because the vector we find could be the negative
	// of the vector expected by the caller of this function, unless we define that the points must be entered
	// in a specific order. It's more convenient to specify the normal directly and just assume the given vector
	// is actually a normal to this plane
	_norm = n;
}

// Construct a plane given a point and two vectors leading away from it to describe the plane,
// as well as its normal, and its height offset
Plane::Plane(Point p0, Vector v0, Vector v1, Vector n, float b) {
	_p0 = p0;
	_p1 = Point(p0.getX() + v0.getX(), p0.getY() + v0.getY(), p0.getZ() + v0.getZ());
	_p2 = Point(p0.getX() + v1.getX(), p0.getY() + v1.getY(), p0.getZ() + v1.getZ());
	_D = b;
	_norm = n;
}

// Destructor
Plane::~Plane() { }

// "Return" three points defining this plane in Point array b
void Plane::getPoints(Point &b) {
	Point result[3] = {_p0, _p1, _p2};
	b = *result;
}

// Set the normal of this plane
void Plane::setNormal(Vector b) {
	_norm = b;
}

// Return the normal of this plane
Vector Plane::getNormal() {
	return _norm;
}

// Set the height offset of this plane
void Plane::setHeight(float h) {
	_D = h;
}

// Get the height offset of this plane
float Plane::getHeight() {
	return _D;
}

// Test the given ray if it intersects with this plane, and if it does, where. Return the
// point of intersection (if no intersection, return the point (-1, -1, -1)).
// TODO: an uninitialized point returned as an actual result is not a very good solution.
// Refactor this to be smarter.
Point Plane::rayIntersection(Ray ray) {
	Vector Rd = ray.getDirection();
	Rd.normalize();

	Point origin = ray.getOrigin();
	Vector R0 = Vector(origin.getX(), origin.getY(), origin.getZ());

	if (_norm.dot(Rd) != 0) {
		float t = (-_norm.dot(R0) + _D)/_norm.dot(Rd);
		Vector vr = Vector(R0 + Rd * t);
		return Point(vr.getX(), vr.getY(), vr.getZ());
	} else {
		return Point(-1.0f, -1.0f, -1.0f);
	}
}
