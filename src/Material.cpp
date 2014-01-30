#include "Material.h"

// Constructor for an unitialized material
Material::Material() {
	_r = 0.0f;
	_g = 0.0f;
	_b = 0.0f;
	_a = 0.0f;
}

// Set the RGBA value for the material
Material::Material(float r, float g, float b, float a) {
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}

// Destructor
Material::~Material() { };

// Set the red channel value for this material
void Material::setR(float r) {
	_r = r;
}

// Set the green channel value for this material
void Material::setG(float g) {
	_g = g;
}

// Set the blue channel value for this material
void Material::setB(float b) {
	_b = b;
}

// Set the alpha channel value for this material
void Material::setA(float a) {
	_a = a;
}

// Get the red channel value for this material
float Material::getR() {
	return _r;
}

// Get the green channel value for this material
float Material::getG() {
	return _g;
}

// Get the blue channel value for this material
float Material::getB() {
	return _b;
}

// Get the alpha channel value for this material
float Material::getA() {
	return _a;
}
