#ifndef UTILS_H
#define UTILS_H

#ifndef __FLT_MAX__
#define __FLT_MAX__ 1e+37
#endif

#include <cmath>
#include <stdlib.h>
#include <string>

#include <math.h>
#include "Point.h"

class Utils {
public:
	static float randomFloat(float, float);
	static int randomInt(int, int);
	static std::string getHelpMessage();
	static float pointDistance(Point, Point);
};

#endif
