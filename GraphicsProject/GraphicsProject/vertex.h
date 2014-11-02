#ifndef VERTEX_H
#define VERTEX_H

#include "math_3d.h"


struct Vertex
{
	Vector3f X;
	Vector4f Color;

	Vertex(Vector3f x, Vector4f c)
	{
		X = x;
		Color = c;
	}
	Vertex()
	{
		X = Vector3f(0, 0, 0);
		Color = Vector4f(0, 0, 0, 1);
	}
};

#endif