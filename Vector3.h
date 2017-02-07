#pragma once
#include <iostream>

class Vector3
{

public:
	float x, y, z;

	Vector3() : x(0), y(0), z(0) {}
	Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
	Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) {}

	float dot(Vector3 v) {
		return x*v.x + y*v.y + z*v.z;
	}
	float magnitude() {
		return sqrt(x*x + y*y + z*z);
	}
	Vector3 normalize() {
		float n = magnitude();
		return Vector3(x / n, y / n, z / n);
	}
	static Vector3 cross(Vector3 v1, Vector3 v2) {
		return Vector3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
	}

	friend Vector3 operator/(const Vector3 &v, const Vector3 &v2);

	friend Vector3 operator+(const Vector3 &v, const Vector3 &v2) {
		return Vector3(v.x + v2.x, v.y + v2.y, v.z + v2.z);
	}
	friend Vector3 operator+(const Vector3 &v, const float a) {
		return Vector3(v.x + a, v.y + a, v.z + a);
	}
	friend Vector3 operator-(const Vector3 &v, const Vector3 &v2) {
		return Vector3(v.x - v2.x, v.y - v2.y, v.z - v2.z);
	}
	friend bool operator==(const Vector3 &v, const Vector3 &v2) {
		return v.x == v2.x && v.y == v2.y && v.z == v2.z;
	}
	Vector3 round() {
		return Vector3((int)(x + .5), (int)(y + .5), (int)(z + .5));
	}
	float distance(Vector3 v) {
		return Vector3(x - v.x, y - v.y, z - v.z).magnitude();
	}



	Vector3& operator+=(const Vector3 &v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}


	friend Vector3 operator*(float f, const Vector3 &v) {
		return Vector3(v.x * f, v.y * f, v.z * f);
	}
	friend Vector3 operator*(const Vector3 &v, float f) {
		return Vector3(v.x * f, v.y * f, v.z * f);
	}

	friend std::ostream &operator<<(std::ostream &output, const Vector3 &v) {
		output << "[" << v.x << "," << v.y << "," << v.z << "]";
		return output;
	}

	static Vector3 getRandomVec3() {
		return Vector3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
	}


	~Vector3() {};

};

