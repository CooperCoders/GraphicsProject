
#include "particle.h"
#include <iostream>

Particle::Particle()
{
	X = Vector3f(rand() / (float)RAND_MAX, 0, 0);
	V = Vector3f(0, 0, 0);
	A = Vector3f(0, -1, 0);
	P = Vertex(X, Vector4f(1, 0, 0, 1));
}

Particle::Particle(Vector3f x, Vector4f c)
{
	X = x;
	V = Vector3f(0, 0, 0);
	A = Vector3f(0, 0, 0);
	P = Vertex(X, c);
}

void Particle::Step(bool* k, int dt)
{
	V += A * (dt / 1000.0f);
	X += V * (dt / 1000.0f);
	P.X = X;
}

void Particle::Draw(Vertex* buf, int& count)
{
	buf[count++] = P;
}
