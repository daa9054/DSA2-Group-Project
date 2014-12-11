#pragma once
#include "ME\MyEngine.h"
#include <SFML\Graphics.hpp>
#include <chrono>
#include "Octant.h"
class OctTreeManager
{
public:
	//Variables
	int numOctants;
	int maxLevels;
	int maxBeforeSubDivide;
	int nID;
	Octant* root;
	
	ModelManagerSingleton* m_pModelMnger;
	std::vector<InstanceClass*> instances;
	std::vector<BoundingObjectClass*> boundingObjects;

	float rootSize;
	vector3 rootOrigin;

	//Methods
	OctTreeManager(ModelManagerSingleton* mm);
	~OctTreeManager(void);
	void CalculateIntialSize();
	void GenerateOctTree();
	void UpdatePositionInTree(BoundingObjectClass& box);
	void Render();
	void Release();
	void Insert(Octant& oct, BoundingObjectClass& box, int level);
	void Divide(Octant& oct, int level);
	Octant& GetOctant(int ID);
	bool Contains(Octant& oct, BoundingObjectClass& box);
	std::vector<int> TraverseOctTree(Octant& oct, BoundingObjectClass& box);

};

