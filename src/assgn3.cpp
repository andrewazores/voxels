/* Author: Andrew Azores
*  Course: Computer Science 3GC3
*  McMaster University
*  Assignment 3 - Voxels
*  November 2012
*/

#include <cstring>
#include <fstream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "Camera.h"
#include "Cube.h"
#include "Light.h"
#include "LightColour.h"
#include "Mouse.h"
#include "Plane.h"
#include "Point.h"
#include "Ray.h"
#include "Utils.h"
#include "Vector.h"

#define K_WINDOW_WIDTH_DEFAULT 1024
#define K_WINDOW_HEIGHT_DEFAULT 768

bool checkCubeExistence(Point);
void display();
void displayCallback(int);
void explode();
void handleKeyboard();
void handleMouseClick();
void keyboard(unsigned char, int, int);
void keyboardUp(unsigned char, int, int);
void loadCubeFile();
void mouse(int, int, int, int);
float pointDistance(Point, Point);
void quit();
void removeCubeFromList();
void renderCube(Cube);
void renderScene();
void reshape(int, int);
void restoreOrder();
int roundToNearest(float, int);
void saveCubeFile();
void specialKeys(int, int, int);
void specialKeysUp(int, int, int);

bool mSnapToGrid = true, mExploding = false, mRidiculousMode = false;
bool keyboardStates[246];
bool specialKeyStates[4];
int kWindowWidth = K_WINDOW_WIDTH_DEFAULT, kWindowHeight = K_WINDOW_HEIGHT_DEFAULT, mWindowId, mActiveLight;
Camera mCamera;
Light mLights[2];
Material mMaterial = Material(0.3f, 0.3f, 0.3f, 1.0f);
Mouse mMouse;
Plane mTerrain;
std::vector<Cube> mCubeList;

float kLightSphereMaterial[4] = {1.0f, 1.0f, 0.2f, 1.0f};
float kTerrainMaterial[4] = {0.0f, 0.2f, 0.043, 1.0f};

// Check if a cube already exists with the specified origin
bool checkCubeExistence(Point P) {
	// Iterate over all the cubes in the cube list and check their origin point. If it is the same point as the
	// specified point, return true to signify that this cube does already exist. This only works when snap to grid
	// mode is enabled.
	for (std::vector<Cube>::iterator it = mCubeList.begin(); it != mCubeList.end(); it++) {
		if ((*it).getOrigin() == P) {
			return true;
		}
	}

	return false;
}

// Display at about 25FPS if possible
void display() {
	renderScene();
	handleKeyboard();

	glutTimerFunc(int(1000/25), displayCallback, 0);
}

// Timer callback wrapper for display
void displayCallback(int unused) {
	glutPostRedisplay();
}

// Initialize an explosion vector for each cube
void explode() {
	std::cout << "Exploding!!" << std::endl << std::endl;
	// Iterate over the list of cubes and assign a pseudorandom movement vector to each cube.
	for (std::vector<Cube>::iterator it = mCubeList.begin(); it != mCubeList.end(); it++) {
		float x = Utils::randomFloat(-2.0f, 2.0f), y = Utils::randomFloat(-2.0f, 2.0f), z = Utils::randomFloat(0.0f, 2.0f);
		Vector movement = Vector(x, y, z);
		(*it).setMovementVector(movement);
	}
}

