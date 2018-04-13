#include "Plane.hpp"

Plane::Plane() {}

void Plane::print()
{
	std::cout << "- Type: Plane" << std::endl;
	std::cout << "- Normal: {" << normal.x << " " << normal.y << " " << normal.z << "}" << std::endl;
	std::cout << "- Distance: " << distance << std::endl;
	parentPrint();
};
