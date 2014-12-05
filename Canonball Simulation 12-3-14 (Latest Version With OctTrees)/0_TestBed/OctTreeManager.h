#pragma once

#include "ME\MyEngine.h"
#include <SFML\Graphics.hpp>
#include <chrono>
#include "TargetBoxManager.h"
#include "TargetBox.h"
#include <vector>
#include "OctTree.h"

class OctTreeManager
{
public:
	OctTreeManager(void);
	~OctTreeManager(void);

	//OctTree* GetOctant(int id);

	void GenerateOctTree(std::vector<BoundingObjectClass*> boxList, 
		int maxSubtrees = 4, int maxObjects = 2);

	void UpdatePositionInTree(BoundingObjectClass* box);

	void Render();

private:
	int numOctants;
	int maxSubTrees;	
	int maxObjects;
	OctTree* root;

	void Release(void);

	void Init(void);

	void Divide(OctTree* node);
	
};

