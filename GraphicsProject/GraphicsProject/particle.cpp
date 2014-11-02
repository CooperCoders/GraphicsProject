
#include "particle.h"
#include <iostream>

Particle::Particle()
{
	X = Vector3f(Rand1(), Rand1(), 0)*.5;
	V = Vector3f(-X.y, X.x, 0) * 2 * round(Rand1() - .1);
	A = Vector3f(0, 0, 0);
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
	A = X * -1 * (1 / sqrt(X.x * X.x + X.y * X.y)) * (1 / sqrt(X.x * X.x + X.y * X.y)) * (1 / sqrt(X.x * X.x + X.y * X.y)) * .25;
	if (X.x > .5)
	{
		X = Vector3f(Rand1(), Rand1(), 0)*.5;
		V = Vector3f(-X.y, X.x, 0) * 2 * round(Rand1() - .1);
	}
	if (X.x < -.5)
	{
		X = Vector3f(Rand1(), Rand1(), 0)*.5;
		V = Vector3f(-X.y, X.x, 0) * 2 * round(Rand1() - .1);
	}
	if (X.y > .5)
	{
		X = Vector3f(Rand1(), Rand1(), 0)*.5;
		V = Vector3f(-X.y, X.x, 0) * 2 * round(Rand1() - .1);
	}
	if (X.y < -.5)
	{
		X = Vector3f(Rand1(), Rand1(), 0)*.5;
		V = Vector3f(-X.y, X.x, 0) * 2 * round(Rand1() - .1);
	}
}

void Particle::Draw(Vertex* buf, int& count)
{
	buf[count++] = P;
}

float Particle::Rand1()
{
	float r = rand() / (float)RAND_MAX;
	r = (r - .5) * 2;
	return r;
}