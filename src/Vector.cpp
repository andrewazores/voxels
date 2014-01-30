#include <math.h>
#include "Vector.h"

// Copy constructor
Vector::Vector(const Vector &b) {
	_x = b._x;
	_y = b._y;
	_z = b._z;
}

// Create a new vector given x, y, and z values (vector from origin to the given point)
Vector::Vector(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
}

// Default constructor is the null vector
Vector::Vector() { _x = 0.0f; _y = 0.0f; _z = 0.0f; }

// Destructor - nothing special, nothing to clean up
Vector::~Vector() { }

// Return X component
float Vector::getX() {
	return _x;
}

// Return Y component
float Vector::getY() {
	return _y;
}

// Return Z component
float Vector::getZ() {
	return _z;
}

// Set X component
void Vector::setX(float x) {
	_x = x;
}

// Set Y component
void Vector::setY(float y) {
	_y = y;
}

// Set Z component
void Vector::setZ(float z) {
	_z = z;
}

// Get magnitude of vector. Can be used along with scalar division to normalize the vector
float Vector::getMagnitude() {
	return sqrt(_x*_x + _y*_y + _z*_z);
}

// Normalize self
void Vector::normalize() {
	float mag = getMagnitude();
	_x /= mag;
	_y /= mag;
	_z /= mag;
}

// Dot product
float Vector::dot(Vector b) {
	return _x*b.getX() + _y*b.getY() + _z*b.getZ();
}

// Define behaviour of vector addition
Vector Vector::operator+(Vector b) {
	Vector v(_x + b.getX(), _y + b.getY(), _z + b.getZ());
	return v; 
}

// Define behaviour of vector subtraction
Vector Vector::operator-(Vector b) {
	Vector v(_x - b.getX(), _y - b.getY(), _z - b.getZ());
	return v;
}

// Define behaviour of vector multiplication, ie cross product
Vector Vector::operator*(Vector b) {
	float x = _y*b.getZ() - b.getY()*_z;
	float y = b.getX()*_z - _x*b.getZ();
	float z = _x*b.getY() - _y*b.getX();

	float scale = sqrt(x*x + y*y + z*z);

	Vector v;
	v._x = x/scale;
	v._y = y/scale;
	v._z = z/scale;

	return v;
}

// Define vector multiplication by scalar
Vector Vector::operator*(float scale) {
	return Vector(_x*scale, _y*scale, _z*scale);
}

// Define vector division by scalar
Vector Vector::operator/(float scale) {
	return Vector (_x/scale, _y/scale, _z/scale);
}

// Define vector comparison - equality
bool Vector::operator==(Vector b) {
	return (_x == b.getX() && _y == b.getY() && _z == b.getZ());
}

// Define vector comparison - inequality
bool Vector::operator!=(Vector b) {
	return (_x != b.getX() || _y != b.getY() || _z != b.getZ());
}
