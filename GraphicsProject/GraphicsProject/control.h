#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <list>
#include "math_3d.h"
#include "settings.h"

class Control
{
public:
	int WindowWidth, WindowHeight;
	int MouseX, MouseY;
	int CurrentTime, DeltaTime, NewTime, FpsTime, Frames;
	bool Keys[256];
	int Mouse[6];
	float Zoom;
	Matrix4f Transform;
	Settings CurrentSettings = Settings("settings.xml");
};

#endif