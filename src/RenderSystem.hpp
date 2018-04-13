#pragma once

#include <glm/glm.hpp>
#include "Scene.hpp"
#include "Hit.hpp"

class RenderSystem {
public:

	void render(Scene & scene, int & width, int & height);

	std::string fileName = "output.png";

};