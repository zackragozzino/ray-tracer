#include "Ray.hpp"

Ray::Ray() {};

Ray::Ray(glm::vec3 pos, glm::vec3 dir) {
	this->position = pos;
	this->direction = dir;
}

glm::vec3 Ray::getIntersectionPoint(float t_val) {
	return position + t_val *direction;
}

void Ray::print() {
	printf("Ray: {%.4f %.4f %.4f} -> {%.4f %.4f %.4f}\n", position.x, position.y, position.z, direction.x, direction.y, direction.z);
};