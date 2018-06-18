#include "Box.hpp"
#include <glm/gtc/epsilon.hpp>

const static float EPSILON = 0.0001f;

Box::Box() : GeomObject()
{
	type = "Box";
}

float Box::intersect(const Ray & ray)
{
    float max = std::numeric_limits<float>::max();
    float min = std::numeric_limits<float>::lowest();

    for (int i = 0; i < 3; i++) {
        if (ray.direction[i] == 0) {
            if (ray.position[i] < this->min[i] || ray.position[i] > this->max[i])
                return -1;
        }
        else {
            float tmin = (this->min[i] - ray.position[i]) / ray.direction[i];
            float tmax = (this->max[i] - ray.position[i]) / ray.direction[i];

            if (tmin > tmax) {
                float temp = tmin;
                tmin = tmax;
                tmax = temp;
            }

            if (tmin > min)
                min = tmin;
            if (tmax < max)
                max = tmax;
        }
    }

    if (min > max)
        return -1;

    if (max < 0)
        return -1;

    if (min > 0)
        return min;
    else
        return max;
}

AABB* Box::newAABB() {
	AABB *aabb = new AABB();
	aabb->min = this->min;
	aabb->max = this->max;
	aabb->transform(ModelMatrix);
	return aabb;
}

glm::vec3 Box::getCenter() {
	return (min + max) / 2.0f;
}

glm::vec3 Box::getNormal(glm::vec3 point)
{

	if (glm::epsilonEqual(point.x, this->min.x, EPSILON))
		return glm::vec3(-1, 0, 0);
	else if (glm::epsilonEqual(point.x, this->max.x, EPSILON))
		return glm::vec3(1, 0, 0);
	else if (glm::epsilonEqual(point.y, this->min.y, EPSILON))
		return glm::vec3(0, -1, 0);
	else if (glm::epsilonEqual(point.y, this->max.y, EPSILON))
		return glm::vec3(0, 1, 0);
	else if (glm::epsilonEqual(point.z, this->min.z, EPSILON))
		return glm::vec3(0, 0, -1);
	else if (glm::epsilonEqual(point.z, this->max.z, EPSILON))
		return glm::vec3(0, 0, 1);
	else
		return glm::vec3(0, 0, 0);
}

void Box::print()
{
	std::cout << "- Type: Box" << std::endl;
	printf("- Min: {%.4f %.4f %.4f}\n", min.x, min.y, min.z);
	printf("- Max: {%.4f %.4f %.4f}\n", max.x, max.y, max.z);
	parentPrint();
}
