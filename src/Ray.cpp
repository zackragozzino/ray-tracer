#include "Ray.hpp"

Ray::Ray() {};

Ray::Ray(glm::vec3 pos, glm::vec3 dir) {
	this->position = pos;
	this->direction = dir;
}

void Ray::print() {
	//std::cout << "Ray: " << "{" << position.x << " " << position.y << " " << position.z << "}";
	//std::cout << " -> ";
	//std::cout << "{" << direction.x << " " << direction.y << " " << direction.z << "}" << std::endl;
	printf("Ray: {%.4f, %.4f, %.4f} -> {%.4f, %.4f, %.4f}\n", position.x, position.y, position.z, direction.x, direction.y, direction.z);
};