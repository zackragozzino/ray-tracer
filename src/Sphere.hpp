#pragma once

#include "GeomObject.hpp"
#include <algorithm>
class Sphere : public GeomObject { // derived (subcl)

public:

	Sphere();

	glm::vec3 center;
	float radius;

	float intersect(const Ray &ray);
	AABB *newAABB();
	glm::vec3 getNormal(glm::vec3 point);
	void print();

};