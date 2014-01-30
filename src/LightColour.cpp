#include "LightColour.h"

// Constructor for an uninitialized LightColour
LightColour::LightColour() {
	_red = 0.0f;
	_green = 0.0f;
	_blue = 0.0f;
	_alpha = 0.0f;
}

// Constructor for a LightColour given its RGBA components
LightColour::LightColour(float red, float green, float blue, float alpha) {
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha;
}

// Copy constructor
LightColour::LightColour(const LightColour &b) {
	_red = b._red;
	_green = b._green;
	_blue = b._blue;
	_alpha = b._alpha;
}

// Destructor
LightColour::~LightColour() { }

// Set the red channel value of this LightColour
void LightColour::setRedChannel(float red) {
	_red = red;
}

// Set the green channel value of this LightColour
void LightColour::setGreenChannel(float green) {
	_green = green;
}

// Set the blue channel value of this LightColour
void LightColour::setBlueChannel(float blue) {
	_blue = blue;
}

// Set the alpha channel value of this LightColour
void LightColour::setAlphaChannel(float alpha) {
	_alpha = alpha;
}

// Get the red channel value of this LightColour
float LightColour::getRedChannel() {
	return _red;
}

// Get the green channel value of this LightColour
float LightColour::getGreenChannel() {
	return _green;
}

// Get the blue channel value of this LightColour
float LightColour::getBlueChannel() {
	return _blue;
}

// Get the alpha channel value of this LightColour
float LightColour::getAlphaChannel() {
	return _alpha;
}
