#pragma once

#include "GeomObject.hpp"

class Plane : public GeomObject {
public:
	Plane();

	float intersect(const Ray &ray);
	glm::vec3 getCenter();
	glm::vec3 getNormal(glm::vec3 point);
	AABB* newAABB();
	glm::vec3 normal;
	float distance;

	void print();
};
