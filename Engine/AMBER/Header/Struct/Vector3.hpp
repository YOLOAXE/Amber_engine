#ifndef __ENGINE_VECTOR_3__
#define __ENGINE_VECTOR_3__

class Vector3
{

public:
	Vector3(float vx, float vy, float vz);
	Vector3(float xyz);
	Vector3();
	Vector3 operator*(const Vector3 &v);
	Vector3 operator*(const float &f);
	Vector3 operator+(const Vector3 &v);
	Vector3 operator+(const float &f);
	Vector3 operator-(const Vector3 &v);
	Vector3 operator-();
	Vector3 operator-(const float &f);
	/*static Vector3 forward();
	static Vector3 down();
	static Vector3 left();
	static Vector3 right();
	static Vector3 up();
	static Vector3 down();*/
public:
	float x = 0;
	float y = 0;
	float z = 0;
};

#endif // __ENGINE_VECTOR_3__