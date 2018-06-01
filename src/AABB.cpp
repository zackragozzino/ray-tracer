#include "AABB.hpp"
#include <algorithm>

AABB::AABB() : Box(){ }

void AABB::Reset(glm::vec3 pt) {
	this->min = this->max = pt;
}

void AABB::AddPoint(glm::vec3 pt) {

	this->min.x = std::min(min.x, pt.x);
	this->min.y = std::min(min.y, pt.y);
	this->min.z = std::min(min.z, pt.z);

	this->max.x = std::max(max.x, pt.x);
	this->max.y = std::max(max.y, pt.y);
	this->max.z = std::max(max.z, pt.z);
}

void AABB::AddBox(AABB *other) {

	AddPoint(other->min);
	AddPoint(other->max);

}

