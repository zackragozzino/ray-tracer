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

			//std::cout << "Wrote to " << x << " , " << y << std::endl;
			//std::cout << glm::to_string(color) << std::endl;
		}
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;
}

float RenderSystem::reMap(float oldValue) {
	float oldRange = (1.f - (-1.f));
	float newRange = (1.f - 0.f);
	float newValue = (((oldValue - (-1.f)) * newRange) / oldRange);

	return newValue;
}

void RenderSystem::renderStereogram(Scene & scene, int & width, int & height) {
	glm::ivec2 size = glm::ivec2(width, height);
	const int numChannels = 3;
	glm::vec3 color;

    int patternDiv = 8;
	int patternWidth = size.x / patternDiv;


    unsigned char *patternTex = generateNoise(size, patternWidth, numChannels);
    unsigned char *depthTex = calculateDepthMap(scene, size, patternWidth, numChannels);
	unsigned char *outTex = new unsigned char[size.x * size.y * numChannels];


	//Perform offsets and write final image
	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			if (x < patternWidth) {
				outTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = patternTex[(patternWidth * numChannels) * (size.y - 1 - y) + numChannels * x + 0];
				outTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = patternTex[(patternWidth * numChannels) * (size.y - 1 - y) + numChannels * x + 1];
				outTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = patternTex[(patternWidth * numChannels) * (size.y - 1 - y) + numChannels * x + 2];
			}
			else {

				int shift = depthTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] / patternDiv;
				int shiftedIndex = x - patternWidth + shift;

				float shiftColorR = outTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * shiftedIndex + 0];
				float shiftColorG = outTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * shiftedIndex + 1];
				float shiftColorB = outTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * shiftedIndex + 2];

				outTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = shiftColorR;
				outTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = shiftColorG;
				outTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = shiftColorB;
			}
		}
	}

	if(depthMap)
		stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, depthTex, size.x * numChannels);
	else
		stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, outTex, size.x * numChannels);
        


	delete[] patternTex;
	delete[] depthTex;
	delete[] outTex;

	std::cout << "Done writing stereogram" << std::endl;
}

