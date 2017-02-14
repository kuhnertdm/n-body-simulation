#include "Object.h"
#include "Main.h"



Object::Object(Vector3 position, float size){
	this->position = position;
	this->size = size;
	this->velocity = Vector3(0, 0, 0);
	this->force = Vector3(0, 0, 0);
}

void Object::resetForces() {
	this->force = Vector3(0, 0, 0);
}

void Object::updateForces(Object other) {
	Vector3 dir = (other.position - this->position).normalize();
	float dist = CUBE_DIM * (this->position.distance(other.position));

	float m1 = this->size * MAX_MASS;
	float m2 = other.size * MAX_MASS;

	this->force += dir * (G * m1 * m2 / dist / dist);
	
}

void Object::move(float dt) {
	this->velocity += this->force * (1.0f / this->size / MAX_MASS) * dt;
	this->position += this->velocity * dt;
}