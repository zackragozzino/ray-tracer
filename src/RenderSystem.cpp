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

			if(hit.hit)
				color = calculateColor(scene, hit);
			//color = hit.color;

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


glm::vec3 RenderSystem::calculateColor(Scene &scene, Hit &hit)
{
	/*glm::vec3 pt = ray.position + ray.direction * t_val;
	glm::vec3 color = object->color * object->finish.ambient;
	bool inShadow;

	for (Light *light : scene.lights) {
		inShadow = false;
		glm::vec3 l = light->location;
	}*/

	glm::vec3 color = hit.color * hit.hitObject->finish.ambient;
	

	for (Light *light : scene.lights) {

		color += calculateDiffuse(hit, *light);
		color += calculateSpecular(hit, *light);
	}

	return color;
}

glm::vec3 RenderSystem::calculateDiffuse(Hit &hit, Light &light) {
	glm::vec3 diffuse = glm::vec3(0, 0, 0);
	glm::vec3 lightDir = glm::normalize(light.location - hit.hitPos);
	
	float NL = std::max(0.f, glm::dot(hit.normal, lightDir));

	if (NL && hit.hitObject->finish.diffuse) {
		diffuse = hit.hitObject->finish.diffuse * NL * light.color * hit.hitObject->color;
	}

	return diffuse;
}

glm::vec3 RenderSystem::calculateSpecular(Hit &hit, Light &light) {
	glm::vec3 specular = glm::vec3(0, 0, 0);
	glm::vec3 lightDir = glm::normalize(light.location - hit.hitPos);
	glm::vec3 half = glm::normalize(lightDir - hit.ray.direction);
	float HN = std::max(0.f, glm::dot(half, hit.normal));

	if (HN && hit.hitObject->finish.specular) {
		float r = hit.hitObject->finish.roughness * hit.hitObject->finish.roughness;
		specular = hit.hitObject->finish.specular * hit.hitObject->color * (float)pow(HN, 2 / r) * light.color;
	}
	
	return specular;
}


