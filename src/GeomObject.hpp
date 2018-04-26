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
	};

	glm::vec3 color;
	Finish finish;
	std::string type;

	void parentPrint();

	virtual float intersect(const Ray &ray) = 0;
	virtual glm::vec3 getNormal(glm::vec3 point) = 0;
	virtual void print() = 0;

	
	//From Ian's reference

	/*~GeomObject();

	void parse_pigment(FILE *fp);
	void parse_transform(FILE *fp);

	virtual void parse(FILE *fp) {
		parse_pigment(fp);
		parse_transform(fp);
	}

protected:

	float tx, ty, tz;

private:
*/
};
