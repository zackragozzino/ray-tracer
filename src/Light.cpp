#include "Light.hpp"

Light::Light() {};

void Light::print() {

	std::cout << "- Location: {" << location.x << " " << location.y << " " << location.z << "}" << std::endl;
	std::cout << "- Color: {" << color.x << " " << color.y << " " << color.z << "}" << std::endl;
};