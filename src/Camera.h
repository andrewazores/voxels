#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include "Vector.h"

class Camera {
public:
	Camera();
	Camera(float, float, float, Vector);
	~Camera();
	void moveForward(float);
	void moveUp(float);
	void moveRight(float);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);
	void rotateUp(float);
	void setVector(Vector);
	void setXLoc(float);
	void setYLoc(float);
	void setZLoc(float);
	float getXloc();
	float getYloc();
	float getZloc();
	float getXrot();
	float getYrot();
	float getZrot();
	void update();
private:
	float _xloc, _yloc, _zloc;
	Vector _vec;
};

#endif
