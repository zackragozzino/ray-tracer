#include "GeomObject.hpp"

GeomObject::GeomObject() { };

void GeomObject::parentPrint() {
    printf("- Color: {%.4f %.4f %.4f}\n", color.r, color.g, color.b);
    printf("- Material: \n");
    printf("  - Ambient: %.4f\n", finish.ambient);
    printf("  - Diffuse: %.4f\n", finish.diffuse);
}
