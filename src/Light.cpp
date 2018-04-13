#include "Light.hpp"

Light::Light() {};

void Light::print() {
    printf("- Location: {%.4f %.4f %.4f}\n", location.x, location.y, location.z);
    printf("- Color: {%.4f %.4f %.4f}\n", color.x, color.y, color.z);
};