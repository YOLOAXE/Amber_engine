#ifndef __ENGINE_VECTOR_2__
#define __ENGINE_VECTOR_2__

class Vector2
{

public:
	Vector2(float vx, float vy);
	Vector2(float xy);
	Vector2();
	Vector2 operator*(const Vector2& v);
	Vector2 operator*(const float& f);
	Vector2 operator+(const Vector2& v);
	Vector2 operator+(const float& f);
	Vector2 operator-(const Vector2& v);
	Vector2 operator-(const float& f);
public:
	float x = 0;
	float y = 0;
};

#endif// !__ENGINE_VECTOR_2__