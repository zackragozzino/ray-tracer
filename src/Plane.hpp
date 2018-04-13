#pragma once

#include "GeomObject.hpp"

class Plane : public GeomObject {
public:
	Plane();

	glm::vec3 normal;
	float distance;

	void print();
};
