#pragma once

#include <glm/glm.hpp>
#include "Scene.hpp"
#include "Hit.hpp"
#include <algorithm>

#define MAX_RAY_BOUNCES 6

class RenderSystem {
public:

	void render(Scene & scene, int & width, int & height);

	glm::vec3 calculateColor(Scene &scene, Ray &ray, int bounceCount);

	glm::vec3 calculateBlinnPhong(Scene &scene, Hit &hit);

	glm::vec3 calculateDiffuse(Hit &hit, Light &light);

	glm::vec3 calculateSpecular(Hit &hit, Light &light);

	glm::vec3 calculateReflection(Scene &scene, Hit &hit, int bounceCount);

	glm::vec3 calculateRefraction(Scene &scene, Hit &hit, int bounceCount);

	glm::vec3 calculateBeers(Hit &hit, Hit & refractionHit);

	float calculateFresnel(Hit &hit);

	std::string fileName = "output.png";

	bool fresnel;

	bool beers;

    int superSamples = 1;

};