#include "Object.h"
#include "Vector3.h"
#include <vector>

class Node {
public:
	bool isLeaf;
	Node *children[2][2][2];
	Vector3 minBound;
	Vector3 maxBound;
	std::vector<Object*> objects;

	void split(std::vector<Object*> objects) {
		
	}
	
	Node(std::vector<Object*> objects) {}
};
