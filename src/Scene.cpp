#include "Scene.hpp"

Scene::Scene() {

}

Ray Scene::castRay(int width, int height, int x, int y) {

	float u = -0.5 + ((x + 0.5) / width);
	float v = -0.5 + ((y + 0.5) / height);

	glm::vec3 w = glm::normalize(glm::vec3(camera->look_at - camera->location));


	glm::vec3 position = camera->location;
	glm::vec3 direction = glm::normalize(glm::vec3(u * camera->right + v * camera->up + w));

	Ray ray(position, direction);

	return ray;
};

void Scene::print()
{
	//Print camera info
	camera->print();
	std::cout << std::endl;
	std::cout << "---" << std::endl << std::endl;

	//Print light info
	std::cout << lights.size() << " light(s)" << std::endl << std::endl;
	for(int i=0; i < lights.size(); i++){
		std::cout << "Light[" << i << "]:" << std::endl;
		lights[i]->print();
		std::cout << std::endl;
	}
	std::cout << "---" << std::endl << std::endl;

	//Print GeomObject info
	std::cout << objects.size() << " object(s)" << std::endl;
	for (int i = 0; i < objects.size(); i++) {
		std::cout << std::endl;
		std::cout << "Object[" << i << "]:" << std::endl;
		objects[i]->print();
	}

}
;