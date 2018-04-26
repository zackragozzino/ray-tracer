#pragma once

#include "GeomObject.hpp"
#include <algorithm>
class Sphere : public GeomObject { // derived (subcl)

public:

	Sphere();

	glm::vec3 center;
	float radius;

	float intersect(const Ray &ray);
	glm::vec3 getNormal(glm::vec3 point);
	void print();
	

	//From Ian's example

	/*~Sphere();

	void parse_sphere(FILE *fp);

	void parse(FILE *fp) {
		GeomObject::parse(fp); // in java, super.parse(...)

		parse_sphere(fp);
	}


private:

	float cx, cy, cz;
	float rad;
	*/

};