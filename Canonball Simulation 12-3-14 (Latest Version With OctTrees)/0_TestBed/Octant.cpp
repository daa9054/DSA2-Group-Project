#include "Octant.h"


Octant::Octant(bool empty, bool leaf, int lvl, int ID, float siz, vector3 org)
{
	isEmpty = empty;
	isLeaf = leaf;
	level = lvl;
	id = ID;
	size = siz;
	origin = org;
}


Octant::~Octant(void)
{
	Release();
}

void Octant::Render()
{

}

void Octant::CalculateCollider()
{

}

void Octant::Release()
{
	delete parent;
	delete [] children;
	delete bo;

	for(int i = 0; i < objectList.size(); i++)
	{
		delete objectList[i];
	}
}

void Octant::Init()
{

}

void Octant::Swap(Octant& other)
{
	std::vector<BoundingObjectClass*> temp1 = objectList;
	std::vector<BoundingObjectClass*> temp2 = other.objectList;
	
	objectList = temp2;
	other.objectList = temp1;
}
