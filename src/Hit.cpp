#include "Hit.hpp"

Hit::Hit() {};

Hit::Hit(Scene & scene, Ray & ray)
{
	this->ray = ray;
	this->hit = false;
	this->t_val = std::numeric_limits<float>::max();

	for (int i = 0; i < scene.objects.size(); i++) {
		checkIntersection(ray, scene.objects[i]);
	}
}

void Hit::checkIntersection(Ray & ray, GeomObject * object)
{
	float intersection_t = object->intersect(ray);

	if (intersection_t > 0.0f && intersection_t < t_val) {
		hit = true;
		t_val = intersection_t;
		hitObject = object;
		color = object->color;
	}
}

void Hit::print()
{
	if (hit) {
		std::cout << "T = " << t_val << std::endl;
		std::cout << "Object Type: " << hitObject->type << std::endl;
	}
	else {
		std::cout << "No Hit" << std::endl;
	}

}
