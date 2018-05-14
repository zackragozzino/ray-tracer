#pragma once

#include "GeomObject.hpp"

class Triangle : public GeomObject {
public:
	Triangle();

	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;

	float intersect(const Ray &ray);
	glm::vec3 getNormal(glm::vec3 point);
	void print();

};


