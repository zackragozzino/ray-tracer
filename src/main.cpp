#include <vector>
#include <memory>
#include "Image.hpp"
#include <algorithm>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "parse.hpp"
#include "scene.hpp"

Scene scene;

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

    Parse::parseFile(FileHandle, scene);
	scene.print();
	return 0;
}