// Handle key presses
void handleKeyboard() {
	// Camera movement
	if (keyboardStates[int('q')] || keyboardStates[int('Q')]) quit(); 
	if (keyboardStates[int('w')]) mCamera.moveForward(0.7f); 
	if (keyboardStates[int('s')]) mCamera.moveForward(-0.7f);
	if (keyboardStates[int('d')]) mCamera.moveRight(0.7f); 
	if (keyboardStates[int('a')]) mCamera.moveRight(-0.7f); 
	if (keyboardStates[int('r')]) mCamera.moveUp(0.7f); 
	if (keyboardStates[int('f')]) mCamera.moveUp(-0.7f); 

	// Misc
	if (keyboardStates[int('c')] || keyboardStates[int('C')]) mCubeList.clear(); 
	if (keyboardStates[int('Z')] || keyboardStates[int('Z')]) mSnapToGrid = !mSnapToGrid; 
	if (keyboardStates[int('?')]) mRidiculousMode = !mRidiculousMode; 
	if (keyboardStates[int('t')] || keyboardStates[int('t')]) mActiveLight = (mActiveLight == 0) ? 1 : 0; 

	// Change cube colours
	if (keyboardStates[int('1')]) mMaterial = Material(1.0f, 0.0f, 0.0f, 1.0f); 
	if (keyboardStates[int('2')]) mMaterial = Material(0.0f, 1.0f, 0.0f, 1.0f); 
	if (keyboardStates[int('3')]) mMaterial = Material(0.0f, 0.0f, 1.0f, 1.0f); 
	if (keyboardStates[int('4')]) mMaterial = Material(0.3f, 0.3f, 0.3f, 1.0f); 
	if (keyboardStates[int('5')]) mMaterial = Material(0.05f, 0.05f, 0.05f, 1.0f); 

	// Save/load
	if (keyboardStates[int('l')]) loadCubeFile();
	if (keyboardStates[int('L')]) saveCubeFile();

	// Light source movement
	if (keyboardStates[int('D')]) mLights[mActiveLight].moveX(0.7f); 
	if (keyboardStates[int('A')]) mLights[mActiveLight].moveX(-0.7f);
	if (keyboardStates[int('S')]) mLights[mActiveLight].moveY(-0.7f);
	if (keyboardStates[int('W')]) mLights[mActiveLight].moveY(0.7f); 
	if (keyboardStates[int('R')]) mLights[mActiveLight].moveZ(0.7f); 
	if (keyboardStates[int('F')]) mLights[mActiveLight].moveZ(-0.7f);

	if (specialKeyStates[0]) mCamera.rotateZ(0.03f);
	if (specialKeyStates[1]) mCamera.rotateZ(-0.03f);
	if (specialKeyStates[2]) mCamera.rotateUp(-0.03f);
	if (specialKeyStates[3]) mCamera.rotateUp(0.03f);
}

// Handle mouse and 'm' key presses
void handleMouseClick() {
	Vector R = mMouse.getVector();
	Point origin = Point(mCamera.getXloc(), mCamera.getYloc(), mCamera.getZloc());
	Ray ray = Ray(origin, R);

	// Test and handle cube intersection
	std::vector<Point> pointList;
	for (std::vector<Cube>::iterator it = mCubeList.begin(); it != mCubeList.end(); it++) {
		Point intersectionPoint = (*it).rayIntersection(ray);
		if (intersectionPoint != Point()) {
			pointList.push_back(intersectionPoint);
		}
	}

	// If we intersected with any cubes...
	if (pointList.size() != 0) {
		float minDist = FLT_MAX;
		Point closestPoint;
		// Find the closest intersection
		for (std::vector<Point>::iterator i = pointList.begin(); i != pointList.end(); i++) {
			float dist = Utils::pointDistance(*i, origin);
			if (dist < minDist) {
				minDist = dist;
				closestPoint = *i;
			}
		}

		// If we left clicked on that intersection, put a new cube there
		if (mMouse.getLeft()) {
			bool locationTaken = checkCubeExistence(closestPoint);
			if (!locationTaken &&
				0.5f < closestPoint.getX() && closestPoint.getX() < 99.5f &&
				0.5f < closestPoint.getY() && closestPoint.getY() < 99.5f) {
				mCubeList.push_back(Cube(closestPoint, mMaterial));
			}
			return;
		}
		// Or, if we right clicked, remove the cube we clicked on
		if (mMouse.getRight()) {
			for (std::vector<Cube>::iterator it = mCubeList.begin(); it != mCubeList.end(); it++) {
				float dist = Utils::pointDistance((*it).getOrigin(), closestPoint);
				if (dist <= 1.0f && (*it).rayIntersection(ray) != Point()) {
					mCubeList.erase(it);
					break;
				}
			}
			return;
		}
		// If we pressed the 'm' key, change the colour of the cube we clicked on to the current global "new cube colour"
		if (keyboardStates[int('m')]) {
			for (std::vector<Cube>::iterator it = mCubeList.begin(); it != mCubeList.end(); it++) {
				float dist = Utils::pointDistance((*it).getOrigin(), closestPoint);
				if (dist <= 1.0f && (*it).rayIntersection(ray) != Point()) {
					(*it).setMaterial(mMaterial);
					break;
				}
			}
			return;
		}
	} else {
		// Test and handle terrain intersection if no cubes were intersected so we can put a cube there
		if (mMouse.getLeft()) {
			Point P = mTerrain.rayIntersection(ray);
			if (P.getX() < 99.5f && P.getX() > 0.5f && P.getY() < 99.5f && P.getY() > 0.5f) {
				if (mSnapToGrid) {
					float nearestX = float(roundToNearest(P.getX(), 1));
					float nearestY = float(roundToNearest(P.getY(), 1));
					float nearestZ = float(roundToNearest(P.getZ(), 1));
					P = Point(nearestX, nearestY, nearestZ);
				}
				P.setZ(P.getZ() + 0.5f);
				mCubeList.push_back(Cube(P, mMaterial));
			}
		}
	}
}

