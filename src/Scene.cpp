#include "Scene.hpp"

Scene::Scene() {

}

Ray Scene::castRay(int width, int height, int x, int y, int ssM, int ssN, int superSamples) {

	//float u = -0.5 + ((x + 0.5) / width);
	//float v = -0.5 + ((y + 0.5) / height);

    float u = -0.5 + ((x + (ssM + 0.5) / superSamples)) / width;
    float v = -0.5 + ((y + (ssN + 0.5) / superSamples)) / height;

	glm::vec3 w = glm::normalize(glm::vec3(camera->look_at - camera->location));


	glm::vec3 position = camera->location;
	glm::vec3 direction = glm::normalize(glm::vec3(u * camera->right + v * camera->up + w));

	Ray ray(position, direction);

	return ray;
};

void Scene::recursiveTreeBuild(std::vector<GeomObject *> objects, int axis, bvh_node *parent) {

	/*if (objects.size() > 1) {
		sort(parent->objs, axis);

		parent->left = new bvh_node;
		parent->right = new bvh_node;
		
		
		std::vector<GeomObject *> leftObjects(objects.begin(), objects.begin() + objects.size() / 2);
		recursiveTreeBuild(leftObjects, (axis + 1) % 3, parent->left);

		std::vector<GeomObject *> rightObjects(objects.begin() + objects.size() / 2, objects.end());
		recursiveTreeBuild(rightObjects, (axis + 1) % 3, parent->right);
	}
	parent->objs = objects;
	instantiateAABB(parent);
	*/



	
	if (objects.size() <= 1) {
        parent->objs = objects;
		instantiateAABB(parent);
        return;
    }

	sort(objects, axis);

    parent->left = new bvh_node;
    parent->right = new bvh_node;

	std::vector<GeomObject *> leftObjects(objects.begin(), objects.begin() + objects.size() / 2);
	recursiveTreeBuild(leftObjects, (axis + 1) % 3, parent->left);

	std::vector<GeomObject *> rightObjects(objects.begin() + objects.size() / 2, objects.end());
	recursiveTreeBuild(rightObjects, (axis + 1) % 3, parent->right);

	parent->objs = objects;
	instantiateAABB(parent);
	
}

void Scene::instantiateAABB(bvh_node* parent) {
	// Leaf node
	if (parent->objs.size() <= 1) {
		parent->aabb.AddBox(parent->objs[0]->newAABB());
	}
	// Inner node
	else {
		if (parent->left != nullptr) {
			parent->aabb.AddBox(&parent->left->aabb);
		}
		if (parent->right != nullptr) {
			parent->aabb.AddBox(&parent->right->aabb);
		}
	}
}

void Scene::sort(std::vector<GeomObject *> objects, int axis) {
	// Selection sort
	for (unsigned int i = 0; i < objects.size(); i++) {
		glm::vec3 icen = objects[i]->getCenter();
		unsigned int min = i;
		unsigned int j = i + 1;
		for (; j < objects.size(); j++) {
			glm::vec3 jcen = objects[j]->getCenter();
			if (jcen[axis] < icen[axis]) {
				min = j;
			}
		}
		if (min != i) {
			GeomObject* temp = objects[i];
			objects[i] = objects[min];
			objects[min] = temp;
		}
	}

	/*
	//Insertion sort based on online pseudocode
	int i, j;
	GeomObject * key;
	for (i = 1; i < objects.size(); i++)
	{
		key = objects[i];
		j = i - 1;

		while (j >= 0 && objects[j]->center[axis] > key->center[axis])
		{
			objects[j + 1] = objects[j];
			j = j - 1;
		}
		objects[j + 1] = key;
	}
	*/
}

void Scene::printTree(bvh_node *node, std::string type) {
	
	glm::vec3 min = node->aabb.min;
	glm::vec3 max = node->aabb.max;

	std::cout << type << ":" << std::endl;
	std::cout << "- min: " << glm::to_string(min) << std::endl;
	std::cout << "- max: " << glm::to_string(max) << std::endl;

	if (node->objs.size() == 1)
		std::cout << "Type: " << node->objs[0]->type.c_str() << std::endl;
	else
		std::cout << "branch - " << node->objs.size() << " objects" <<std::endl;

	std::cout << "--------------------" << std::endl;

	if(node->left != nullptr)
		printTree(node->left, type + "->left");
	if(node->right != nullptr)
		printTree(node->right, type + "->right");
}

GeomObject* Scene::traverseTree(bvh_node *node, Ray &ray) {

	/*std::cout << "~~~ Objects ~~~" << std::endl;
	std::cout << "Size: " << node->objs.size() << std::endl;
	for (int i = 0; i < node->objs.size(); i++) {
		std::cout << node->objs[i]->type.c_str() << std::endl;
	}
	std::cout << "~~~~~~~~~~~~" << std::endl;
	*/
	// Base Case
	

	//std::cout << "left: " << leftT << std::endl;
	//std::cout << "right: " << rightT << std::endl;

	if (node->aabb.intersect(ray) > 0.0005f) {

		if (node->objs.size() == 1) {
			//std::cout << "Returning: " << node->objs[0]->type.c_str() << std::endl;
			return node->objs[0];
		}

		GeomObject* leftObj = nullptr;
		GeomObject* rightObj = nullptr;

		leftObj = traverseTree(node->left, ray);
		rightObj = traverseTree(node->right, ray);

		//std::cout << "Testing... " << std::endl;

		if (leftObj != nullptr && rightObj != nullptr) {
			//std::cout << "left: " << leftT << std::endl;
			//std::cout << "right: " << rightT << std::endl;

			float leftT = node->left->aabb.intersect(ray);
			float rightT = node->right->aabb.intersect(ray);

			return leftT > rightT ? leftObj : rightObj;
		}
		else {
			//std::cout << "0 or 1 hit" << std::endl;
			return leftObj != nullptr ? leftObj : rightObj;
		}
	
	}

	return nullptr;

	/*
	//std::cout << node->objs.size() << std::endl;
	// Traversal	
	if (node->aabb.intersect(ray) > 0.0005f) {
		//std::cout << node->left->objs.size() << std::endl;
		GeomObject* leftObject;
		GeomObject* rightObject;

		float leftT = node->left->aabb.intersect(ray);
		float rightT = node->right->aabb.intersect(ray);

		//std::cout << "left: " << leftT << std::endl;
		//std::cout << "right: " << rightT << std::endl;

		if (leftT > 0.0005f || rightT > 0.0005f) {
			//std::cout << "left: " << leftT << std::endl;
			//std::cout << "right: " << rightT << std::endl;
			return leftT > rightT ? traverseTree(node->left, ray) : traverseTree(node->right, ray);
		}


		if (node->left != nullptr) {
			//std::cout << "Left..." << std::endl;
			//leftObject = traverseTree(node->left, ray);
			//return traverseTree(node->left, ray);
		}
		if (node->right != nullptr) {
			//std::cout << "Right..." << std::endl;
			//rightObject = traverseTree(node->right, ray);
			//return traverseTree(node->right, ray);
		}

		//return leftObject->intersect(ray) > rightObject->intersect(ray) ? leftObject : rightObject;


	}
	return nullptr;
	*/
	
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