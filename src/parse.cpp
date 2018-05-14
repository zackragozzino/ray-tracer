
#include "parse.hpp"

// is this all the headers?
#include <iostream>
#include <limits>
#include <fstream>

std::vector<GeomObject*> Parse::parseFile(std::ifstream & file, Scene &scene)
{
    std::string String;

    file.seekg(0, std::ios::end);
    String.reserve((unsigned int)file.tellg());
    file.seekg(0, std::ios::beg);

    String.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return Parse::parseString(String, scene);
}

std::vector<GeomObject*> Parse::parseString(std::string const & filestream, Scene &scene)
{
	std::istringstream iss(filestream);
    std::string token;

    while (!iss.eof()) {
        iss >> token;

        //Check if token is a comment
		if (token.substr(0, 2) == "//")
			std::getline(iss, token);
		else if (token == "camera")
			scene.camera = parseCamera(iss);
		else if (token == "light_source")
			scene.lights.push_back(Parse::parseLight(iss));
		else if (token == "sphere")
			scene.objects.push_back(Parse::parseSphere(iss));
		else if (token == "plane")
			scene.objects.push_back(Parse::parsePlane(iss));
		else if (token == "triangle")
			scene.objects.push_back(Parse::parseTriangle(iss));

        //else
            //std::cout << token << std::endl;
    }

    return std::vector<GeomObject*>();
}

Camera * Parse::parseCamera(std::istringstream & iss)
{
	Camera *camera = new Camera;
	std::string token;
	std::stringstream Stream;

	iss >> token;
	validateToken("{", token);

	//Get the location vector
	iss >> token;
	validateToken("location", token);
	std::getline(iss, token);
	Stream.str(token);
	camera->location = Vector(Stream);

	//Get the up vector
	iss >> token;
	validateToken("up", token);
	std::getline(iss, token);
	Stream.str(token);
	camera->up = Vector(Stream);

	//Get the right vector
	iss >> token;
	validateToken("right", token);
	std::getline(iss, token);
	Stream.str(token);
	camera->right = Vector(Stream);

	//Get the look at vector
	iss >> token;
	validateToken("look_at", token);
	std::getline(iss, token);
	Stream.str(token);
	camera->look_at = Vector(Stream);

	iss >> token;
	validateToken("}", token);

	//camera->print();

	return camera;
}

Light * Parse::parseLight(std::istringstream & iss)
{
	Light *light = new Light;
	std::string token;
	std::stringstream Stream;
	std::stringstream Stream2;


	//Get the location vector
	std::getline(iss, token);
	Stream.str(token);
	light->location = Vector(Stream);

	//Get the color vector
	Stream >> token;
	validateToken("color", token);
	Stream >> token;
	validateToken("rgb", token);
	std::getline(Stream, token);
	token.resize(token.size() - 1);
	Stream2.str(token);
	light->color = Vector(Stream2);

	//light->print();

	return light;
}

GeomObject * Parse::parseSphere(std::istringstream & iss)
{
	Sphere *sphere = new Sphere;
	std::string token;
	std::stringstream Stream;
	std::stringstream Stream2;

	//Get the center vector
	std::getline(iss, token);

	
	Stream.str(token);
	sphere->center = Vector(Stream);

	//Get the radius
	Stream2.str(token);

	Stream2.ignore(std::numeric_limits<std::streamsize>::max(), ',');
	Stream2.ignore(std::numeric_limits<std::streamsize>::max(), ',');
	Stream2.ignore(std::numeric_limits<std::streamsize>::max(), ',');
	Stream2 >> token;
	sphere->radius = strtof(token.c_str(), NULL);
	

	//Get the color vector
	iss >> token;
	validateToken("pigment", token);
	std::getline(iss, token);
	Stream.str(token);
	sphere->color = Vector(Stream);

	//Get the finish info
	iss >> token;
	validateToken("finish", token);
	std::getline(iss, token);
	Stream.str(token);
	parseFinish(Stream, *sphere);

    return sphere;
}

