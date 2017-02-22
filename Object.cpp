#include "Object.h"
#include "Main.h"



Object::Object(Vector3 position, float size){
	this->position = position;
	this->size = size;
	this->velocity = Vector3(0, 0, 0);
	this->force = Vector3(0, 0, 0);
	this->isAlive = true;
}

void Object::resetForces() {
	this->force = Vector3(0, 0, 0);
}

void Object::updateForces(Object *other) {
	if (!this->isAlive || !other->isAlive) return;
	Vector3 dir = (other->position - this->position).normalize();

	float dist = this->position.distance(other->position);
	dist = sqrt(dist*dist + SOFTEN * SOFTEN);

	if (dist < CUBE_DEM) {
		if (this->size > other->size) {
			other->isAlive = false;
			//printf("Velocities before collide: %f %f\n", this->velocity.magnitude(), other->velocity.magnitude());
			this->velocity = (this->velocity * this->size + other->velocity * other->size) * (1.0f / (this->size + other->size));
			//printf("Velocity after collide: %f\n", this->velocity.magnitude());
			this->size += other->size;
			other->size = 0;
			return;
		}
		else {
			this->isAlive = false;
			other->velocity = (this->velocity * this->size + other->velocity * other->size) * (1.0f / (this->size + other->size));
			other->size += this->size;
			this->size = 0;
			return;
		}
	}
	float m1 = this->size;
	float m2 = other->size;

	this->force += dir * (G * m1 * m2 / dist / dist);
	
}

void Object::updateForces(Vector3 oPosition, float mass) {
	Vector3 dir = (oPosition - this->position).normalize();

	float dist = this->position.distance(oPosition);

	dist = sqrt(dist*dist + SOFTEN * SOFTEN);
	float m1 = this->size;
	float m2 = mass;

	this->force += dir * (G * m1 * m2 / dist / dist);
}

void Object::move(float dt) {
	this->velocity += this->force * (1.0f / this->size) * dt;
	this->position += this->velocity * dt;
}