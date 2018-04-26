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

glm::vec3 Hit::getHitColor(Ray & ray, GeomObject * object, float t_val)
{
    glm::vec3 pt = ray.position + ray.direction * t_val;
    glm::vec3 color = object->color * object->finish.ambient;



    return glm::vec3();
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
