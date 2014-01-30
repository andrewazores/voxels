#include <string>
#include "Utils.h"

// Return a pseudorandom float within the specified range
float Utils::randomFloat(float min, float max) {
    if (min > max) {
		float tmp = min;
		min = max;
		max = tmp;
	}
    float random = ((float) rand()) / (float) RAND_MAX;

    float range = max - min;  
    return (random*range) + min;
}

// Return a pseudorandom integer within the specified range
int Utils::randomInt(int min, int max) {
	if (min > max) {
		int tmp = min;
		min = max;
		max = tmp;
	}
	double scale = (double)rand()/RAND_MAX;
    return (max - min)*int(scale)+ min;
}

// Return a handy dandy help message
std::string Utils::getHelpMessage() {
	std::string message;

	message += "Andrew Azores\n";
	message += "\tComputer Science 3GC3\n";
	message += "\tR. Teather\n";
	message += "\tAssignment 3\n";
	message += "\nInstructions:\n";
	message += "Use 'w', 'a', 's', and 'd' to move the camera around the scene. Use 'r' and 'f' to change height.\n\n";
	message += "Left click on the ground or on cubes to place more cubes. Right click on cubes to remove them.\n\n";
	message += "Use the 1-5 keys to change the cube colour.\n\n";
	message += "Press 'm' while pointing at an existing cube to change its colour to the colour you have chosen.\n\n";
	message += "Use the 'c' key to clear all the cubes in the scene.\n\n";
	message += "Press 'l' to load a save file and 'L' to save.\n\n";
	message += "Press 'z' to toggle \"snap to grid\" mode.\n\n";
	message += "Press 'e' to make the scene explode!\n\n";
	message += "Press 't' to switch which light source you control.n\n";
	message += "Use 'W', 'A', 'S', 'D', 'R', and 'F' to move the light source around the scene\n\n";
	message += "Try pressing '?'...\n\n";

	return message;
}

// Return the floating point distance between two points in 3D space
float Utils::pointDistance(Point p1, Point p2) {
	float dx = p2.getX() - p1.getX(), dy = p2.getY() - p1.getY(), dz = p2.getZ() - p1.getZ();
	float xs = dx*dx, ys = dy*dy, zs = dz*dz;
	return std::sqrt(xs + ys + zs);
}
