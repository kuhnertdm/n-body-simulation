#include "Object.h"



Object::Object(Vector3 position, float size){
	this->position = position;
	this->size = size;
	this->velocity = Vector3(0, 0, 0);
	this->force = Vector3(0, 0, 0);
} 