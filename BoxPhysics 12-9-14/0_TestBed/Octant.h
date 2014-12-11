#pragma once
#include "ME\MyEngine.h"
#include <SFML\Graphics.hpp>
#include <chrono>

class Octant
{
public:
	//variables
	bool isEmpty;
	bool isLeaf;

	int level;
	int id;

	vector3 origin;
	float size;

	Octant* parent;
	Octant* children[8];

	std::vector<BoundingObjectClass*> data;
	BoundingObjectClass* bo;

	//Methods
	Octant(bool IL, int lvl, int ID, float siz, Octant &par, vector3 org);
	~Octant(void);

	void Render();
	void Release();
	void Swap(Octant& other);
};

