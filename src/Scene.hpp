#pragma once

#include "GeomObject.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include <vector>

class Scene {
public:
	Scene();

	Camera *camera;
	std::vector<Light *> lights;
	std::vector<GeomObject *> objects;
	void print();

};