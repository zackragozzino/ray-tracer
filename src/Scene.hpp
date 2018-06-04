#pragma once

#include "GeomObject.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "AABB.hpp"
#include <vector>

class Scene {
public:

	class bvh_node {
	public:
		bvh_node* left;
		bvh_node* right;
		std::vector<GeomObject *> objs;
		
		AABB aabb;
	};

	Scene();

	Camera *camera;
	std::vector<Light *> lights;
	std::vector<GeomObject *> objects;
	bool sds;
	bvh_node* rootNode;

	Ray castRay(int width, int height, int x, int y, int ssM, int ssN, int superSamples);
	
	//AABB methods
	void sort(std::vector<GeomObject *> objects, int axis);
	void recursiveTreeBuild(std::vector<GeomObject *> objects, int axis, bvh_node *parent);
	void instantiateAABB(bvh_node* parent);
	GeomObject* traverseTree(bvh_node *node, Ray &ray);

	
	void print();

};