#include "Cube.h"
#include "Utils.h"

// Constructor for an uninitialized cube
Cube::Cube() {
	_origin = Point();
	_mat = Material();
	_movement = Vector();
}

// Construct a cube given its centre and material
Cube::Cube(Point p, Material mat) {
	_origin = p;
	_movement = Vector();
	_mat = mat;
}

// Destructor
Cube::~Cube() { }

// Copy constructor
Cube::Cube(const Cube &c) {
	_origin = c._origin;
	_mat = c._mat;
	_movement = c._movement;
}

// Set the centre point of this cube
void Cube::setOrigin(Point p) {
	_origin = p;
}

// Set the material of this cube
void Cube::setMaterial(Material mat) {
	_mat = mat;
}

// Set the movement vector of this cube
void Cube::setMovementVector(Vector v) {
	_movement = v;
}

// Get the origin point of this cube
Point Cube::getOrigin() {
	return _origin;
}

// Get the material of this cube
Material Cube::getMaterial() {
	return _mat;
}

// Get the movement vector of this cube
Vector Cube::getMovementVector() {
	return _movement;
}

// Test if the given ray intersects with this cube
Point Cube::rayIntersection(Ray r) {
	Point R0 = r.getOrigin();
	Vector Rd = r.getDirection();

	// x = R0.x + t * Rd.x
	std::vector<Point> pointList;

	float xMin = _origin.getX() - 0.5f, xMax = _origin.getX() + 0.5f, yMin = _origin.getY() - 0.5f, yMax = _origin.getY() + 0.5f, zMin = _origin.getZ() - 0.5f, zMax = _origin.getZ() + 0.5f;

	// Top face
	float tTop = (zMax - R0.getZ()) / Rd.getZ();
	float xTop = R0.getX() + tTop * Rd.getX();
	float yTop = R0.getY() + tTop * Rd.getY();
	if ((xMin <= xTop && xTop <= xMax) && (yMin <= yTop && yTop <= yMax)) {
		pointList.push_back(Point(_origin.getX(), _origin.getY(), zMax + 0.5f));
	}

	// Bottom face
	float tBottom = (zMin - R0.getZ()) / Rd.getZ();
	float xBottom = R0.getX() + tBottom * Rd.getX();
	float yBottom = R0.getY() + tBottom * Rd.getY();
	if ((xMin <= xBottom && xBottom <= xMax) && (yMin <= yBottom && yBottom <= yMax)) {
		pointList.push_back(Point(_origin.getX(), _origin.getY(), zMin - 0.5f));
	}

	// Near face
	float tNear = (xMin - R0.getX()) / Rd.getX();
	float zNear= R0.getZ() + tNear * Rd.getZ();
	float yNear= R0.getY() + tNear * Rd.getY();
	if ((zMin <= zNear && zNear <= zMax) && (yMin <= yNear && yNear<= yMax)) {
		pointList.push_back(Point(xMin - 0.5f, _origin.getY(), _origin.getZ()));
	}

	// Far face
	float tFar = (xMax - R0.getX()) / Rd.getX();
	float zFar= R0.getZ() + tFar * Rd.getZ();
	float yFar= R0.getY() + tFar * Rd.getY();
	if ((zMin <= zFar && zFar <= zMax) && (yMin <= yFar && yFar <= yMax)) {
		pointList.push_back(Point(xMax + 0.5f, _origin.getY(), _origin.getZ()));
	}

	// Left face
	float tLeft = (yMin - R0.getY()) / Rd.getY();
	float zLeft = R0.getZ() + tLeft * Rd.getZ();
	float xLeft = R0.getX() + tLeft * Rd.getX();
	if ((zMin <= zLeft && zLeft <= zMax) && (xMin <= xLeft && xLeft <= xMax)) {
		pointList.push_back(Point(_origin.getX(), yMin - 0.5f, _origin.getZ()));
	}

	// Right face
	float tRight = (yMax - R0.getY()) / Rd.getY();
	float zRight = R0.getZ() + tRight * Rd.getZ();
	float xRight = R0.getX() + tRight * Rd.getX();
	if ((zMin <= zRight && zRight <= zMax) && (xMin <= xRight && xRight <= xMax)) {
		pointList.push_back(Point(_origin.getX(), yMax + 0.5f, _origin.getZ()));
	}

	float minDist = FLT_MAX;
	Point closestPoint;
	std::vector<Point>::iterator it;
	for (it = pointList.begin(); it != pointList.end(); it++) {
		float dist = Utils::pointDistance((*it), R0);
		if (dist < minDist) {
			minDist = dist;
			closestPoint = *it;
		}
	}

	return closestPoint;
}
