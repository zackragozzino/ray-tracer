#include "GeomObject.hpp"

GeomObject::GeomObject() { };

void GeomObject::parentPrint() {
	//std::cout << "- Color: {" << color.x << " " << color.y << " " << color.z << "}" << std::endl;
    printf("- Color: {%.4f %.4f %.4f}\n", color.r, color.g, color.b);
    //std::cout << "- Material:" << std::endl;
    printf("- Material: \n");
    //std::cout << "  - Ambient: " << finish.ambient << std::endl;
    printf("  - Ambient: %.4f\n", finish.ambient);
    //std::cout << "  - Diffuse: " << finish.diffuse << std::endl;
    printf("  - Diffuse: %.4f\n", finish.diffuse);
}
