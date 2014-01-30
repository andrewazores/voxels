#ifndef MOUSE_H
#define MOUSE_H

#include <GL/glut.h>
#include <GL/gl.h>

#include "Point.h"
#include "Ray.h"

class Mouse {
public:
	Mouse(void);
	Mouse(const Mouse&);
	Mouse(int, int);
	void setX(int);
	void setY(int);
	void setCoordinates(int, int);
	void setLeft(bool);
	void setRight(bool);
	Vector getVector(void);
	int getX(void);
	int getY(void);
	bool getLeft(void);
	bool getRight(void);
private:
	int _x, _y;
	bool _left, _right;
};

#endif