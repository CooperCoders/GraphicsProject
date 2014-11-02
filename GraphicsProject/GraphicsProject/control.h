#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <list>
#include "math_3d.h"


class Control
{
public:
	int windowWidth, windowHeight;
	int mouseX, mouseY;
	int currentTime, deltaTime, newTime, fpsTime, frames;
	bool keys[256];
	float zoom;
	Matrix4f transform;
};

#endif