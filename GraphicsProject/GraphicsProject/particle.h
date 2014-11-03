#ifndef PARTICLE_H
#define PARTICLE_H

#include "vertex.h"

class Particle
{
public:
	Vertex P;
	Vector3f X, V, A;
	void Draw(Vertex*, int&);
	void Step(bool *k, int* m, int _x, int _y, int dt);
	int ColorSpeed;
	float ColorAngle;
	Particle(Vector3f, Vector4f);
	Particle();
	Vector4f GetColor(float, float);
};

#endif