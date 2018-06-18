#include "Sphere.hpp"

Sphere::Sphere() {
	type = "Sphere";
};

float Sphere::intersect(const Ray & ray)
{
    const glm::vec3 offset = ray.position - center;

    const float a = glm::dot(ray.direction, ray.direction);
    const float b = 2.f * glm::dot(ray.direction, offset);
    const float c = glm::dot(offset, offset) - radius * radius;

    const float discriminant = b * b - 4.f * a * c;

    if (discriminant >= 0.f)
    {
        const float sqrtDiscriminant = sqrt(discriminant);

        float numerator = -b - sqrtDiscriminant;

        if (numerator < 0)
        {
            numerator = -b + sqrtDiscriminant;
        }

        const float t = numerator / (2.f * a);

        if (t >= 0.f)
        {
            return t;
        }
    }

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
