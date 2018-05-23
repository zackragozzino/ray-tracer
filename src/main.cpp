#include <vector>
#include <memory>
#include <algorithm>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

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
	else if (!strcmp(argv[1], "pixelray") || !strcmp(argv[1], "firsthit") || !strcmp(argv[1], "pixelcolor") || !strcmp(argv[1], "printrays") ) {
		int width = atoi(argv[3]);
		int height = atoi(argv[4]);
		int x = atoi(argv[5]);
		int y = atoi(argv[6]);

		Ray ray = scene.castRay(width, height, x, y, 0, 0, 1);

		std::cout << "Pixel: [" << x << ", " << y << "] ";
		ray.print();
		
		if (!strcmp(argv[1], "firsthit") || !strcmp(argv[1], "printrays")) {
			Hit hit(scene, ray);
			hit.print();
			if(hit.hit)
                printf("Color: %.4f %.4f %.4f\n", hit.color.r, hit.color.g, hit.color.b);
		}

		else if(!strcmp(argv[1], "pixelcolor"))
		{
			Hit hit(scene, ray);
			glm::vec3 color = renderSystem.calculateColor(scene, ray, 6);

			printf("T = %.4f\n", hit.t_val);
			std::cout << "Object Type: " << hit.hitObject->type << std::endl;
			std::cout << "BRDF: " << "Blinn-Phong" << std::endl;
			printf("Color: (%.0f, %.0f, %.0f)\n", color.r, color.g, color.b);
		}

    }
    else if (!strcmp(argv[1], "render")) {
		//std::cout << argv[5] << std::endl;
		if (std::string(argv[5]).find("-ss") != std::string::npos) {
			size_t last_index = std::string(argv[5]).find_last_not_of("0123456789");
			//std::cout << std::string(argv[5]).substr(last_index + 1) << std::endl;
			std::string ss = std::string(argv[5]).substr(last_index + 1);
			renderSystem.superSamples = atoi(ss.c_str());
		}

        int width = atoi(argv[3]);
        int height = atoi(argv[4]);
        renderSystem.render(scene, width, height);
    }

	return 0;
}
