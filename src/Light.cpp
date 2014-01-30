#include "Light.h"

// Constructor for an uninitialized Light
Light::Light() {
	_identity = 0;
	_origin = Point();
	_ambient = LightColour();
	_diffuse = LightColour();
	_specular = LightColour();

	_enableAmb = false; _enableDiff = false; _enableSpec = false;
}

// Constructor for a light given its location and colour components
Light::Light(int identity, Point origin, LightColour ambient, LightColour diffuse, LightColour specular) {
	_identity = identity;
	_origin = origin;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;

	_enableAmb = false; _enableDiff = false; _enableSpec = false;
}

// Copy constructor
Light::Light(const Light &b) {
	_identity = b._identity;
	_origin = b._origin;
	_ambient = b._ambient;
	_diffuse = b._diffuse;
	_specular = b._specular;

	_enableAmb = b._enableAmb;
	_enableDiff = b._enableDiff;
	_enableSpec = b._enableSpec;
}

// Destructor
Light::~Light() { }

// Set the identity of this light
void Light::setIdentity(int identity) {
	_identity = identity;
}

// Set the location of this light
void Light::setOrigin(Point origin) {
	_origin = origin;
}

// Set the ambient colour of this light
void Light::setAmbient(LightColour ambient) {
	_ambient = ambient;
}

// Set the diffuse colour of this light
void Light::setDiffuse(LightColour diffuse) {
	_diffuse = diffuse;
}

// Set the specular colour of this light
void Light::setSpecular(LightColour specular) {
	_specular = specular;
}

// Move the light a distance dx in the x direction
void Light::moveX(float dx) {
	_origin.setX(_origin.getX() + dx);
}

// Move the light a distance dy in the y direction
void Light::moveY(float dy) {
	_origin.setY(_origin.getY() + dy);
}

// Move the light a distance dz in the z direction
void Light::moveZ(float dz) {
	_origin.setZ(_origin.getZ() + dz);
}

// Get the identity of the light
int Light::getIdentity() {
	return _identity;
}

// Get the location of the light
Point Light::getOrigin() {
	return _origin;
}

// Get the ambient colour of the light
LightColour Light::getAmbient() {
	return _ambient;
}

// Get the diffuse colour of the light
LightColour Light::getDiffuse() {
	return _diffuse;
}

// Get the specular colour of the light
LightColour Light::getSpecular() {
	return _specular;
}

// Update the light colour and position
void Light::update() {
	float point[3] = {_origin.getX(), _origin.getY(), _origin.getZ()};
	float ambient[4] = {_ambient.getRedChannel(), _ambient.getGreenChannel(), _ambient.getBlueChannel(), _ambient.getAlphaChannel()};
	float diffuse[4] = {_diffuse.getRedChannel(), _diffuse.getGreenChannel(), _diffuse.getBlueChannel(), _diffuse.getAlphaChannel()};
	float specular[4] = {_specular.getRedChannel(), _specular.getGreenChannel(), _specular.getBlueChannel(), _specular.getAlphaChannel()};

	glLightfv(_identity, GL_POSITION, point);
	if (_enableAmb) glLightfv(_identity, GL_AMBIENT, ambient);
	if (_enableDiff) glLightfv(_identity, GL_DIFFUSE, diffuse);
	if (_enableSpec) glLightfv(_identity, GL_SPECULAR, specular);
}

// Check if a component of the light is enabled or disabled
bool Light::getComponentState(int component) {
	switch(component) {
		case GL_AMBIENT: return _enableAmb;
		case GL_DIFFUSE: return _enableDiff;
		case GL_SPECULAR: return _enableSpec;
		default: return false;
	}
}

// Enable or disable components of the light
void Light::enableComponent(int component, bool state) {
	switch(component) {
		case GL_AMBIENT: _enableAmb = state; break;
		case GL_DIFFUSE: _enableDiff = state; break;
		case GL_SPECULAR: _enableSpec = state; break;
	}
}
