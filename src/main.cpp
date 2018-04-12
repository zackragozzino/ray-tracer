#include <vector>
#include <memory>
#include "Image.h"
#include <algorithm>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "parse.hpp"


int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Usage: raytracer <infile>.pov" << std::endl;
        return 1;
    }

    std::ifstream FileHandle(argv[1]);

    if (!FileHandle) {
        std::cout << "File not found" << std::endl;
        return 1;
    }

    Parse::parseFile(FileHandle);

    /*std::ifstream file(argv[1]);
    std::istringstream iss;
    std::stringstream sstr;

    if (!file) {
        std::cout << "File not found" << std::endl;
        return 1;
    }

    sstr << file.rdbuf();
    //std::cout << sstr.str() << std::endl;
    iss.str(sstr.str());

    std::string line;

    //std::cout << iss.getline() << '\n';

    std::string word;
    while (!iss.eof()) {
		iss >> word;

		if (word == "//")
			std::getline(iss, word);
		else
			std::cout << word << std::endl;
    }
    */
	return 0;
}
