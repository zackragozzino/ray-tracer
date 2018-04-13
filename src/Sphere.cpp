#include "Sphere.hpp"

Sphere::Sphere() {
};

void Sphere::print() {
	std::cout << "- Type: Sphere" << std::endl;
	std::cout << "- Center: {" << center.x << " " << center.y << " " << center.z << "}" << std::endl;
	std::cout << "- Radius " << radius << std::endl;
	parentPrint();
};