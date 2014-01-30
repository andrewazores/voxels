#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glut.h>
#include <GL/gl.h>

#include "LightColour.h"
#include "Point.h"

class Light {
public:
	Light(void);
	Light(int, Point, LightColour, LightColour, LightColour);
	Light(const Light&);
	~Light();
	void setIdentity(int);
	void setOrigin(Point);
	void setAmbient(LightColour);
	void setDiffuse(LightColour);
	void setSpecular(LightColour);
	void moveX(float);
	void moveY(float);
	void moveZ(float);
	int getIdentity(void);
	Point getOrigin(void);
	LightColour getAmbient(void);
	LightColour getDiffuse(void);
	LightColour getSpecular(void);
	void update(void);
	bool getComponentState(int);
	void enableComponent(int, bool);
private:
	int _identity;
	Point _origin;
	LightColour _ambient, _diffuse, _specular;
	bool _enableAmb, _enableDiff, _enableSpec;
};

#endif