#include "Box.hpp"
#include <glm/gtc/epsilon.hpp>

const static float EPSILON = 0.0001f;

Box::Box() : GeomObject()
{
	type = "Box";
}

float Box::intersect(const Ray & ray)
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

glm::vec3 Box::getNormal(glm::vec3 point)
{

	if (glm::epsilonEqual(point.x, this->min.x, EPSILON))
		return glm::vec3(-1, 0, 0);
	else if (glm::epsilonEqual(point.x, this->max.x, EPSILON))
		return glm::vec3(1, 0, 0);
	else if (glm::epsilonEqual(point.y, this->min.y, EPSILON))
		return glm::vec3(0, -1, 0);
	else if (glm::epsilonEqual(point.y, this->max.y, EPSILON))
		return glm::vec3(0, 1, 0);
	else if (glm::epsilonEqual(point.z, this->min.z, EPSILON))
		return glm::vec3(0, 0, -1);
	else if (glm::epsilonEqual(point.z, this->max.z, EPSILON))
		return glm::vec3(0, 0, 1);
	else
		return glm::vec3(0, 0, 0);
}

void Box::print()
{
}
