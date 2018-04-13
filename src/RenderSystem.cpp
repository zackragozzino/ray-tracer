#include "RenderSystem.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void RenderSystem::render(Scene & scene, int & width, int & height)
{
	glm::ivec2 size = glm::ivec2(width , height);
	const int numChannels = 3;

	unsigned char *data = new unsigned char[size.x * size.y * numChannels];
	
	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			glm::vec3 color = glm::vec3(0, 0, 0);

			Ray ray = scene.castRay(width, height, x, y);
			Hit hit(scene, ray);

			color = hit.color;
			color.r = round(glm::clamp(color.r, 0.f, 1.f) * 255.f);
			color.g = round(glm::clamp(color.g, 0.f, 1.f) * 255.f);
			color.b = round(glm::clamp(color.b, 0.f, 1.f) * 255.f);

			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = color.r;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = color.g;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = color.b;
		}
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;
	
}
