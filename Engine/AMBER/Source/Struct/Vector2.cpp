#include "Vector2.hpp"

Vector2::Vector2(float vx, float vy)
{
	x = vx;
	y = vy;
}

Vector2::Vector2(float xy)
{
	x = xy;
	y = xy;
}

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2 Vector2::operator*(const Vector2 & v)
{
	Vector2 mult;
	mult.x = this->x * v.x;
	mult.y = this->y * v.y;
	return mult;
}

Vector2 Vector2::operator*(const float & f)
{
	Vector2 mult;
	mult.x = this->x * f;
	mult.y = this->y * f;
	return mult;
}

Vector2 Vector2::operator+(const Vector2 & v)
{
	Vector2 add;
	add.x = this->x + v.x;
	add.y = this->y + v.y;
	return add;
}

Vector2 Vector2::operator+(const float & f)
{
	Vector2 add;
	add.x = this->x + f;
	add.y = this->y + f;
	return add;
}

Vector2 Vector2::operator-(const Vector2 & v)
{
	Vector2 add;
	add.x = this->x - v.x;
	add.y = this->y - v.y;
	return add;
}

Vector2 Vector2::operator-(const float & f)
{
	Vector2 add;
	add.x = this->x - f;
	add.y = this->y - f;
	return add;
}

