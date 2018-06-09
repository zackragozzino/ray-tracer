#include "AABB.hpp"
#include <algorithm>

AABB::AABB(){ 
    this->min = glm::vec3(std::numeric_limits<float>::infinity());
    this->max = glm::vec3(-std::numeric_limits<float>::infinity());
}

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

	this->center = (min + max) / 2.f;
}

void AABB::AddBox(AABB *other) {

	AddPoint(other->min);
	AddPoint(other->max);

	this->center = (min + max) / 2.f;
}

float AABB::intersect(const Ray & ray)
{
	float max = std::numeric_limits<float>::max();
	float min = std::numeric_limits<float>::lowest();

	for (int i = 0; i < 3; i++) {
		if (ray.direction[i] == 0) {
			if (ray.position[i] < this->min[i] || ray.position[i] > this->max[i])
				return -1;
		}
		else {
			float tmin = (this->min[i] - ray.position[i]) / ray.direction[i];
			float tmax = (this->max[i] - ray.position[i]) / ray.direction[i];

			if (tmin > tmax) {
				float temp = tmin;
				tmin = tmax;
				tmax = temp;
			}

			if (tmin > min)
				min = tmin;
			if (tmax < max)
				max = tmax;
		}
	}

	if (min > max)
		return -1;

	if (max < 0)
		return -1;

	if (min > 0)
		return min;
	else
		return max;
}

std::vector<glm::vec3> AABB::compute_8_vertices() {
	std::vector<glm::vec3> vertices;

	vertices.push_back(glm::vec3(min.x, min.y, min.z));
    vertices.push_back(glm::vec3(max.x, min.y, min.z));
    vertices.push_back(glm::vec3(min.x, max.y, min.z));
    vertices.push_back(glm::vec3(max.x, max.y, min.z));
	vertices.push_back(glm::vec3(min.x, min.y, max.z));
    vertices.push_back(glm::vec3(max.x, min.y, max.z));
	vertices.push_back(glm::vec3(min.x, max.y, max.z));
	vertices.push_back(glm::vec3(max.x, max.y, max.z));

	return vertices;
}

void AABB::transform(glm::mat4 &M) {

	std::vector<glm::vec3> vertices = compute_8_vertices();

	this->min = glm::vec3(std::numeric_limits<float>::max());
	this->max = glm::vec3(std::numeric_limits<float>::min());

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i] = glm::vec3(M * glm::vec4(vertices[i], 1.f));
	}

	Reset(vertices[0]);
	for (int i = 1; i < 8; ++i) {
		AddPoint(vertices[i]);
	}

	this->center = (min + max) / 2.f;
}

