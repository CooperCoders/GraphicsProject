#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include "vertex.h"

class Particle
{
public:
	Vertex P;
	Vector3f X, V, A;
	void Step(bool *k, int dt);
	Particle(Vector3f, Vector4f);
	Particle();
	float Rand1();
};
#endif