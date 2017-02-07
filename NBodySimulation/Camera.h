#pragma once
#include "Vector3.h"
#include "Mat4.h"


class Camera
{

public:
	enum CameraType {
		FIRST_PERSON,
		THIRD_PERSON
	};


public:
	Camera();
	~Camera();

	CameraType camType = THIRD_PERSON;

	Vector3 position = Vector3(0, 0, 5);
	Vector3 direction;
	Vector3 right;
	Vector3 up = Vector3(0, 1, 0);

	float horzAngle = 0, vertAngle = 3.14159f;

	Mat4 viewMatrix;

	
	void update() {

		if (vertAngle <= 3.14159f / 2) {
			vertAngle = 3.14159f / 2;
		}
		if (vertAngle >= 3 * 3.14159f / 2) {
			vertAngle = 3 * 3.14159f / 2;
		}


		direction.x = (float)(cos(vertAngle) * sin(horzAngle));
		direction.y = (float)sin(vertAngle);
		direction.z = (float)(cos(vertAngle) * cos(horzAngle));
		direction = direction.normalize();


		right.x = (float)sin(horzAngle - 3.14f / 2.0f);
		right.y = 0;
		right.z = (float)cos(horzAngle - 3.14f / 2.0f);
		right = right.normalize();

		up = Vector3::cross(direction, right).normalize();

		/*
		if (camType == FIRST_PERSON) {
			position = player->position;
		}

		if (camType == THIRD_PERSON) {
			position = player->position - 4 * direction;
		}
		*/

		viewMatrix.createViewMatrix(position, right, direction, up);

	}

};

