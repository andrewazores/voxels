#include "Camera.h"

// Default constructor - camera at origin and null directional look vector
Camera::Camera() {
	_xloc = 0.0f;
	_yloc = 0.0f;
	_zloc = 0.0f;
	_vec = Vector();
}

// Construct a camera given a location and direction to look
Camera::Camera(float xl, float yl, float zl, Vector v) {
	_xloc = xl;
	_yloc = yl;
	_zloc = zl;
	_vec = v;
}

// Destructor - nothing special, no cleanup required
Camera::~Camera() { }

// Update camera view
void Camera::update() {
	gluLookAt( _xloc,_yloc,_zloc, _xloc+_vec.getX(),_yloc+_vec.getY(),_zloc+_vec.getZ(), 0,0,1 );
}

// Change the directional look vector
void Camera::setVector(Vector v) {
	_vec = v;
}

// Set absolute X location
void Camera::setXLoc(float x) {
	_xloc = x;
}

// Set absolute Y location
void Camera::setYLoc(float y) {
	_yloc = y;
}

// Set absolute Z location
void Camera::setZLoc(float z) {
	_zloc = z;
}

// Return X location
float Camera::getXloc() {
	return _xloc;
}

// Return Y location
float Camera::getYloc() {
	return _yloc;
}

// Return Z location
float Camera::getZloc() {
	return _zloc;
}

// Return X component of look vector
float Camera::getXrot() {
	return _vec.getX();
}

// Return Y component of look vector
float Camera::getYrot() {
	return _vec.getY();
}

// Return Z component of look vector
float Camera::getZrot() {
	return _vec.getZ();
}

// Move the camera along the direction of its look vector
void Camera::moveForward(float scale) {
	// Add the vector to the current location
	_xloc += _vec.getX()*scale;
	_yloc += _vec.getY()*scale;
	_zloc += _vec.getZ()*scale;
}

// Move the camera along the direction of the apparent relative upward vector
void Camera::moveUp(float scale) {
	// Use the right hand rule to define "right" as the cross product of absolute up and the current
	// look vector. Relative up is then the cross product of relative right and the current look
	// vector.
	Vector absUp(0, 0, 1);
	Vector right = _vec * absUp;
	Vector relUp = right * _vec;
	_xloc += relUp.getX()*scale;
	_yloc += relUp.getY()*scale;
	_zloc += relUp.getZ()*scale;
}

// Move the camera along the direction of the apparent relative rightward vector
void Camera::moveRight(float scale) {
	// Define "right" as the cross product of the current look vector and the absolute up vector.
	Vector absUp(0, 0, 1);
	Vector right = _vec * absUp;
	right = right/right.getMagnitude();
	_xloc += right.getX()*scale;
	_yloc += right.getY()*scale;
	_zloc += right.getZ()*scale;
}

// Rotate the camera "deg" degrees clockwise about the X axis
void Camera::rotateX(float deg) {
	float y = _vec.getY(), z = _vec.getZ();
	_vec.setY( y*cos(deg) - z*sin(deg) );
	_vec.setZ( y*sin(deg) + z*cos(deg) );

	_vec = _vec/_vec.getMagnitude();
}

// Rotate the camera "deg" degrees clockwise about the Y axis
void Camera::rotateY(float deg) {
	float x = _vec.getX(), z = _vec.getZ();
	_vec.setZ( z*cos(deg) - x*sin(deg) );
	_vec.setX( z*sin(deg) + x*cos(deg) );

	_vec = _vec/_vec.getMagnitude();
}

// Rotate the camera "deg" degrees clockwise about the Z axis
void Camera::rotateZ(float deg) {
	float x = _vec.getX(), y = _vec.getY();
	_vec.setX( x*cos(deg) - y*sin(deg) );
	_vec.setY( x*sin(deg) + y*cos(deg) );

	_vec = _vec/_vec.getMagnitude();
}

// Rotate the camera around its local relative axes to achieve proper up/down rotation
void Camera::rotateUp(float deg) {
	Vector relZ = Vector(0.0f, 0.0f, 1.0f);
	Vector relY = _vec;
	Vector relX = relZ * relY;
	relX.normalize();

	float x = _vec.getX(), y = _vec.getY(), z = _vec.getZ(), u = relX.getX(), v = relX.getY(), w = relX.getZ(),
		ux = u*x, uy = u*y, uz = u*z, vx = v*x, vy = v*y, vz = v*z, wx = w*x, wy = w*y, wz = w*z;
	
	float newX = cos(deg)*u*(ux + vy + wz) + (x*(v*v + w*w) - u*(vy + wz)) + sin(deg)*(-wy + vz);
	float newY = cos(deg)*v*(ux + vy + wz) + (y*(u*u + w*w) - v*(ux + wz)) + sin(deg)*(wx - uz);
	float newZ = cos(deg)*w*(ux + vy + wz) + (z*(u*u + v*v) - w*(ux + vy)) + sin(deg)*(-vx + uy);

	_vec = Vector(newX, newY, newZ);
	_vec.normalize();
}
