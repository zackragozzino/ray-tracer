
#include <string>
#include <sstream>
#include "GeomObject.hpp"
#include <vector>

struct vec3
{
	float x, y, z;
};


class Parse
{

public:

	Parse() {}

    static std::vector<GeomObject *> parseFile(std::ifstream & file);

    static std::vector<GeomObject *> parseString(std::string const & filestream);

    static GeomObject * parseSphere(std::istringstream & iss);

	static vec3 Vector(std::stringstream & Stream);

};