// Handle keyboard presses
void keyboard(unsigned char key, int x, int y) {
	if (key == 'e' || key == 'E') {
		mExploding = !mExploding;
		if (mExploding) explode();
		else restoreOrder();
	}

	keyboardStates[int(key)] = true;

	mMouse.setCoordinates(x, y);
	handleMouseClick();
}

// Handle keyboard releases
void keyboardUp(unsigned char key, int x, int y) {
	keyboardStates[int(key)] = false;
}

// Load a .cube savefile
void loadCubeFile() {
	std::string filename;
	std::cout << "Enter the filename to load to (or \"cancel\" to cancel loading): "; std::cin >> filename; std::cout << std::endl; 

	if (filename == "cancel") return;

	filename += ".cube";
	std::cout << "Loading from " << filename << "..." << std::endl;

	mCubeList.clear();

	std::string line, key, val;
	int pos, attrCount = 0;
	float originX = 0.0f, originY = 0.0f, originZ = 0.0f,
				vectorX = 0.0f, vectorY = 0.0f, vectorZ = 0.0f,
				materialR = 0.0f, materialG = 0.0f, materialB = 0.0f, materialA = 0.0f;

	// Parse the file
	std::ifstream saveFile;
	saveFile.open(filename.c_str(), std::ifstream::in);
	if (saveFile.is_open()) {
		while (saveFile.good()) {
			getline(saveFile, line);

			if (line == "\0") break;

			pos = line.find(":");
			key = line.substr(0, pos);
			val = line.substr(pos + 1);

			if (key == "originX") {
				originX = ::atof(val.c_str());
				attrCount++;
			} else if (key == "originY") {
				originY = ::atof(val.c_str());
				attrCount++;
			} else if (key == "originZ") {
				originZ = ::atof(val.c_str());
				attrCount++;
			} else if (key == "vectorX") {
				vectorX = ::atof(val.c_str());
				attrCount++;
			} else if (key == "vectorY") {
				vectorY = ::atof(val.c_str());
				attrCount++;
			} else if (key == "vectorZ") {
				vectorZ = ::atof(val.c_str());
				attrCount++;
			} else if (key == "materialR") {
				materialR = ::atof(val.c_str());
				attrCount++;
			} else if (key == "materialG") {
				materialG = ::atof(val.c_str());
				attrCount++;
			} else if (key == "materialB") {
				materialB = ::atof(val.c_str());
				attrCount++;
			} else if (key == "materialA") {
				materialA = ::atof(val.c_str());
				attrCount++;
			}

			// This is a pretty weak check for validity of the save file but it works. If we have enough attributes read
			// to create a cube, create a cube...
			if (attrCount == 10) {
				Material material = Material(materialR, materialG, materialB, materialA);
				Point origin = Point(originX, originY, originZ);
				Cube c = Cube(origin, material);
				c.setMovementVector(Vector(vectorX, vectorY, vectorZ));
				mCubeList.push_back(c);
				attrCount = 0;
			}
		}
		saveFile.close();
	} else {
		std::cout << "Could not open file." << std::endl;
	}

	std::cout << "Done loading." << std::endl;
}

// Mouse callback handler function
void mouse(int button, int state, int x, int y) {
	switch(button) {
		case GLUT_LEFT_BUTTON: mMouse.setLeft(state == 0); break;
		case GLUT_RIGHT_BUTTON: mMouse.setRight(state == 0);; break;
	};
	mMouse.setCoordinates(x, y);
	handleMouseClick();
}

// Quit the program
void quit() {
	glutDestroyWindow(mWindowId);

	exit(0);
}

// Render a given cube
void renderCube(Cube c) {
	glPushMatrix();
		Point origin = c.getOrigin();
		glTranslatef(origin.getX(), origin.getY(), origin.getZ());

		Material mat = c.getMaterial();
		float materialColor[4] = {mat.getR(), mat.getG(), mat.getB(), mat.getA()};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialColor);

		if (!mRidiculousMode) glutSolidCube(1.0f);
		else glutSolidTeapot(0.5f);
	glPopMatrix();
}

