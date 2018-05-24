#pragma once

#include <stdio.h>
#include <iostream>
#include "glm/glm.hpp"
#include "Ray.hpp"

class GeomObject {

public:

	GeomObject();

	struct Finish {
		float ambient = 0;
		float diffuse = 0;
		float specular = 0;
		float roughness = 0;
		float reflection = 0;
		float refraction = 0;
		float ior = 0;
		float filter = 0;
	};

	glm::vec3 color;
	Finish finish;
	std::string type;
	glm::mat4 ModelMatrix;
	glm::mat4 invModelMatrix;

	void parentPrint();

	virtual float intersect(const Ray &ray) = 0;
	virtual glm::vec3 getNormal(glm::vec3 point) = 0;
	virtual void print() = 0;
};
