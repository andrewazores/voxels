#include "Mouse.h"

// Constructor for an uninitialized mouse
Mouse::Mouse() {
	_x = 0;
	_y = 0;
}

// Copy constructor
Mouse::Mouse(const Mouse &b) {
	_x = b._x;
	_y = b._y;
}

// Constructor for a mouse given its x and y coordinates
Mouse::Mouse(int x, int y) {
	_x = x;
	_y = y;
}

// Set the X coordinate of the mouse
void Mouse::setX(int x ) {
	_x = x;
}

// Set the Y coordinate of the mouse
void Mouse::setY(int y) {
	_y = y;
}

// Set the left button state
void Mouse::setLeft(bool left) {
	_left = left;
}

// Set the right button state
void Mouse::setRight(bool right) {
	_right = right;
}

// Set the coordinates of the mouse at the same time for convenience
void Mouse::setCoordinates(int x, int y) {
	_x = x;
	_y = y;
}

// Return a vector for use in unprojecting the mouse location into 3D world coordinates
Vector Mouse::getVector() {
	GLdouble modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	GLdouble projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	int realY = viewport[3] - _y + 1;

	GLdouble nearX, nearY, nearZ, farX, farY, farZ;
	gluUnProject(_x, realY, 0.0f, modelview, projection, viewport, &nearX, &nearY, &nearZ);
	gluUnProject(_x, realY, 1.0f, modelview, projection, viewport, &farX, &farY, &farZ);

	return Vector(farX - nearX, farY - nearY, farZ - nearZ);
}

// Return the X coordinate of the mouse
int Mouse::getX() {
	return _x;
}

// Return the Y coordinate of the mouse
int Mouse::getY() {
	return _y;
}

// Return the left button state of the mouse
bool Mouse::getLeft() {
	return _left;
}

// Return the right button state of the mouse
bool Mouse::getRight() {
	return _right;
}
