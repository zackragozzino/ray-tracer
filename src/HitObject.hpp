#pragma once

#include "GeomObject.hpp"

class HitObject {
public:
	GeomObject * object = nullptr;
	glm::vec3 objectSpacePos;
	float t_Val = 0;
};