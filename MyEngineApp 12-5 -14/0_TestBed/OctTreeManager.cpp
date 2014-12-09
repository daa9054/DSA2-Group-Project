#include "OctTreeManager.h"


OctTreeManager::OctTreeManager(void)
{
	m_pModelMnger = ModelManagerSingleton::GetInstance();
	int numInstances = m_pModelMnger->GetNumberOfInstances();
	for(int i = 0; i < numInstances; i++)
	{
		InstanceClass* instance = m_pModelMnger->GetInstanceByIndex(i);
		instances.push_back(instance);
		boundingObjects.push_back(instance->GetGrandBoundingObject());
	}
	//GenerateOctTree();
}


OctTreeManager::~OctTreeManager(void)
{
	Release();
}

void OctTreeManager::Render()
{
	root->Render();
}

void OctTreeManager::Release()
{
	delete root;
	root = nullptr;
}

bool OctTreeManager::Contains(Octant& oct, BoundingObjectClass& box)
{
	if(oct.bo->IsColliding(box))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void OctTreeManager::Insert(Octant& oct, BoundingObjectClass& box, int lvl)
{
	if(Contains(oct, box) == true)
	{
		if(oct.isLeaf == true && oct.data.size() < maxBeforeSubDivide)
		{
			oct.data.push_back(&box);
		}
		else if(oct.isLeaf == true && oct.data.size() >= maxBeforeSubDivide)
		{
			oct.data.push_back(&box);
			Divide(oct, lvl);
		}
		else if(oct.isLeaf == false)
		{
			for(int i = 0; i < 8; i++)
			{
				Octant& child = *oct.children[i];
				if(Contains(child,box) == true)
				{
					Insert(child, box, lvl + 1);
				}
			}
		}
	}
}

void OctTreeManager::Divide(Octant& oct, int level)
{
	if(oct.isLeaf == true)
	{
		vector3 origin1 = vector3((oct.origin.x + oct.size)/2.0f,
									(oct.origin.y + oct.size)/2.0f,
									(oct.origin.z - oct.size)/2.0f);
		oct.children[0] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin1);
		nID++;

		vector3 origin2 = vector3((oct.origin.x - oct.size)/2.0f,
									(oct.origin.y + oct.size)/2.0f,
									(oct.origin.z - oct.size)/2.0f);
		oct.children[1] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin2);
		nID++;

		vector3 origin3 = vector3((oct.origin.x - oct.size)/2.0f,
									(oct.origin.y + oct.size)/2.0f,
									(oct.origin.z + oct.size)/2.0f);
		oct.children[2] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin3);
		nID++;

		vector3 origin4 = vector3((oct.origin.x + oct.size)/2.0f,
									(oct.origin.y + oct.size)/2.0f,
									(oct.origin.z + oct.size)/2.0f);
		oct.children[3] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin4);
		nID++;

		vector3 origin5 = vector3((oct.origin.x + oct.size)/2.0f,
									(oct.origin.y - oct.size)/2.0f,
									(oct.origin.z - oct.size)/2.0f);
		oct.children[4] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin5);
		nID++;

		vector3 origin6 = vector3((oct.origin.x - oct.size)/2.0f,
									(oct.origin.y - oct.size)/2.0f,
									(oct.origin.z - oct.size)/2.0f);
		oct.children[5] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin6);
		nID++;

		vector3 origin7 = vector3((oct.origin.x - oct.size)/2.0f,
									(oct.origin.y - oct.size)/2.0f,
									(oct.origin.z + oct.size)/2.0f);
		oct.children[6] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin7);
		nID++;

		vector3 origin8 = vector3((oct.origin.x + oct.size)/2.0f,
									(oct.origin.y - oct.size)/2.0f,
									(oct.origin.z + oct.size)/2.0f);
		oct.children[7] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin8);
		nID++;

		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < oct.data.size(); j++)
			{
				Octant& child = *oct.children[i];
				BoundingObjectClass& box = *oct.data[j];
				if(Contains(child, box) == true)
				{
					child.data.push_back(&box);
					oct.data.erase(oct.data.begin() + j);
				}
			}
		}

	}
}

std::vector<int> OctTreeManager::TraverseOctTree(Octant& oct, BoundingObjectClass& box)
{

	static std::vector<int> octantIDList;
	if(Contains(oct, box) == true)
	{
		if(oct.isLeaf == true)
		{
			octantIDList.push_back(oct.id);
		}
		else if(oct.isLeaf == false)
		{
			for(int i = 0; i < 8; i++)
			{
				std::vector<int> temp;
				Octant& child = *oct.children[i];
				temp  = TraverseOctTree(child, box);
				if(temp.empty() == false)
				{
					for(int i = 0; i < temp.size(); i++)
					{
						octantIDList.push_back(temp[i]);
					}
				}
			}
		}
	}

	return octantIDList;
}

void OctTreeManager::CaluclateIntialSize()
{
	rootSize = 0.0f;
	for(int i = 0; i < boundingObjects.size(); i++)
	{
		vector3 object = boundingObjects[i]->GetCentroidGlobal();
	}
}


