#pragma once
#include "Vector3.h"


class BoundingBox {
public:
	Vector3 minBound;
	Vector3 maxBound;
	BoundingBox() {}
	BoundingBox(Vector3 minB, Vector3 maxB) {
		this->minBound = minB;
		this->maxBound = maxB;
	}

	virtual Vector3 getMinBound() {
		return this->minBound;
	}
	virtual Vector3 getMaxBound() {
		return this->maxBound;
	}
	BoundingBox expand(BoundingBox b) {
		Vector3 newMin;
		Vector3 newMax;
			newMin.x = fmin(this->minBound.x, b.minBound.x);
			newMax.x = fmax(this->maxBound.x, b.maxBound.x);
			newMin.y = fmin(this->minBound.y, b.minBound.y);
			newMax.y = fmax(this->maxBound.y, b.maxBound.y);
			newMin.z = fmin(this->minBound.z, b.minBound.z);
			newMax.z = fmax(this->maxBound.z, b.maxBound.z);
		BoundingBox newB = BoundingBox(newMin, newMax);
		return newB;
	}
};