#include "Point.h"

// Constructor for an uninitialized point
Point::Point() {
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}

// Copy constructor
Point::Point(const Point &b) {
	_x = b._x;
	_y = b._y;
	_z = b._z;
}

// Construct a point given three floating point values for its position
Point::Point(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
}

// Destructor
Point::~Point() { }

// Return the X coordinate of this point
float Point::getX() {
	return _x;
}

// Return the Y coordinate of this point
float Point::getY() {
	return _y;
}

// Return the Z coordinate of this point
float Point::getZ() {
	return _z;
}

// Set the X coordinate of this point
void Point::setX(float x) {
	_x = x;
}

// Set the Y coordinate of this point
void Point::setY(float y) {
	_y = y;
}

// Set the Z coordinate of this point
void Point::setZ(float z) {
	_z = z;
}

// Define point equality
bool Point::operator==(Point b) {
	return (_x == b._x && _y == b._y && _z == b._z);
}

// Define point inequality
bool Point::operator!=(Point b) {
	return (_x != b._x || _y != b._y || _z != b._z);
}

// Define point addition
Point Point::operator+(Point b) {
	float x = _x + b.getX();
	float y = _y + b.getY();
	float z = _z + b.getZ();
	return Point(x, y, z);
}

// Define adding a vector to a point
Point Point::operator+(Vector v) {
	float x = _x + v.getX();
	float y = _y + v.getY();
	float z = _z + v.getZ();
	return Point(x, y, z);
}
