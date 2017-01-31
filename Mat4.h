#pragma once
#include <iostream>
#include "Vector3.h"

class Mat4
{
public:

	float * mat;

	Mat4() {
		mat = new float[16];
		for (int i = 0; i < 16; i++) { mat[i] = 0.0f; }
		mat[0] = 1;		mat[5] = 1;		mat[10] = 1;	mat[15] = 1;

	}
	~Mat4() {
		delete[] mat;
	}

	void set(int r, int c, float value) {
		*(mat + (4 * r + c)) = value;
	}

	float * getMatrix() {
		return mat;
	}


	friend std::ostream &operator<<(std::ostream &output, const Mat4 &m) {
		output << "[" << m.mat[0] << "," << m.mat[1] << "," << m.mat[2] << "," << m.mat[3] << "]\n";
		output << "[" << m.mat[4] << "," << m.mat[5] << "," << m.mat[6] << "," << m.mat[7] << "]\n";
		output << "[" << m.mat[8] << "," << m.mat[9] << "," << m.mat[10] << "," << m.mat[11] << "]\n";
		output << "[" << m.mat[12] << "," << m.mat[13] << "," << m.mat[14] << "," << m.mat[15] << "]";
		return output;
	}

	void setRow(int row, float a, float b, float c, float d) {
		mat[4 * row + 0] = a;
		mat[4 * row + 1] = b;
		mat[4 * row + 2] = c;
		mat[4 * row + 3] = d;
	}

	void createSimpleTransformationMatrix(float x, float y, float z, float s) {
		setRow(0, s, 0, 0, x);
		setRow(1, 0, s, 0, y);
		setRow(2, 0, 0, s, z);
		setRow(3, 0, 0, 0, 1);
	}

	void createProjectionMatrix(float angle, float ratio, float near, float far) {
		angle *= 2 * 3.14159f / 360;
		float tan_angle = (float)tan(angle / 2);
		setRow(0, 1 / (ratio*tan_angle), 0, 0, 0);
		setRow(1, 0, 1 / (tan_angle), 0, 0);
		setRow(2, 0, 0, -(far + near) / (far - near), -2 * (far*near) / (far - near));
		setRow(3, 0, 0, -1, 0);

	}
	void createViewMatrix(Vector3 position, Vector3 right, Vector3 direction, Vector3 up) {
		setRow(0, right.x, right.y, right.z, -right.dot(position));
		setRow(1, up.x, up.y, up.z, -up.dot(position));
		setRow(2, -direction.x, -direction.y, -direction.z, direction.dot(position));
		setRow(3, 0, 0, 0, 1);

	}

};

