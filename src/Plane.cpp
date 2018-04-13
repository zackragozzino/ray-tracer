#include "Plane.hpp"

Plane::Plane() {
	type = "Plane";
}
float Plane::intersect(const Ray & ray)
{
	float denominator = dot(ray.direction, normal);
	if (denominator == 0)
		return -1;

	float numerator = distance - dot(ray.position, normal);

	return numerator / denominator;
}
;

void Plane::print()
{
	std::cout << "- Type: Plane" << std::endl;
	//std::cout << "- Normal: {" << normal.x << " " << normal.y << " " << normal.z << "}" << std::endl;
    printf("- Normal: {%.4f %.4f %.4f}\n", normal.x, normal.y, normal.z);
	//std::cout << "- Distance: " << distance << std::endl;
    printf("- Distance: %.4f\n", distance);
    parentPrint();
};