// Render/simulate the entire scene
void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, kWindowWidth/kWindowHeight, 0.01f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Make sure we can't go below the terrain.
	if (mCamera.getZloc() < 0.1f) mCamera.setZLoc(0.1f);
	mCamera.update();

	// Update the light positions
	mLights[0].update();
	Point p1 = mLights[0].getOrigin();
	mLights[1].update();
	Point p2 = mLights[1].getOrigin();

	// Render spheres where the light sources are
	
	glPushMatrix();
		glTranslatef(p1.getX(), p1.getY(), p1.getZ());
		glMaterialfv(GL_FRONT, GL_AMBIENT, kLightSphereMaterial);
		glutSolidSphere(1.0f, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(p2.getX(), p2.getY(), p2.getZ());
		glMaterialfv(GL_FRONT, GL_AMBIENT, kLightSphereMaterial);
		glutSolidSphere(1.0f, 10, 10);
	glPopMatrix();
	
	// Render the terrain
    glMaterialfv(GL_FRONT, GL_AMBIENT, kTerrainMaterial);
	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 100.0f, 0.0f);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
	glEnd();

	// Iterate over the cube list
	std::vector<Cube>::iterator it;
	for (it = mCubeList.begin(); it != mCubeList.end(); it++) {
		// Render each cube
		renderCube(*it);
		// If the simulation should be blowing up right now, then do a lot of extra math to move all the cubes around
		if (mExploding) {
			// All of this is arbitrary physics but it looks nice, makes sense, and works...

			// For convenience and to reduce the number of function calls (at the expense of a little memory),
			// assign these commonly used values to new variables with convenient names
			Vector oldVec = (*it).getMovementVector();
			Point origin = (*it).getOrigin();
			float x = origin.getX(), y = origin.getY(), z = origin.getZ();
			float dx = oldVec.getX(), dy = oldVec.getY(), dz = oldVec.getZ();

			// If the cube we are examining is "on the ground," apply a certain amount of "friction."
			// If the cube is not on the ground, apply some "drag," with less magnitude than the friction.
			if (z < 1.5f && dz < 0.1f) {
				dx *= 0.85;
				dy *= 0.85;
			} else {
				dx *= 0.995;
				dy *= 0.995;
			}

			// Simulate air drag in the vertical direction as a function of height (atmospheric density)
			dz *= 1.0f - z/100;

			// Simulate gravity
			dz -= z/1000;
			
			// If the cube is moving slow enough, just stop it from moving
			if (abs(dx) < 0.02) {
				dx = 0.0f;
			}

			// Same as above
			if (abs(dy) < 0.02) {
				dy = 0.0f;
			}

			// If we hit the bounding walls of the "map," reverse direction
			if (0.0f > x || 100.0f < x) {
				dx = -dx;
			}

			// Same as above
			if (0.0f > y || 100.0f < y) {
				dy = -dy;
			}

			// If we hit the ground, bounce
			if (1.0f > z) {
				dz = -0.9*dz;
			}

			// If we are close enough to the ground and moving slowly enough, stop and sit on the ground
			if (z < 1.5f && abs(dz) < 0.2f) {
				z = 0.5f;
				dz = 0.0f;
			}

			// If the cube is moving outside of the bounding walls, bring it back in
			if (x > 100.0f) x = 99.5f;
			if (x < 0.0f) x = 0.5f;

			// Same as above
			if (y > 100.0f) y = 99.5f;
			if (y < 0.0f) y = 0.5f;

			// If the cube is inside the terrain, bring it back up
			if (z < 1.5f) z = 0.5f;

			// Set the new movement vector to the cube
			Vector newVec = Vector(dx, dy, dz);
			(*it).setMovementVector(newVec);

			// Set the new position to the cube
			Point newOrigin = Point(x, y, z) + newVec;
			(*it).setOrigin(newOrigin);
		}
	}

	glFlush();
	glutSwapBuffers();
}

// Handle window reshaping
void reshape(int width, int height) {
	glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, GLdouble (width), 0, GLdouble (height) );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Snap cubes back to grid
void restoreOrder() {
	std::cout << "Stopping explosion and snapping cubes back to grid. This process may take some time. Please wait..." << std::endl;

	// Iterate over the list of cubes
	for (std::vector<Cube>::iterator it = mCubeList.begin(); it != mCubeList.end(); it++) {
		// Get the origin of the cube
		Point origin = (*it).getOrigin();
		// Snap the origin to a grid point
		Point newPoint = Point(roundToNearest(origin.getX(), 1), roundToNearest(origin.getY(), 1), roundToNearest(origin.getZ(), 1) + 0.5f);
		if (checkCubeExistence(newPoint)) {
			// If there's already a cube at that grid point, delete this cube so we don't have two cubes in the same place.
			it = mCubeList.erase(it);
		} else {
			// Otherwise move it to that grid point position
			(*it).setOrigin(newPoint);
		}
	}

	std::cout << "Order restored." << std::endl << std::endl;
}

