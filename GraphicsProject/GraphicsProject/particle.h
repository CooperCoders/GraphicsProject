#ifndef PARTICLE_H
#define PARTICLE_H

#include "vertex.h"

class Particle
{
public:
	Vertex P;
	Vector3f X, V, A;
	void Draw(Vertex*, int&);
	void Step(bool *k, int dt);
	Particle(Vector3f, Vector4f);
	Particle();
};

#endif