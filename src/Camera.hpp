#pragma once

#include "glm/glm.hpp"
#include <iostream>

class Camera {
	public:
		Camera();

		void print();

		glm::vec3 location;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 look_at;
};