unsigned char* RenderSystem::generateNoise(glm::ivec2 size, int patternWidth, int numChannels) {
    unsigned char *patternTex = new unsigned char[patternWidth * size.y * numChannels];
    glm::vec3 color;
    srand(time(NULL));

    float mod = 360.f / size.y;

    int offset1 = (rand() / (float)RAND_MAX) * 300;
    int offset2 = (rand() / (float)RAND_MAX) * 300;
    int offset3 = (rand() / (float)RAND_MAX) * 300;


    std::cout << "Generating random noise... " << std::endl;
    //Generate random noise
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < patternWidth; ++x)
        {
            float noise = rand() / (float)RAND_MAX;

            float redVal = round(reMap(sin(glm::radians(y * mod + offset1))) * 255.f);
            float greenVal = round(reMap(sin(glm::radians(y * mod + offset2))) * 255.f);
            float blueVal = round(reMap(sin(glm::radians(y * mod + offset3))) * 255.f);

            //std::cout << redVal << " " << greenVal << " " << blueVal << std::endl;

            color = glm::vec3(redVal, greenVal, blueVal);
            color += glm::vec3(round(glm::clamp(noise, 0.f, 1.f) * 255.f));

            //color = glm::vec3(round(glm::clamp(noise, 0.f, 1.f) * 255.f));

            patternTex[(patternWidth * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = color.r;
            patternTex[(patternWidth * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = color.g;
            patternTex[(patternWidth * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = color.b;
        }
    }
    return patternTex;
}

unsigned char* RenderSystem::calculateDepthMap(Scene &scene, glm::ivec2 size, int patternWidth, int numChannels) {
    unsigned char *depthTex = new unsigned char[size.x * size.y * numChannels];
    glm::vec3 color;
    std::vector<float> depthData;

    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::lowest();

    std::cout << "Getting intersections..." << std::endl;
    //Store intersection info
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            Ray ray = scene.castRay(size.x, size.y, x, y, 0, 0, superSamples);
            Hit hit(scene, ray);

            if (hit.hit && strcmp("Plane", hit.object->type.c_str())) {
                depthData.push_back(hit.t_val);

                if (hit.t_val > max)
                    max = hit.t_val;
                if (hit.t_val < min)
                    min = hit.t_val;
            }
            else
                depthData.push_back(-1.f);
        }
    }

    float oldRange = (min - max);
    float newRange = 1;

    std::cout << "Writing depth map..." << std::endl;
    //Write depth map
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            color = glm::vec3(0);

            float depthVal = depthData.at(y*size.x + x);

            //Check if non-intersection
            if (depthVal == -1)
                depthVal = max + 0.1f;

            float depthValRemap = (((depthVal - max) * newRange) / oldRange);
            color = glm::vec3(round(glm::clamp(depthValRemap, 0.f, 1.f) * 255.f));

            depthTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = color.r;
            depthTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = color.g;
            depthTex[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = color.b;
        }
    }

    return depthTex;
}


glm::vec3 RenderSystem::calculateColor(Scene &scene, Ray &ray, int bounceCount)
{
	glm::vec3 color = glm::vec3(0, 0, 0);
	
	if (bounceCount <= 0)
		return color;

	Hit hit(scene, ray);

	if (hit.hit) {

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

	if (gi) {
		bounceCount = (gi_bounces < bounceCount ? gi_bounces : (bounceCount - 1));
		color = calculateGI(scene, hit, bounceCount);
	}
	else {
		color = hit.object->finish.ambient * hit.color;
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
	glm::vec3 upVector = glm::vec3(0, 0, 1);

	int numSamples = gi_samples;

	if (gi_bounces - bounceCount > 0)
		numSamples /= ((gi_bounces - bounceCount) * 8);

	float angle = glm::acos(glm::dot(upVector, hit.normal));
	glm::vec3 axis = glm::cross(upVector, hit.normal);

	glm::mat4 matrix;
	if (upVector == hit.normal) {
		matrix = glm::mat4(1.f);
	}
	else if (upVector == -hit.normal) {
		matrix = glm::mat4(-1.f);
	}
	else
		matrix = glm::rotate(glm::mat4(1.0f), angle, axis);

	float rootSamples = std::sqrt(numSamples);
	float ratio = rootSamples / numSamples;

	// Stratified samples 
	for (float x = 0.f; x <= numSamples; x += rootSamples) {
		for (float y = 0.f; y <= numSamples; y += rootSamples) {
			float gridX = x / numSamples + ratio * (rand() / (float)RAND_MAX);
			float gridY = y / numSamples + ratio * (rand() / (float)RAND_MAX);

			glm::vec3 samplePt = calculateCosineWeightedPoint(gridX, gridY);
			samplePt = glm::vec3(matrix * glm::vec4(samplePt, 1.f));
			Ray sampleRay(hit.hitPos + samplePt * 0.0001f, samplePt);
			giColor += calculateColor(scene, sampleRay, bounceCount);
		}
	}

	giColor *= 1 / (float)numSamples;

	return giColor;
}

glm::vec3 RenderSystem::calculateCosineWeightedPoint(float u, float v)
{
	float radial = sqrt(u);
	float theta = 2.0 * M_PI * v;

	float x = radial * glm::cos(theta);
	float y = radial * glm::sin(theta);

	return glm::vec3(x, y, sqrt(1 - u));
}


glm::vec3 RenderSystem::calculateBeers(Hit & hit, Hit & refractionHit)

{
	float d = glm::distance(refractionHit.hitPos, hit.hitPos);
	glm::vec3 absorbance = (1.f - hit.color) * (0.15f) * -d;
	glm::vec3 attenuation = exp(absorbance);

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


