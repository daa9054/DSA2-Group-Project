#include "OctTree.h"


OctTree::OctTree(vector3 aOrigin, vector3 aHalfDepth, TargetBoxManager aBoxMngr, int aMaxSize, 
				vector3 aMinOct, vector3 aMaxOct)
{
	origin = aOrigin;
	halfDepth = aHalfDepth;
	boxMngr = aBoxMngr;
	maxPerOctant = aMaxSize;
	minOct = aMinOct;
	maxOct = aMaxOct;
}

OctTree::~OctTree(void)
{
}

std::vector<TargetBox> OctTree::GetListofTargetBoxes(OctTree oct)
{
	std::vector<TargetBox> temp = oct.GetData();
	return temp;
}

vector3 OctTree::GetOrigin()
{
	return origin;
}

void OctTree::SetOrigin(vector3 aOrigin)
{
	origin = aOrigin;
}

vector3 OctTree::GetHalfDepth()
{
	return halfDepth;
}

void OctTree::SetHalfDepth(vector3 depth)
{
	halfDepth = depth;
}

TargetBoxManager OctTree::GetBoxManager()
{
	return boxMngr;
}

std::vector<TargetBox> OctTree::GetData()
{
	return data;
}

int OctTree::GetMaxOctantSize()
{
	return maxPerOctant;
}

void OctTree::SetMaxOctantSize(int size)
{
	maxPerOctant = size;
}

vector3 OctTree::GetMinOct()
{
	return minOct;
}

void OctTree::SetMinOct(vector3 min)
{
	minOct = min;
}

vector3 OctTree::GetMaxOct()
{
	return maxOct;
}

void OctTree::SetMaxOct(vector3 max)
{
	maxOct = max;
}

void OctTree::Insert(TargetBox box)
{
	if(maxOct.x < box.GetPos().x && minOct.x > box.GetPos().x &&
		maxOct.y < box.GetPos().y && minOct.x > box.GetPos().y &&
		maxOct.z < box.GetPos().x && minOct.x > box.GetPos().x)
	{
		if(children.empty == true && data.size() < maxPerOctant)
		{
			data.push_back(box);
		}
	}
}
