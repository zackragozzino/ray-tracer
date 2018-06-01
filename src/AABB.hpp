#pragma once

#include "Box.hpp"

class AABB : public Box{
public:
	AABB();

	void Reset(glm::vec3 pt);
	void AddPoint(glm::vec3 pt);
	void AddBox(AABB *other);

};