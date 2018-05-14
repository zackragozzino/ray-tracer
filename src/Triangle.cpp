#include "Triangle.hpp"

Triangle::Triangle() : GeomObject() {
	type = "Triangle";
}

float Triangle::intersect(const Ray & ray)
{
	glm::mat3 aMat, bMat, gMat, tMat;
	float detA, detB, detG, detT;
	float beta, gamma, T;

	aMat = 
		glm::mat3(p1.x - p2.x, p1.x - p3.x, ray.direction.x,
				  p1.y - p2.y, p1.y - p3.y, ray.direction.y,
				  p1.z - p2.z, p1.z - p3.z, ray.direction.z);
    bMat = 
		glm::mat3(p1.x - ray.position.x, p1.x - p3.x, ray.direction.x,
				  p1.y - ray.position.y, p1.y - p3.y, ray.direction.y,
			      p1.z - ray.position.z, p1.z - p3.z, ray.direction.z);
	gMat = 
		glm::mat3(p1.x - p2.x, p1.x - ray.position.x, ray.direction.x,
				  p1.y - p2.y, p1.y - ray.position.y, ray.direction.y,
				  p1.z - p2.z, p1.z - ray.position.z, ray.direction.z);
	tMat = 
		glm::mat3(p1.x - p2.x, p1.x - p3.x, p1.x - ray.position.x,
				  p1.y - p2.y, p1.y - p3.y, p1.y - ray.position.y,
				  p1.z - p2.z, p1.z - p3.z, p1.z - ray.position.z);

	detA = glm::determinant(aMat);
	detB = glm::determinant(bMat);
	detG = glm::determinant(gMat);
	detT = glm::determinant(tMat);

	beta = detB / detA;
	gamma = detG / detA;
	T = detT / detA;

	if (beta < 0 || beta > 1 || gamma < 0 || gamma > 1 - beta)
		return -1;
	else
		return T;
}

glm::vec3 Triangle::getNormal(glm::vec3 point)
{
	glm::vec3 normal;
	glm::vec3 U = p2 - p1;
	glm::vec3 V = p3 - p1;

	normal.x = (U.y * V.z) - (U.z * V.y);
	normal.y = (U.z * V.x) - (U.x * V.z);
	normal.z = (U.x - V.y) - (U.y * V.x);

	return normalize(normal);

	//return normalize(glm::vec3(V.y*W.z - V.z*W.y, V.z*W.x - V.x*W.z, V.x*W.y - V.y*W.x));
	
}

void Triangle::print()
{
		std::cout << "- Type: Triangle" << std::endl;
		printf("- p1: {%.4f %.4f %.4f}\n", p1.x, p1.y, p1.z);
		printf("- p2: {%.4f %.4f %.4f}\n", p2.x, p2.y, p2.z);
		printf("- p3: {%.4f %.4f %.4f}\n", p2.x, p2.y, p2.z);

		parentPrint();
}