#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <list>
#include "math_3d.h"
#include "settings.h"

class Control
{
public:
	int windowWidth, windowHeight;
	int mouseX, mouseY;
	int currentTime, deltaTime, newTime, fpsTime, frames;
	bool keys[256];
	bool mouse[6];
	float zoom;
	Matrix4f transform;
	Settings settings;
};

#endif