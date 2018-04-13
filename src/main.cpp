#include <vector>
#include <memory>
#include <algorithm>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "parse.hpp"
#include "Scene.hpp"
#include "parse.hpp"
#include "Hit.hpp"
#include "RenderSystem.hpp"

Scene scene;
RenderSystem renderSystem;

int main(int argc, char **argv)
{
    if (argc == 1) {;
        return 1;
    }

    std::ifstream FileHandle(argv[2]);

    if (!FileHandle) {
        std::cout << "File not found" << std::endl;
        return 1;
    }

    Parse::parseFile(FileHandle, scene);

	if(!strcmp(argv[1], "sceneinfo"))
		scene.print();
	else if (!strcmp(argv[1], "pixelray") || (!strcmp(argv[1], "firsthit"))) {
		int width = atoi(argv[3]);
		int height = atoi(argv[4]);
		int x = atoi(argv[5]);
		int y = atoi(argv[6]);

		Ray ray = scene.castRay(width, height, x, y);

		std::cout << "Pixel: [" << x << ", " << y << "] ";
		ray.print();
		
		if ((!strcmp(argv[1], "firsthit"))) {
			Hit hit(scene, ray);
			hit.print();
			if(hit.hit)
				std::cout << "Color: " << hit.color.r << " " << hit.color.g << " " << hit.color.b << std::endl;
		}

	}

	int width = atoi(argv[3]);
	int height = atoi(argv[4]);
	renderSystem.render(scene, width, height);

	return 0;
}
