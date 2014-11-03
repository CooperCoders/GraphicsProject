
#include "particle.h"
#include <iostream>

Particle::Particle()
{
	X = Vector3f(0, 0, 0);
	V = Vector3f(rand() / (float)RAND_MAX - .5, rand() / (float)RAND_MAX - .5, 0);
	A = Vector3f(0, -1, 0);
	P = Vertex(X, Vector4f(.9, 0, 0, rand() / (float)RAND_MAX));
}

Particle::Particle(Vector3f x, Vector4f c)
{
	X = x;
	V = Vector3f(0, 0, 0);
	A = Vector3f(0, 0, 0);
	P = Vertex(X, c);
}

void Particle::Step(bool* k, int* m, int _x, int _y, int dt)
{
	V += A * (dt / 1000.0f);
	X += V * (dt / 1000.0f);
	V *= .999;
	
	P.X = X;
	if (X.y < -1)
	{
		V.y *= -.99;
		X.y = -.999;
	}
	if (X.x < -1)
	{
		V.x *= -1;
		X.x = -.999;
	}
	if (X.x > 1)
	{
		V.x *= -1;
		X.x = .999;
	}
	if (!m[0])
	{
		A = Vector3f((_x - 320) / 320.0f, (_y - 320) / -320.0f, 0) - X;
		A *= 1 / (sqrt(A.x * A.x + A.y * A.y));
	}
	else
	{
		A = Vector3f(0, -1, 0);
	}
}

void Particle::Draw(Vertex* buf, int& count)
{
	buf[count++] = P;
}
