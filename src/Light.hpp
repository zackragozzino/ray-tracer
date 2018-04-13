#pragma once

#include "glm/glm.hpp"
#include <iostream>

class Light {
public:
	Light();

	void print();

	glm::vec3 location;
	glm::vec3 color;
};
