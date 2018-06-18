#include "Scene.hpp"

Scene::Scene() {

}

Ray Scene::castRay(int width, int height, int x, int y, int ssM, int ssN, int superSamples) {

    float u = -0.5 + ((x + (ssM + 0.5) / superSamples)) / width;
    float v = -0.5 + ((y + (ssN + 0.5) / superSamples)) / height;

	glm::vec3 w = glm::normalize(glm::vec3(camera->look_at - camera->location));


	glm::vec3 position = camera->location;
	glm::vec3 direction = glm::normalize(glm::vec3(u * camera->right + v * camera->up + w));

	Ray ray(position, direction);

	return ray;
};

void Scene::recursiveTreeBuild(std::vector<GeomObject *> objects, int axis, bvh_node *parent) {

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

	instantiateAABB(parent);
	
}

void Scene::instantiateAABB(bvh_node* parent) {
	// Leaf node
	if (parent->objs.size() == 1) {
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

void Scene::sort(std::vector<GeomObject *> &objects, int axis) {
	//Insertion sort based on online pseudocode
	int i, j;
	GeomObject * key;
	for (i = 1; i < objects.size(); i++)
	{
		key = objects[i];
		j = i - 1;

		while (j >= 0 && objects[j]->getCenter()[axis] > key->getCenter()[axis])
		{
			objects[j + 1] = objects[j];
			j = j - 1;
		}
		objects[j + 1] = key;
	}
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

HitObject* Scene::traverseTree(bvh_node *node, Ray &ray) {
	
	// Base Case

    if (node->objs.size() == 1) {
		glm::vec3 p = glm::vec3(node->objs[0]->invModelMatrix * glm::vec4(ray.position, 1));
		glm::vec3 d = glm::vec3(node->objs[0]->invModelMatrix * glm::vec4(ray.direction, 0));
		Ray objectSpaceRay(p, d);
		float t_Val = node->objs[0]->intersect(objectSpaceRay);
		
		if (t_Val > 0.0005f) {
			HitObject *hitObject = new HitObject;
			hitObject->object = node->objs[0];
			hitObject->t_Val = t_Val;
			hitObject->objectSpacePos = objectSpaceRay.getIntersectionPoint(t_Val);
			return hitObject;
		}
        else
            return nullptr;
    }

	if (node->aabb.intersect(ray) > 0.0005f) {

		HitObject* leftObj = nullptr;
		HitObject* rightObj = nullptr;

		leftObj = traverseTree(node->left, ray);
		rightObj = traverseTree(node->right, ray);

		if (leftObj != nullptr && rightObj != nullptr) {
			return leftObj->t_Val < rightObj->t_Val ? leftObj : rightObj;
		}
		else {
			return leftObj != nullptr ? leftObj : rightObj;
		}
	
	}

	return nullptr;
	
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