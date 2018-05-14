#pragma once

#include "Scene.hpp"
#include "GeomObject.hpp"
#include <string>

class Hit {
public:
	Hit();

	Hit(Scene &scene, Ray &ray);

	void checkIntersection(GeomObject *object);

	bool hit;
	Ray ray;
	float t_val;
	glm::vec3 color;
	glm::vec3 hitPos;
	glm::vec3 normal;

	GeomObject *hitObject = nullptr;

	void print();


};