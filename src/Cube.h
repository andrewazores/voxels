#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <cfloat>
#include "math.h"

#include "Material.h"
#include "Plane.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"

class Cube {
public:
	Cube(void);
	Cube(Point, Material);
	Cube(const Cube&);
	~Cube(void);
	void setOrigin(Point);
	void setMaterial(Material);
	void setMovementVector(Vector);
	Point getOrigin(void);
	Material getMaterial(void);
	Vector getMovementVector();
	Point rayIntersection(Ray);
private:
	Point _origin;
	Material _mat;
	Vector _movement;
};

#endif
