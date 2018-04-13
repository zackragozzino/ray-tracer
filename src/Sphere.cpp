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

void Sphere::print() {
	std::cout << "- Type: Sphere" << std::endl;
	//std::cout << "- Center: {" << center.x << " " << center.y << " " << center.z << "}" << std::endl;
    printf("- Center: {%.4f %.4f %.4f}\n", center.x, center.y, center.z);
	//std::cout << "- Radius " << radius << std::endl;
    printf("- Radius: %.4f\n", radius);
    parentPrint();
};

float intersect(const Ray & ray)
{
	return 0.0f;
}
