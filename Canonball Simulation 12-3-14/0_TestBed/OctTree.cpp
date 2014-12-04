#include "OctTree.h"


OctTree::OctTree(vector3 aOrigin, TargetBoxManager aBoxMngr, int aMaxSize, 
				vector3 aMinOct, vector3 aMaxOct)
{
	origin = aOrigin;
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
		if(children.empty() == true && data.size() < maxPerOctant)
		{
			data.push_back(box);
		}
		else if(children.empty() == true && data.size() >= maxPerOctant)
		{
			data.push_back(box);
			Divide();
		}
		else if (children.empty() == false)
		{
			for(int i = 0; i < children.size(); i++)
			{
				if(children[i].GetMaxOct().x < box.GetPos().x && children[i].GetMinOct().x > box.GetPos().x &&
					children[i].GetMaxOct().y < box.GetPos().y && children[i].GetMinOct().y > box.GetPos().y &&
					children[i].GetMaxOct().z < box.GetPos().z && children[i].GetMinOct().z > box.GetPos().z)
				{
					children[i].Insert(box);
				}
				else if(data.size() < maxPerOctant)
				{
					data.push_back(box);
				}
			}
		}
	}
}

void OctTree::Divide()
{
	if(children.empty() == true)
	{
		vector3 aMin = vector3(origin.x, origin.y, minOct.z);
		vector3 aMax = vector3(maxOct.x, maxOct.y, origin.z);
		vector3 aOrigin = vector3((origin.x + maxOct.x)/2.0f, (origin.y + maxOct.y)/2.0f, (minOct.z + origin.z)/2.0f);
		children[0] =  OctTree(aOrigin, boxMngr, maxPerOctant, aMin, aMax);

		vector3 bMin = vector3(minOct.x, origin.y, minOct.z);
		vector3 bMax = vector3(origin.x, maxOct.y, origin.z);
		vector3 bOrigin = vector3((origin.x + minOct.x)/2.0f, (origin.y + maxOct.y)/2.0f, (minOct.z + origin.z)/2.0f);
		children[1] =  OctTree(bOrigin, boxMngr, maxPerOctant, bMin, bMax);

		vector3 cMin = vector3(minOct.x, origin.y, origin.z);
		vector3 cMax = vector3(origin.x, maxOct.y, maxOct.z);
		vector3 cOrigin = vector3((origin.x + minOct.x)/2.0f, (origin.y + maxOct.y)/2.0f, (maxOct.z + origin.z)/2.0f);
		children[2] =  OctTree(cOrigin, boxMngr, maxPerOctant, cMin, cMax);

		vector3 dMin = vector3(origin.x, origin.y, origin.z);
		vector3 dMax = vector3(maxOct.x, maxOct.y, maxOct.z);
		vector3 dOrigin = vector3((origin.x + maxOct.x)/2.0f, (origin.y + maxOct.y)/2.0f, (maxOct.z + origin.z)/2.0f);
		children[3] =  OctTree(dOrigin, boxMngr, maxPerOctant, dMin, dMax);

		vector3 eMin = vector3(origin.x, minOct.y, minOct.z);
		vector3 eMax = vector3(maxOct.x, origin.y, origin.z);
		vector3 eOrigin = vector3((origin.x + maxOct.x)/2.0f, (minOct.y + origin.y)/2.0f, (minOct.z + origin.z)/2.0f);
		children[4] =  OctTree(eOrigin, boxMngr, maxPerOctant, eMin, eMax);

		vector3 fMin = vector3(minOct.x, minOct.y, minOct.z);
		vector3 fMax = vector3(origin.x, origin.y, origin.z);
		vector3 fOrigin = vector3((minOct.x + origin.x)/2.0f, (minOct.y + origin.y)/2.0f, (minOct.z + origin.z)/2.0f);
		children[5] =  OctTree(fOrigin, boxMngr, maxPerOctant, fMin, fMax);

		vector3 gMin = vector3(minOct.x, minOct.y, origin.z);
		vector3 gMax = vector3(origin.x, origin.y, maxOct.z);
		vector3 gOrigin = vector3((minOct.x + origin.x)/2.0f, (minOct.y + origin.y)/2.0f, (origin.z + maxOct.z)/2.0f);
		children[6] =  OctTree(gOrigin, boxMngr, maxPerOctant, gMin, gMax);

		vector3 hMin = vector3(origin.x, minOct.y, origin.z);
		vector3 hMax = vector3(maxOct.x, origin.y, maxOct.z);
		vector3 hOrigin = vector3((maxOct.x + origin.x)/2.0f, (minOct.y + origin.y)/2.0f, (maxOct.z + origin.z)/2.0f);
		children[7] =  OctTree(hOrigin, boxMngr, maxPerOctant, hMin, hMax);

		for(int i = 0; i < children.size(); i++)
		{
			for(int j = 0; j < data.size(); j++)
			{
				if(children[i].GetMaxOct().x < data[j].GetPos().x && children[i].GetMinOct().x > data[j].GetPos().x &&
					maxOct.y < box.GetPos().y && minOct.x > box.GetPos().y &&
					maxOct.z < box.GetPos().x && minOct.x > box.GetPos().x)

			}
		}
		


	}

}
