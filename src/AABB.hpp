#pragma once

#include "glm/glm.hpp"
#include "Ray.hpp"
#include <vector>

class AABB{
public:
	AABB();

	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 center;

	void Reset(glm::vec3 pt);
	void AddPoint(glm::vec3 pt);
	void AddBox(AABB *other);
	float intersect(const Ray & ray);
	std::vector<glm::vec3> compute_8_vertices();
	void transform(glm::mat4 &M);

};