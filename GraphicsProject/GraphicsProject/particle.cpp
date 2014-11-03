
#include "particle.h"
#include <iostream>

Particle::Particle()
{
	X = Vector3f(0, 0, 0);
	V = Vector3f(rand() / (float)RAND_MAX - .5, rand() / (float)RAND_MAX - .5, 0);
	A = Vector3f(0, -1, 0);
	P = Vertex(X, Vector4f(.9, 0, 0, rand() / (float)RAND_MAX));
	ColorSpeed = 30;
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
	V *= .99;
	ColorAngle += ColorSpeed * (dt / 1000.0f);
	
	P.X = X;
	P.Color = GetColor(ColorAngle, 1.0f);
	if (X.y < -1)
	{
		V.y *= -.99;
		X.y = -.999;
	}
	if (X.y > 1)
	{
		V.y *= -.99;
		X.y = .999;
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
		A *= 10 / (sqrt(A.x * A.x + A.y * A.y));
	}
	else
	{
		A = Vector3f(0, -.2, 0);
	}
}

void Particle::Draw(Vertex* buf, int& count)
{
	buf[count++] = P;
}

Vector4f Particle::GetColor(float angle, float alpha)
{
	float R, G, B;
	float H = angle;
	float S = 1;
	float V = 1;
	float C = V * S;
	float Hp = H / 60;
	float X = C*(1 - fabs((fmod(Hp, 2)) - 1));
	if (Hp < 1)
	{
		R = C; G = X; B = 0;
	}
	else if (Hp < 2)
	{
		R = X; G = C; B = 0;
	}
	else if (Hp < 3)
	{
		R = 0; G = C; B = X;
	}
	else if (Hp < 4)
	{
		R = 0; G = X; B = C;
	}
	else if (Hp < 5)
	{
		R = X; G = 0; B = C;
	}
	else
	{
		R = C; G = 0; B = X;
	}
	float m = V - C;
	R += m;
	G += m;
	B += m;
	return Vector4f(R, G, B, alpha);
}