// Found a floating point number to a nearest integer
int roundToNearest(float a, int b) {
	int remainder = int(a) % b;

	if (remainder > b/2) {
		return (int(a) - remainder + b);
	} else {
		return (int(a) - remainder);
	}
}

// Save the current scene to a .cube file
void saveCubeFile() {
	std::string filename;
	std::cout << "Enter the filename to save to (or \"cancel\" to cancel saving): "; std::cin >> filename; std::cout << std::endl;

	if (filename == "cancel") return;

	filename += ".cube";
	std::cout << "Saving to " << filename << "..." << std::endl;

	std::ofstream saveFile;
	saveFile.open(filename.c_str(), std::ifstream::out);

	if (!saveFile.is_open()) {
		std::cout << "Could not open file." << std::endl;
		return;
	}

	for (std::vector<Cube>::iterator it = mCubeList.begin(); it != mCubeList.end(); it++) {
		// Save origin
			saveFile << "originX:" << (*it).getOrigin().getX() << "\n";
			saveFile << "originY:" << (*it).getOrigin().getY() << "\n";
			saveFile << "originZ:" << (*it).getOrigin().getZ() << "\n";

		// Save movement vector
			saveFile << "vectorX:" << (*it).getMovementVector().getX() << "\n";
			saveFile << "vectorY:" << (*it).getMovementVector().getY() << "\n";
			saveFile << "vectorZ:" << (*it).getMovementVector().getZ() << "\n";

		// Save material
			saveFile << "materialR:" << (*it).getMaterial().getR() << "\n";
			saveFile << "materialG:" << (*it).getMaterial().getG() << "\n";
			saveFile << "materialB:" << (*it).getMaterial().getB() << "\n";
			saveFile << "materialA:" << (*it).getMaterial().getA() << "\n";
	}

	saveFile << std::flush;

	std::cout << "Saved to " << filename << "." << std::endl;
}

// Special keys callback handler
void specialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: specialKeyStates[0] = true; break;
		case GLUT_KEY_RIGHT: specialKeyStates[1] = true; break;
		case GLUT_KEY_UP: specialKeyStates[2] = true; break;
		case GLUT_KEY_DOWN: specialKeyStates[3] = true; break;
	}
}

void specialKeysUp(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: specialKeyStates[0] = false; break;
		case GLUT_KEY_RIGHT: specialKeyStates[1] = false; break;
		case GLUT_KEY_UP: specialKeyStates[2] = false; break;
		case GLUT_KEY_DOWN: specialKeyStates[3] = false; break;
	}
}

int main(int argc, char** argv) {
	std::cout << Utils::getHelpMessage() << std::endl;

	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(kWindowWidth, kWindowHeight);
	glutInitWindowPosition(120, 40);	
	glutInit(&argc, argv);
	mWindowId = glutCreateWindow("MynKreft");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialKeys);
	glutSpecialUpFunc(specialKeysUp);

	glClearColor(0.5f, 0.9f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Vector v = Vector(10.0f, 10.0f, -2.0f);
	v.normalize();
	mCamera = Camera(-10.0f, -10.0f, 5.0f, v);

	mCubeList = std::vector<Cube>();

	Vector N = Vector(0.0f, 0.0f, 1.0f);
	Vector p1 = Vector(100.0f, 0.0f, 0.0f);
	Vector p2 = Vector(0.0f, 100.0f, 0.0f);
	mTerrain = Plane(Point(0.0f, 0.0f, 0.0f), p1, p2, N, 0.0f);

	glEnable(GL_LIGHTING);
	float ambient[4] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	glEnable(GL_LIGHT0);
	LightColour ambientLightOne(1.0f, 1.0f, 1.0f, 1.0f);
	Point positionLightOne = Point(50.0f, 50.0f, 12.0f);
	mLights[0] = Light();
	mLights[0].setIdentity(GL_LIGHT0);
	mLights[0].setAmbient(ambientLightOne);
	mLights[0].setOrigin(positionLightOne);
	mLights[0].enableComponent(GL_AMBIENT, true);
	
	glEnable(GL_LIGHT1);
	LightColour ambientLightTwo(1.0f, 1.0f, 0.2f, 1.0f);
	Point positionLightTwo = Point(0.0f, 0.0f, 6.0f);
	mLights[1] = Light();
	mLights[1].setIdentity(GL_LIGHT1);
	mLights[1].setAmbient(ambientLightTwo);
	mLights[1].setOrigin(positionLightTwo);
	mLights[1].enableComponent(GL_AMBIENT, true);

	glutMainLoop();

	return 0;
}
