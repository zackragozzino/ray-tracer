#include "Sphere.hpp"

Sphere::Sphere() {
	type = "Sphere";
};

float Sphere::intersect(const Ray & ray)
{
	glm::vec3 dist = ray.position - center;
	float A = dot(ray.direction, ray.direction);
	float B = dot(ray.direction + ray.direction, dist);
	float C = dot(dist, dist) - radius * radius;
	float determinant = B * B - 4 * A*C;

	if (determinant < 0)
		return -1;

	determinant = sqrt(determinant);
	float t1 = (-B + determinant) / (2 * A);
	float t2 = (-B - determinant) / (2 * A);

	if (t1 > 0 && t2 > 0)
		return std::min(t1, t2);
	else if (t1 > 0 || t2 > 0)
		return t1 > 0 ? t1 : t2;

	return -1;
}

AABB* Sphere::newAABB() {
	AABB* aabb = new AABB();

	aabb->Reset(center - radius);
	aabb->AddPoint(center + radius);

	aabb->transform(this->ModelMatrix);
	return aabb;
}

glm::vec3 Sphere::getCenter() {
	return center;
}

glm::vec3 Sphere::getNormal(glm::vec3 point) {
	return glm::normalize(point - center);
}

void Sphere::print() {
	std::cout << "- Type: Sphere" << std::endl;
    printf("- Center: {%.4f %.4f %.4f}\n", center.x, center.y, center.z);
    printf("- Radius: %.4f\n", radius);
    parentPrint();
};
