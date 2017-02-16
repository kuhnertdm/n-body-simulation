#pragma once
  
#include "Object.h"
#include "Vector3.h"
#include <vector>
#include "BoundingBox.h"

class Node {
public:
	float mass;
	Vector3 center;
	bool isLeaf;
	Node *children[2][2][2];
	std::vector<Object*> objects;
	BoundingBox bb;

	void split(std::vector<Object*> &objects) {
		float splitx = (bb.maxBound.x + bb.minBound.x) / 2;
		float splity = (bb.maxBound.y + bb.minBound.y) / 2;
		float splitz = (bb.maxBound.z + bb.minBound.z) / 2;
		std::vector<Object*> *values[2][2][2];
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					values[i][j][k] = new std::vector<Object*>;
				}
			}
		}
		for (int i = 0; i < objects.size(); i++) {
			int ix = 0;
			int iy = 0;
			int iz = 0;;
			Object *ob = objects[i];
			if (ob->position.x > splitx) {
				ix = 1;
			}
			if (ob->position.y > splity) {
				iy = 1;
			}
			if (ob->position.z > splitz) {
				iz = 1;
			}
			values[ix][iy][iz]->push_back(ob);
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					this->children[i][j][k] = new Node(*values[i][j][k]);
				}
			}
		}
	}
	
	Node(std::vector<Object*> objects) {
		this->mass = 0;
		this->center = Vector3(0, 0, 0);
		//printf("Creating node with size %d\n", objects.size());
		int N = 10;
		if (objects.size() == 0) {
			this->isLeaf = true;
			this->objects = objects;
			this->mass = 0;
			this->center = Vector3(0, 0, 0);
			return;
		}
		BoundingBox newbb= BoundingBox(objects[0]->position, objects[0]->position);
		for (int i = 0; i < objects.size(); i++) {
			Object *ob = objects[i];
			newbb = newbb.expand(BoundingBox(ob->position, ob->position));
			this->mass += ob->size;
			this->center = this->center + (ob->position * ob->size);
		}
		this->center = this->center * (1 / this->mass);
		this->bb = newbb;
		//printf("Boundingbox minBound at %f, %f, %f, maxBound at %f, %f, %f\n", bb.minBound.x, bb.minBound.y, bb.minBound.z, bb.maxBound.x, bb.maxBound.y, bb.maxBound.z);
<<<<<<< HEAD
		//printf("A cluster of %d points created with mass %f, centered at %f, %f, %f\n", objects.size(), this->mass, this->center.x, this->center.y, this->center.z);
=======
>>>>>>> 32fe56d0258bdc4f738144d3ad2fc0d1c6494203
		if (objects.size() <= N) {
			this->isLeaf = true;
			this->objects = objects;
		}
		else {
			this->isLeaf = false;
			split(objects);
		}
		//printf("A cluster of %d points created with mass %f, centered at %f, %f, %f\n", objects.size(), this->mass, this->center.x, this->center.y, this->center.z);
	}

	/*
	void updatePhysics() {
		this->mass = 0;
		this->center = Vector3(0, 0, 0);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					Node *child = this->children[i][j][k];
					child->updatePhysics();
					this->mass += child->mass;
					this->center = this->center + (child->center * child->mass);
				}
			}
		}
		this->center = this->center * (1 / this->mass);
	}
	*/

	void updateForces(float outsideMass, Vector3 outsidePosition) {
		//printf("Updating forces at Node with mass %f\n", this->mass);
		if (this->isLeaf) {
			//printf("IsLeaf\n");
			for (int i = 0; i < this->objects.size(); i++) {
				if (!objects[i]->isAlive) continue;
				objects[i]->resetForces();
				for (int j = 0; j < this->objects.size(); j++) {
					if (i != j && objects[j]->isAlive) {
						objects[i]->updateForces(*objects[j]);
					}
				}
			}
			Object fakeObject = Object(outsidePosition, outsideMass);
			for (int i = 0; i < this->objects.size(); i++) {
				objects[i]->updateForces(fakeObject);
			}
		}
		else {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					for (int k = 0; k < 2; k++) {
						Node *child = this->children[i][j][k];
						float nextOutsideMass = this->mass + outsideMass - child->mass;
						Vector3 nextCenter = (this->mass * this->center + outsideMass * outsidePosition - child->mass * child->center) * (1.0f / nextOutsideMass);
						child->updateForces(nextOutsideMass, nextCenter);
					}
				}
			}
		}
	}
};
