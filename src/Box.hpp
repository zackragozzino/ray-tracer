#pragma once

#include "GeomObject.hpp"


class Box : public GeomObject{
public:
	Box();

	float intersect(const Ray &ray);
	glm::vec3 getNormal(glm::vec3 point);
	void print();

	glm::vec3 min;
	glm::vec3 max;

};