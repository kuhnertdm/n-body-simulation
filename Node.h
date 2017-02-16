#pragma once
  
#include "Object.h"
#include "Vector3.h"
#include <vector>
#include "BoundingBox.h"
#include "Main.h"

class Node {
public:
	float mass;
	Vector3 center;
	bool isLeaf;
	bool isEmpty;
	Node *children[2][2][2];
	Object *object;
	BoundingBox bb;

	void split(std::vector<Object*> objects) {
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
		this->isLeaf = true;
		this->isEmpty = false;
		if (objects.size() == 0) {
			this->isEmpty = true;
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
		if (objects.size() == 1) {
			this->object = objects[0];
		}
		else {
			this->isLeaf = false;
			split(objects);
		}
	}

	void updateForceOn(Object *target) {
		if (this->isEmpty) {
			return;
		}
		if (this->isLeaf && this->object == target) {
			return;
		}
		if (this->isLeaf) {
			target->updateForces(this->object);
			return;
		}
		float ratio = (this->bb.maxBound.x - this->bb.minBound.x) / 2 / (target->position.distance(this->center));
		if (ratio < CHEAT_RATIO) {
			//Treat as one
			target->updateForces(this->center, this->mass);
		} else {
			//Traverse down the tree
			if (!this->isLeaf) {
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 2; j++) {
						for (int k = 0; k < 2; k++) {
							this->children[i][j][k]->updateForceOn(target);
						}
					}
				}
			} else {
				target->updateForces(this->center, this->mass);
			}
		}
	}
};
