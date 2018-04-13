
#include "parse.hpp"

// is this all the headers?
#include <iostream>
#include <limits>
#include <fstream>
#include <streambuf>
using namespace std;

std::vector<GeomObject*> Parse::parseFile(std::ifstream & file)
{
    std::string String;

    file.seekg(0, std::ios::end);
    String.reserve((unsigned int)file.tellg());
    file.seekg(0, std::ios::beg);

    String.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return Parse::parseString(String);
}

std::vector<GeomObject*> Parse::parseString(std::string const & filestream)
{
    std::istringstream iss(filestream);
    std::string token;
    std::vector<GeomObject*> obj;

    while (!iss.eof()) {
        iss >> token;

        //Check if token is a comment
        if (token.substr(0, 2) == "//")
            std::getline(iss, token);
        else if (token == "sphere")
            obj.push_back(Parse::parseSphere(iss));

        else
            std::cout << token << std::endl;
    }

    return std::vector<GeomObject*>();
}

GeomObject * Parse::parseSphere(std::istringstream & iss)
{
    std::streambuf buf();
    iss.ignore(numeric_limits<streamsize>::max(), '<');
    iss.get(buf(), '>');  
    std::string test;
    buf().sputn(test, buf())
    int read = sscanf(buf() )


    return nullptr;
}


vec3 Parse::Vector(std::stringstream & Stream)
{
	vec3 v;
	v.x = v.y = v.z = 0.f;
	std::stringbuf buf;

	Stream.ignore(1, '<');
	Stream.get(buf, '>');
	Stream.ignore(numeric_limits<streamsize>::max(), '>');

	string line = buf.str(); // be careful...
	int read = sscanf(line.c_str(), "%f, %f, %f", &v.x, &v.y, &v.z);

	if (read != 3)
	{
		cerr << "Expected to read 3 vector elements but found '" << line << "'" << endl;
	}

	return v;
}

// see: std::stof
