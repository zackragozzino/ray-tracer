#include "RenderSystem.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define _USE_MATH_DEFINES
#include <math.h>

void RenderSystem::render(Scene & scene, int & width, int & height)
{
	glm::ivec2 size = glm::ivec2(width , height);
	const int numChannels = 3;
    glm::vec3 color;

	unsigned char *data = new unsigned char[size.x * size.y * numChannels];
	
	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			//Super sampling for anti-aliasing
            color = glm::vec3(0);
            for (int ssM = 0; ssM < superSamples; ssM++) {
                for (int ssN = 0; ssN < superSamples; ssN++) {
                    Ray ray = scene.castRay(width, height, x, y, ssM, ssN, superSamples);
                    color += calculateColor(scene, ray, MAX_RAY_BOUNCES);
                }
            }

            color /= (superSamples * superSamples);

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


glm::vec3 RenderSystem::calculateColor(Scene &scene, Ray &ray, int bounceCount)
{
	Hit hit(scene, ray);
	glm::vec3 color = glm::vec3(0,0,0);

	if (hit.hit && bounceCount > 0) {

		glm::vec3 blinnPhongColor = calculateBlinnPhong(scene, hit, bounceCount);
		glm::vec3 reflectionColor = calculateReflection(scene, hit, bounceCount);
		glm::vec3 refractionColor = calculateRefraction(scene, hit, bounceCount);

		float fresnelReflectance = 0.f;
		if (fresnel)
			fresnelReflectance = calculateFresnel(hit);

        float localContribution = (1 - hit.object->finish.filter) * (1 - hit.object->finish.reflection);
        float reflectionContribution = (1 - hit.object->finish.filter) * hit.object->finish.reflection + (hit.object->finish.filter) * (fresnelReflectance);
        float refractionContribution = hit.object->finish.filter * (1 - fresnelReflectance);

		color += blinnPhongColor * localContribution;
        color += reflectionColor * reflectionContribution;
        color += refractionColor * refractionContribution;
	}

	return color;
}

glm::vec3 RenderSystem::calculateBlinnPhong(Scene & scene, Hit & hit, int bounceCount)
{
	glm::vec3 color;
	if (!gi) {
		color = hit.object->finish.ambient * hit.color;
	}
	else {
		bounceCount = gi_bounces < bounceCount ? gi_bounces : bounceCount-1;
		color = calculateGI(scene, hit, bounceCount);
	}

	for (Light *light : scene.lights) {
		glm::vec3 lightDir = glm::normalize(light->location - hit.hitPos);
		Ray lightRay(hit.hitPos, lightDir);
		Hit lightHit(scene, lightRay);

		if (!lightHit.hit || glm::distance(hit.hitPos, light->location) < distance(hit.hitPos, lightHit.hitPos)) {
			color += calculateDiffuse(hit, *light);
			color += calculateSpecular(hit, *light);
		}
	}
	return color;
}

glm::vec3 RenderSystem::calculateDiffuse(Hit &hit, Light &light) {
	glm::vec3 diffuse = glm::vec3(0, 0, 0);
	glm::vec3 lightDir = glm::normalize(light.location - hit.hitPos);
	
	float NL = std::max(0.f, glm::dot(hit.normal, lightDir));

	if (NL && hit.object->finish.diffuse) {
		diffuse = hit.object->finish.diffuse * NL * light.color * hit.object->color;
	}

	return diffuse;
}

glm::vec3 RenderSystem::calculateSpecular(Hit &hit, Light &light) {
	glm::vec3 specular = glm::vec3(0, 0, 0);
	glm::vec3 lightDir = glm::normalize(light.location - hit.hitPos);
	glm::vec3 half = glm::normalize(lightDir - hit.ray.direction);
	float HN = std::max(0.f, glm::dot(half, hit.normal));

	if (HN && hit.object->finish.specular) {
		float r = hit.object->finish.roughness * hit.object->finish.roughness;
		specular = hit.object->finish.specular * hit.object->color * (float)pow(HN, 2/r - 2) * light.color;
	}
	
	return specular;
}

glm::vec3 RenderSystem::calculateReflection(Scene & scene, Hit & hit, int bounceCount)
{
	glm::vec3 reflectionColor = glm::vec3(0, 0, 0);

    //If there's not reflection and we're not doing fresnel on translucent objects
	if (hit.object->finish.reflection == 0 && (hit.object->finish.filter == 0 && !fresnel))
		return reflectionColor;

	Ray reflection = hit.getReflectedRay();
	reflectionColor = calculateColor(scene, reflection, bounceCount - 1) * hit.color;

	return reflectionColor;
}

glm::vec3 RenderSystem::calculateRefraction(Scene & scene, Hit & hit, int bounceCount)
{
	glm::vec3 refractionColor = glm::vec3(0, 0, 0);

	if (hit.object->finish.filter == 0)
		return refractionColor;

	Ray refraction = hit.getRefractedRay();
	Hit refractionHit = Hit(scene, refraction);

	if (!refractionHit.hit)
		return refractionColor;

	refractionColor = calculateColor(scene, refraction, bounceCount - 1);

    if (beers) {
        //If entering
        if (dot(hit.normal, hit.ray.direction) < 0)
            refractionColor *= calculateBeers(hit, refractionHit);
    }
    //If entering and not beers
    else if ( !(dot(hit.normal, hit.ray.direction) > 0) ) {
        refractionColor *= hit.color;
    }

	return refractionColor;
}
glm::vec3 RenderSystem::calculateGI(Scene & scene, Hit & hit, int bounceCount)
{
	glm::vec3 giColor = glm::vec3(0, 0, 0);
	int samples = gi_samples;

	glm::vec3 upVec = glm::vec3(0, 0, 1);
	float angle = glm::acos(glm::dot(upVec, hit.normal));
	glm::vec3 axis = glm::cross(upVec, hit.normal);
	glm::mat4 matrix = glm::rotate(glm::mat4(1.0f), angle, axis);

	if (gi_bounces - bounceCount > 0)
		samples /= ((gi_bounces - bounceCount) * 8);

	float sqrtSamples = std::sqrt(samples);
	float ratio = sqrtSamples / samples;

	for (float x = 0.0f; x <= samples; x += sqrtSamples) {
		for (float y = 0.0f; y <= samples; y += sqrtSamples) {
			float u = (x / samples) + ratio * (rand() / (float)RAND_MAX);
			float v = (y / samples) + ratio * (rand() / (float)RAND_MAX);

			glm::vec3 samplePt = calculateCosineWeightedPoint(u, v, matrix);
			Ray sampleRay(hit.hitPos + samplePt * 0.0001f, samplePt);
			giColor += calculateColor(scene, sampleRay, bounceCount);
		}
	}

	return giColor / (float)samples;
}

glm::vec3 RenderSystem::calculateCosineWeightedPoint(float u, float v, glm::mat4 & matrix)
{
	float radial = sqrt(u);
	float theta = 2.0 * M_PI * v;

	float x = radial * glm::cos(theta);
	float y = radial * glm::sin(theta);

	glm::vec3 weightedPoint = glm::vec3(x, y, sqrt(1 - u));
	return glm::vec3(matrix * glm::vec4(weightedPoint, 1.0));
}


glm::vec3 RenderSystem::calculateBeers(Hit & hit, Hit & refractionHit)

{
	float d = glm::distance(refractionHit.hitPos, hit.hitPos);
	glm::vec3 absorbance = (1.f - hit.color) * (0.15f) * -d;
	glm::vec3 attenuation = exp(absorbance);

    //std::cout << attenuation.x << " " << attenuation.y << " " << attenuation.z << std::endl;

	return attenuation;
}

float RenderSystem::calculateFresnel(Hit & hit)
{
	float n = hit.object->finish.ior;
	glm::vec3 norm = hit.normal;

	if (dot(norm, hit.ray.direction) > 0) {
		norm = -norm;
	}

	float incidence = ((n - 1.f)*(n - 1.f)) / ((n + 1.f) * (n + 1.f));

	return ( incidence + (1.f - incidence) * pow(1.f - dot(norm, -hit.ray.direction), 5.f) );
}


