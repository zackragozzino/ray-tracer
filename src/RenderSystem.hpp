#pragma once

#include <glm/glm.hpp>
#include "Scene.hpp"
#include "Hit.hpp"
#include <algorithm>
#include <vector>

#define MAX_RAY_BOUNCES 6

class RenderSystem {
public:

	void render(Scene & scene, int & width, int & height);

	void renderStereogram(Scene & scene, int & width, int & height);

	glm::vec3 calculateColor(Scene &scene, Ray &ray, int bounceCount);

	glm::vec3 calculateBlinnPhong(Scene &scene, Hit &hit, int bounceCount);

	glm::vec3 calculateDiffuse(Hit &hit, Light &light);

	glm::vec3 calculateSpecular(Hit &hit, Light &light);

	glm::vec3 calculateReflection(Scene &scene, Hit &hit, int bounceCount);

	glm::vec3 calculateRefraction(Scene &scene, Hit &hit, int bounceCount);
	
	glm::vec3 calculateGI(Scene &scene, Hit &hit, int bounceCount);

	glm::vec3 calculateCosineWeightedPoint(float u, float v);

	glm::vec3 calculateBeers(Hit &hit, Hit & refractionHit);

	float calculateFresnel(Hit &hit);

	float reMap(float oldValue);

	std::string fileName = "output.png";

	bool fresnel;

	bool beers;

	bool SIS;

	bool depthMap;

	bool gi;
	int gi_samples = 64;
	int gi_bounces = 2;

    int superSamples = 1;

};