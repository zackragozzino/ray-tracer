#pragma once

#include "Scene.hpp"
#include "GeomObject.hpp"
#include "HitObject.hpp"
#include <string>

class Hit {
public:
	Hit();

	Hit(Scene &scene, Ray &ray);

	void checkIntersection(GeomObject *object);

	void getObjectT(GeomObject *object);

	Ray getReflectedRay();

	Ray getRefractedRay();

	bool hit;
	Ray ray;
	float t_val;
	HitObject *hitObject = nullptr;
	glm::vec3 color;
	glm::vec3 hitPos;
	glm::vec3 normal;

	GeomObject *object = nullptr;

	void print();


};