#ifndef __ENGINE_VECTOR_4__
#define __ENGINE_VECTOR_4__

class Vector4
{

public:
	Vector4(float vx, float vy, float vz, float vw);
	Vector4(float xyzw);
	Vector4();
public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;
};

#endif// __ENGINE_VECTOR_4__