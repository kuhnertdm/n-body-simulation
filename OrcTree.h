#pragma once
#include "Node.h"
#include <vector>

class OrcTree {
public:
	Node *root;

	OrcTree() {}

	OrcTree(std::vector<Object*> &objects) {
		this->root = new Node(objects);
	}
};