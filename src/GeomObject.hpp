#pragma once

#include <stdio.h>

class GeomObject {

public:

	GeomObject();
	~GeomObject();

	void parse_pigment(FILE *fp);
	void parse_transform(FILE *fp);

	virtual void parse(FILE *fp) {
		parse_pigment(fp);
		parse_transform(fp);
	}

protected:

	float tx, ty, tz;

private:

};

class Sphere : public GeomObject { // derived (subcl)

public:

	Sphere();
	~Sphere();

	void parse_sphere(FILE *fp);

	void parse(FILE *fp) {
		GeomObject::parse(fp); // in java, super.parse(...)

		parse_sphere(fp);
	}

private:

	float cx, cy, cz;
	float rad;

};
