#include "Hit.hpp"

const static float EPSILON = 0.0001f;

Hit::Hit() {};

Hit::Hit(Scene & scene, Ray & ray)
{
	this->ray = ray;
	this->hit = false;
	this->t_val = std::numeric_limits<float>::max();

	for (int i = 0; i < scene.objects.size(); i++) {
		checkIntersection(scene.objects[i]);
	}
}

void Hit::checkIntersection(GeomObject * object)
{
	float intersection_t = object->intersect(ray);

	if (intersection_t > EPSILON && intersection_t < t_val) {
		hit = true;
		t_val = intersection_t;
		hitObject = object;
		color = object->color;
		hitPos = ray.getIntersectionPoint(t_val);
		normal = glm::vec3(glm::transpose(glm::mat4(1.0f)) * glm::vec4(hitObject->getNormal(hitPos), 0.0f));
	}
}

Ray Hit::getReflectedRay()
{
	glm::vec3 reflectedDir = glm::normalize(ray.direction - 2 * glm::dot(ray.direction, normal) * normal);

	return Ray(reflectedDir * EPSILON + hitPos, reflectedDir);
}

Ray Hit::getRefractedRay()
{
    float n1 = 1;
    float n2 = hitObject->finish.ior;
    glm::vec3 refractionNormal = normal;
	
	float snellRatio = n1 / n2;
	
	//If ray is exiting media
	if (dot(normal, ray.direction) > 0) {
		snellRatio = n2 / n1;
		refractionNormal = -normal;
	}

	float dirDotNorm = dot(ray.direction, refractionNormal);

	glm::vec3 snellPart1 = snellRatio * (ray.direction - dirDotNorm * refractionNormal) - refractionNormal;
	float snellPart2 = (float)sqrt( 1 - (snellRatio*snellRatio) * (1 - (dirDotNorm*dirDotNorm)) );

	glm::vec3 refractedDir = glm::normalize(snellPart1 * snellPart2);

	return Ray(refractedDir * EPSILON + hitPos, refractedDir);
}

void Hit::print()
{
	if (hit) {
        printf("T = %.4f\n", t_val);
		std::cout << "Object Type: " << hitObject->type << std::endl;
	}
	else {
		std::cout << "No Hit" << std::endl;
	}

}
