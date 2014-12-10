#include "Octant.h"


Octant::Octant(bool IL, int lvl, int ID, float siz, Octant &par, vector3 org)
{
	isLeaf = IL;
	level = lvl;
	id = ID;
	size = siz;
	parent = &par;
	origin = org;

	bo = new BoundingObjectClass(origin,size);
}


Octant::~Octant(void)
{
	Release();
}

void Octant::Release()
{
	delete parent;
	parent = nullptr;

	delete [] children;
	for(int i = 0; i < 8; i++)
	{
		children[i] = nullptr;
	}

	for(int i = 0; i < data.size(); i++)
	{
		delete data[i];
		data[i] = nullptr;
	}

	delete bo;
	bo = nullptr;
}

void Octant::Render()
{
	bo->SetVisible(true);
	bo->Render();

	if(isLeaf = false)
	{
		for(int i = 0; i < 8; i++)
		{
			children[i]->Render();
		}
	}

}

