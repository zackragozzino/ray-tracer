#include "Scene.hpp"

Scene::Scene() {

}
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
	std::cout << "---" << std::endl;
}
;