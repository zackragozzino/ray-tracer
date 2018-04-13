#include "Camera.hpp"

Camera::Camera() {}

void Camera::print()
{
	std::cout << "Camera:" << std::endl;
	std::cout << "- Location: {" << location.x << " " << location.y << " " << location.z << "}" << std::endl;
	std::cout << "- Up: {" << up.x << " " << up.y << " " << up.z << "}" << std::endl;
	std::cout << "- Right: {" << right.x << " " << right.y << " " << right.z << "}" << std::endl;
	std::cout << "- Look at: {" << look_at.x << " " << look_at.y << " " << look_at.z << "}" << std::endl;
};
