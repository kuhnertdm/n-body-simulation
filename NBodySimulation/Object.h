#pragma once
#include "Vector3.h"

class Object
{
public:
	Vector3 position;
	Vector3 velocity;
	Vector3 force;
	float size;
	Object(Vector3 position, float size);
	void resetForces();
	void updateForces(Object other);
	void move(float dt);
	~Object() {};
};

