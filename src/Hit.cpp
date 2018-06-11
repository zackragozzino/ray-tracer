#include "Hit.hpp"

const static float EPSILON = 0.0005f;

Hit::Hit() {
	
};

Hit::Hit(Scene & scene, Ray & ray)
{
	hitObject = new HitObject;
	this->ray = ray;
	this->hit = false;
	this->t_val = std::numeric_limits<float>::max();

	for (int i = 0; i < scene.objects.size(); i++) {
		getObjectT(scene.objects[i]);
		checkIntersection(scene.objects[i]);
	}

	if (scene.sds) {
		hitObject = scene.traverseTree(scene.rootNode, ray);
		if (hitObject != nullptr) {
			checkIntersection(hitObject->object);
		}
	}
}

void Hit::checkIntersection(GeomObject * object)
{
	/*
	glm::vec3 p = glm::vec3(object->invModelMatrix * glm::vec4(ray.position, 1));
	glm::vec3 d = glm::vec3(object->invModelMatrix * glm::vec4(ray.direction, 0));
	Ray objectSpaceRay(p, d);


	float intersection_t = object->intersect(objectSpaceRay);
	*/
	
	if (hitObject->t_Val > EPSILON && hitObject->t_Val < t_val) {
		hit = true;
		t_val = hitObject->t_Val;
		this->object = object;
		color = object->color;
		hitPos = ray.getIntersectionPoint(t_val);
		normal = glm::vec3(glm::transpose(glm::mat4(1.f)) * glm::vec4(this->object->getNormal(hitPos), 0));
		glm::vec3 objNormal = object->getNormal(hitObject->objectSpacePos);
		glm::vec3 worldNorm = glm::vec3(glm::transpose(object->invModelMatrix) * glm::vec4(objNormal, 0));

		normal = glm::normalize(worldNorm);
	}
}

void Hit::getObjectT(GeomObject * object)
{
	glm::vec3 p = glm::vec3(object->invModelMatrix * glm::vec4(ray.position, 1));
	glm::vec3 d = glm::vec3(object->invModelMatrix * glm::vec4(ray.direction, 0));
	Ray objectSpaceRay(p, d);
	float intersection_t = object->intersect(objectSpaceRay);

	hitObject->object = object;
	hitObject->t_Val = intersection_t;
	hitObject->objectSpacePos = objectSpaceRay.getIntersectionPoint(intersection_t);
}

Ray Hit::getReflectedRay()
{
	glm::vec3 reflectedDir = glm::normalize(ray.direction - 2 * glm::dot(ray.direction, normal) * normal);

	return Ray(reflectedDir * EPSILON + hitPos, reflectedDir);
}

Ray Hit::getRefractedRay()
{
    float n1 = 1;
    float n2 = object->finish.ior;
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
		std::cout << "Object Type: " << object->type << std::endl;
	}
	else {
		std::cout << "No Hit" << std::endl;
	}

}
