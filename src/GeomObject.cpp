#include "GeomObject.hpp"

GeomObject::GeomObject() { };

void GeomObject::parentPrint() {
	std::cout << "- Color: {" << color.x << " " << color.y << " " << color.z << "}" << std::endl;
	std::cout << "- Material:" << std::endl;
	std::cout << "  - Ambient: " << finish.ambient << std::endl;
	std::cout << "  - Diffuse: " << finish.diffuse << std::endl;
}
