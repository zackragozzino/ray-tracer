#include "GeomObject.hpp"

GeomObject::GeomObject() { };

void GeomObject::parentPrint() {
    printf("- Color: {%.4f %.4f %.4f}\n", color.r, color.g, color.b);
    printf("- Material: \n");
    printf("  - Ambient: %.4f\n", finish.ambient);
    printf("  - Diffuse: %.4f\n", finish.diffuse);
	printf("  - Specular: %.4f\n", finish.specular);
	printf("  - Roughness: %.4f\n", finish.roughness);
	printf("  - Reflection: %.4f\n", finish.reflection);
	printf("  - Refraction: %.4f\n", finish.refraction);
	printf("  - ior: %.4f\n", finish.ior);
	printf("  - Filter: %.4f\n", finish.filter);
}
