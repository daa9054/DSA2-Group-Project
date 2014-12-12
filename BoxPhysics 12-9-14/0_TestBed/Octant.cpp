#include "Octant.h"

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

//Constuctor, Loads intial values
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

//Destructor
Octant::~Octant(void)
{
	Release();
}

//Releases any allocated memory when destructor is called
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

//Sets boungbox to visible and calls render
//if the octant has children (isLeaf == false) 
//call the render fuction of the children
void Octant::Render()
{
	bo->SetVisible(true);
	bo->SetVisibleBS(false);
	bo->Render();

	if(isLeaf == false)
	{
		for(int i = 0; i < 8; i++)
		{
			children[i]->Render();
		}
	}

}

