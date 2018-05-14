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
