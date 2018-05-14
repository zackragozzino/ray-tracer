#include "Camera.hpp"

Camera::Camera() {}

void Camera::print()
{
	std::cout << "Camera:" << std::endl;
    printf("- Location: {%.4f %.4f %.4f}\n", location.x, location.y, location.z);
    printf("- Up: {%.4f %.4f %.4f}\n", up.x, up.y, up.z);
    printf("- Right: {%.4f %.4f %.4f}\n", right.x, right.y, right.z);
    printf("- Look at: {%.4f %.4f %.4f}\n", look_at.x, look_at.y, look_at.z);
};
