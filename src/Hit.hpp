#pragma once

#include "Scene.hpp"
#include "GeomObject.hpp"
#include <string>

class Hit {
public:
	Hit();

	Hit(Scene &scene, Ray &ray);

	void checkIntersection(Ray &ray, GeomObject *object);

    glm::vec3 getHitColor(Ray &ray, GeomObject *object, float t_val);

	bool hit;
	Ray ray;
	float t_val;
	glm::vec3 color;

	GeomObject *hitObject = nullptr;

	void print();


};