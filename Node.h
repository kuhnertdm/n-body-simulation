#pragma once


#include "Object.h"
#include "Vector3.h"
#include <vector>
#include "BoundingBox.h"

class Node {
public:
	bool isLeaf;
	Node *children[2][2][2];
	std::vector<Object*> objects;
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
					children[i][j][k] = new Node(*values[i][j][k]);
				}
			}
		}
	}
	
	Node(std::vector<Object*> objects) {
		int N = 1;
		bb.minBound = objects[0]->position;
		bb.maxBound = objects[0]->position;
		for (int i = 0; i < objects.size(); i++) {
			bb.expand(BoundingBox(objects[i]->position, objects[i]->position));
		}
		this->bb = bb;
		if (objects.size <= N) {
			this->isLeaf = true;
			this->objects = objects;
		}
		else {
			split(objects);
		}
	}
};
