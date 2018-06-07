#include "AABB.hpp"
#include <algorithm>

AABB::AABB(){ }

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
	float tgmax = std::numeric_limits<float>::infinity();
	float tgmin = -std::numeric_limits<float>::infinity();

	for (int i = 0; i < 3; i++) {
		if (ray.direction[i] == 0) {
			if (ray.position[i] >= this->min[i] || ray.position[i] < this->max[i])
				return -1;
		}
		else {
			float t1 = (this->min[i] - ray.position[i]) / ray.direction[i];
			float t2 = (this->max[i] - ray.position[i]) / ray.direction[i];

			if (t1 > t2) {
				float temp = t1;
				t1 = t2;
				t2 = temp;
			}

			if (t1 > tgmin)
				tgmin = t1;
			if (t2 < tgmax)
				tgmax = t2;
		}
	}

	if (tgmin > tgmax)
		return -1;

	if (tgmax < 0)
		return tgmin;

	if (tgmin > 0)
		return tgmin;
	else
		return tgmax;
}

std::vector<glm::vec3> AABB::compute_8_vertices() {
	std::vector<glm::vec3> vertices;

	vertices.push_back(glm::vec3(min.x, min.y, min.z));
	vertices.push_back(glm::vec3(min.x, min.y, max.z));
	vertices.push_back(glm::vec3(min.x, max.y, max.z));
	vertices.push_back(glm::vec3(min.x, max.y, min.z));
	vertices.push_back(glm::vec3(max.x, min.y, min.z));
	vertices.push_back(glm::vec3(max.x, min.y, max.z));
	vertices.push_back(glm::vec3(max.x, max.y, max.z));
	vertices.push_back(glm::vec3(max.x, max.y, min.z));

	return vertices;
}

void AABB::transform(glm::mat4 &M) {

	std::vector<glm::vec3> vertices = compute_8_vertices();

	this->min = glm::vec3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	this->max = -min;
	
	/*
	for (int i = 0; i < 8; i++) {
		vertices[i] = glm::vec3(M * glm::vec4(vertices[i], 1.f));
		AddPoint(vertices[i]);
	}*/

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i] = glm::vec3(M * glm::vec4(vertices[i], 1.f));
	}

	Reset(vertices[0]);
	for (int i = 1; i < 8; ++i) {
		AddPoint(vertices[i]);
	}

	this->center = (min + max) / 2.f;
}

