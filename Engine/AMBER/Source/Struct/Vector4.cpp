#include "Vector4.hpp"

Vector4::Vector4(float vx, float vy, float vz, float vw)
{
	x = vx;
	y = vy;
	z = vz;
	w = vw;
}

Vector4::Vector4(float xyzw)
{
	x = xyzw;
	y = xyzw;
	z = xyzw;
	w = xyzw;
}

Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}
