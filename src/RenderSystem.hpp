#pragma once

#include <glm/glm.hpp>
#include "Scene.hpp"
#include "Hit.hpp"
#include <algorithm>

class RenderSystem {
public:

	void render(Scene & scene, int & width, int & height);

	glm::vec3 calculateColor(Scene &scene, Hit &hit);

	glm::vec3 calculateDiffuse(Hit &hit, Light &light);

	glm::vec3 calculateSpecular(Hit &hit, Light &light);

	std::string fileName = "output.png";

};