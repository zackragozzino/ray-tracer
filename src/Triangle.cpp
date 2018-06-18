#include "Triangle.hpp"

Triangle::Triangle() : GeomObject() {
	type = "Triangle";
}

float Triangle::intersect(const Ray & ray)
{
    const glm::vec3 abc = p1 - p2;
    const glm::vec3 def = p1 - p3;
    const glm::vec3 ghi = ray.direction;
    const glm::vec3 jkl = p1 - ray.position;

    const float ei_hf = def.y * ghi.z - ghi.y * def.z;
    const float gf_di = ghi.x * def.z - def.x * ghi.z;
    const float dh_eg = def.x * ghi.y - def.y * ghi.x;

    const float denom = abc.x * ei_hf + abc.y * gf_di + abc.z * dh_eg;

    if (denom == 0.f)
        return -1;

    const float beta = (jkl.x * ei_hf + jkl.y * gf_di + jkl.z * dh_eg) / denom;

    if (beta < 0 || beta > 1)
        return -1;

    const float ak_jb = abc.x * jkl.y - jkl.x * abc.y;
    const float jc_al = jkl.x * abc.z - abc.x * jkl.z;
    const float bl_kc = abc.y * jkl.z - jkl.y * abc.z;

    const float gamma = (ghi.z * ak_jb + ghi.y * jc_al + ghi.x * bl_kc) / denom;

    if (gamma < 0 || gamma > 1 - beta)
        return -1;

    const float t = (-def.z * ak_jb + -def.y * jc_al + -def.x * bl_kc) / denom;

    if (t < 0)
        return -1;

    return t;
}

AABB* Triangle::newAABB() {
	AABB* aabb = new AABB;
	aabb->Reset(p1);
	aabb->AddPoint(p2);
	aabb->AddPoint(p3);
	aabb->transform(ModelMatrix);
	return aabb;
}

glm::vec3 Triangle::getCenter() {
	return center;
}

glm::vec3 Triangle::getNormal(glm::vec3 point)
{
	glm::vec3 normal;
	glm::vec3 U = p2 - p1;
	glm::vec3 V = p3 - p1;

    normal = glm::cross(U, V);

	return normalize(normal);
}

void Triangle::print()
{
		std::cout << "- Type: Triangle" << std::endl;
		printf("- p1: {%.4f %.4f %.4f}\n", p1.x, p1.y, p1.z);
		printf("- p2: {%.4f %.4f %.4f}\n", p2.x, p2.y, p2.z);
		printf("- p3: {%.4f %.4f %.4f}\n", p2.x, p2.y, p2.z);

		parentPrint();
}
