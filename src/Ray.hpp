#pragma once

#include "glm/glm.hpp"
#include <iostream>

class Ray {
public:
	Ray();
	Ray(glm::vec3 pos, glm::vec3 dir);

	glm::vec3 getIntersectionPoint(float t_val);

	glm::vec3 position;
	glm::vec3 direction;

	void print();

};

