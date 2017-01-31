#pragma once
#include "Vector3.h"

class Object
{
public:
	Vector3 position;
	float size;
	Object(Vector3 position, float size);
	~Object() {};
};