GeomObject * Parse::parsePlane(std::istringstream & iss)
{
	Plane *plane = new Plane;
	std::string token;
	std::stringstream Stream;
	std::stringstream Stream2;

	//Get the normal
	std::getline(iss, token);
	Stream.str(token);
	plane->normal= Vector(Stream);

	//Get the distance
	Stream2.str(token);

	Stream2.ignore(std::numeric_limits<std::streamsize>::max(), ',');
	Stream2.ignore(std::numeric_limits<std::streamsize>::max(), ',');
	Stream2.ignore(std::numeric_limits<std::streamsize>::max(), ',');
	Stream2 >> token;
	plane-> distance = strtof(token.c_str(), NULL);


	//Get the color vector
	iss >> token;
	validateToken("pigment", token);
	std::getline(iss, token);
	Stream.str(token);
	plane->color = Vector(Stream);

	//Get the finish info
	iss >> token;
	validateToken("finish", token);
	std::getline(iss, token);
	Stream.str(token);
	parseFinish(Stream, *plane);

	return plane;
}

GeomObject * Parse::parseTriangle(std::istringstream & iss)
{
	Triangle *triangle = new Triangle;
	std::string token;
	std::stringstream Stream;
	
	std::getline(iss, token);
	//Get p1
	std::getline(iss, token);
	Stream.str(token);
	triangle->p1 = Vector(Stream);

	//Get p2
	std::getline(iss, token);
	Stream.str(token);
	triangle->p2 = Vector(Stream);

	//Get p3
	std::getline(iss, token);
	Stream.str(token);
	triangle->p3 = Vector(Stream);

	//Get the color vector
	iss >> token;
	validateToken("pigment", token);
	std::getline(iss, token);
	Stream.str(token);
	triangle->color = Vector(Stream);

	//Get the finish info
	iss >> token;
	validateToken("finish", token);
	std::getline(iss, token);
	Stream.str(token);
	parseFinish(Stream, *triangle);
	
	return triangle;
}

void Parse::parseFinish(std::stringstream & Stream, GeomObject & object) {
	std::stringbuf buf;
	std::stringstream bufSS;
	std::string token;

	Stream.ignore(std::numeric_limits<std::streamsize>::max(), '{');
	Stream.get(buf, '}');
	Stream.ignore(std::numeric_limits<std::streamsize>::max(), '}');

	bufSS.str(buf.str());

	//Get ambient value
	bufSS >> token;
	validateToken("ambient", token);
	bufSS >> token;
	object.finish.ambient = strtof((token).c_str(), 0);

	//Get diffuse value
	bufSS >> token;
	validateToken("diffuse", token);
	bufSS >> token;
	object.finish.diffuse = strtof((token).c_str(), 0);

	//Get specular
	bufSS >> token;
	if (token == "specular") {
		bufSS >> token;
		object.finish.specular = strtof((token).c_str(), 0);
	}

	//Get roughness
	bufSS >> token;
	if (token == "roughness") {
		bufSS >> token;
		object.finish.roughness = strtof((token).c_str(), 0);
	}


	
}


glm::vec3 Parse::Vector(std::stringstream & Stream)
{
	glm::vec3 v;
	v.x = v.y = v.z = 0.f;
	std::stringbuf buf;

	Stream.ignore(std::numeric_limits<std::streamsize>::max(), '<');
	Stream.get(buf, '>');
	Stream.ignore(std::numeric_limits<std::streamsize>::max(), '>');

	std::string line = buf.str(); // be careful...
	int read = sscanf(line.c_str(), "%f, %f, %f", &v.x, &v.y, &v.z);

	if (read != 3)
	{
		std::cerr << "Expected to read 3 vector elements but found '" << line << "'" << std::endl;
	}

	return v;
}

void Parse::validateToken(std::string const & expected, std::string const & actual)
{
	if (expected != actual) {
		std::cerr << "Expected '" << expected << "' but found '" << actual << "'" << std::endl;
		exit(1);
	}
}

// see: std::stof
