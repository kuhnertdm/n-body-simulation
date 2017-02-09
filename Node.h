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
