#pragma once
#include <string>
#include <sstream>
#include "GeomObject.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include <vector>

struct vec3
{
	float x, y, z;
};


class Parse
{

public:

	Parse() {}

    static std::vector<GeomObject *> parseFile(std::ifstream & file, Scene &scene);

private:

	static std::vector<GeomObject *> parseString(std::string const & filestream, Scene &scene);

	static Camera* parseCamera(std::istringstream & iss);

	static Light* parseLight(std::istringstream & iss);

	static GeomObject* parseSphere(std::istringstream & iss);

	static GeomObject* parsePlane(std::istringstream & iss);

	static void parseFinish(std::stringstream & iss, GeomObject & object);

	static glm::vec3 Vector(std::stringstream & Stream);

	static void validateToken(std::string const & expected, std::string const & actual);
};
