#include "Hit.hpp"

const static float EPSILON = 0.0005f;

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


	glm::vec3 p = glm::vec3(object->invModelMatrix * glm::vec4(ray.position, 1.f));
	glm::vec3 d = glm::vec3(object->invModelMatrix * glm::vec4(ray.direction, 0.f));
	Ray objectSpaceRay(p, d);
	glm::vec3 objectSpacePos;

	float intersection_t = object->intersect(objectSpaceRay);

	if (intersection_t > EPSILON && intersection_t < t_val) {
		hit = true;
		t_val = intersection_t;
		hitObject = object;
		color = object->color;
		hitPos = ray.getIntersectionPoint(t_val);
		objectSpacePos = objectSpaceRay.getIntersectionPoint(t_val);
		normal = glm::vec3(glm::transpose(glm::mat4(1.f)) * glm::vec4(hitObject->getNormal(hitPos), 0.f));

		glm::vec3 objNormal = object->getNormal(objectSpacePos);
		glm::vec3 worldNorm = glm::vec3(glm::transpose(object->invModelMatrix) * glm::vec4(objNormal, 0.f));

		normal = glm::normalize(worldNorm);
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
	glm::vec3 refractedDir = glm::normalize(snellRatio*(ray.direction - dirDotNorm * refractionNormal) - refractionNormal * (float)sqrt(1 - (snellRatio*snellRatio) * (1 - (dirDotNorm*dirDotNorm))));

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
