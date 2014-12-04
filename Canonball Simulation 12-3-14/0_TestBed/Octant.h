#pragma once
#include "ME\MyEngine.h"
#include <SFML\Graphics.hpp>
#include <chrono>
#include "TargetBoxManager.h"
#include "TargetBox.h"
#include <vector>

class Octant
{
public:

	//varaibles
	bool isEmpty;
	bool isLeaf;

	int level;
	int id;

	float size;

	Octant* parent;
	Octant* children[8];
	BoundingObjectClass* bo;

	vector3 origin;

	std::vector<BoundingObjectClass*> objectList;

	//methods
	Octant(bool empty, bool leaf, int lvl, int ID, float siz, vector3 org);
	~Octant(void);

	void Render();
	void CalculateCollider(void);

private:
	void Release(void);

	void Init(void);

	void Swap(Octant& other);
};

