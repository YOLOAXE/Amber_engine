#include "Vector3.hpp"

Vector3::Vector3(float vx, float vy, float vz)
{
	x = vx;
	y = vy;
	z = vz;
}

Vector3::Vector3(float xyz)
{
	x = xyz;
	y = xyz;
	z = xyz;
}

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3 Vector3::operator*(const Vector3 & v)
{
	Vector3 mult;
	mult.x = this->x * v.x;
	mult.y = this->y * v.y;
	mult.z = this->z * v.z;
	return mult;
}

Vector3 Vector3::operator*(const float & f)
{
	Vector3 mult;
	mult.x = this->x * f;
	mult.y = this->y * f;
	mult.z = this->z * f;
	return mult;
}

Vector3 Vector3::operator+(const Vector3 & v)
{
	Vector3 add;
	add.x = this->x + v.x;
	add.y = this->y + v.y;
	add.z = this->z + v.z;
	return add;
}

Vector3 Vector3::operator+(const float & f)
{
	Vector3 add;
	add.x = this->x + f;
	add.y = this->y + f;
	add.z = this->z + f;
	return add;
}

Vector3 Vector3::operator-(const Vector3 & v)
{
	Vector3 add;
	add.x = this->x - v.x;
	add.y = this->y - v.y;
	add.z = this->z - v.z;
	return add;
}

Vector3 Vector3::operator-()
{
	Vector3 add;
	add.x = -this->x;
	add.y = -this->y;
	add.z = -this->z;
	return add;
}

Vector3 Vector3::operator-(const float & f)
{
	Vector3 add;
	add.x = this->x - f;
	add.y = this->y - f;
	add.z = this->z - f;
	return add;
}

