#include "OctTreeManager.h"


OctTreeManager::OctTreeManager(ModelManagerSingleton* mm)
{
	maxBeforeSubDivide = 3;
	maxLevels = 3;
	numOctants = 0;

	m_pModelMnger = mm;
	int numInstances = m_pModelMnger->GetNumberOfInstances();
	for(int i = 0; i < numInstances; i++)
	{
		InstanceClass* instance = m_pModelMnger->GetInstanceByIndex(i);
		instances.push_back(instance);
		boundingObjects.push_back(instance->GetGrandBoundingObject());
	}
	GenerateOctTree();
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
	m_pModelMnger = nullptr;

	for(int i = 0; i < instances.size(); i++)
	{
		instances[i] = nullptr;
	}
	for(int i = 0; i < boundingObjects.size(); i++)
	{
		boundingObjects[i] = nullptr;
	}
}

bool OctTreeManager::Contains(Octant& oct, BoundingObjectClass& box)
{
	if(oct.bo->IsColliding(box,false))
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
		nID++;
		vector3 origin1 = vector3((oct.origin.x + oct.size)/2.0f,
									(oct.origin.y + oct.size)/2.0f,
									(oct.origin.z - oct.size)/2.0f);
		oct.children[0] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin1);
		numOctants++;

		nID++;
		vector3 origin2 = vector3((oct.origin.x - oct.size)/2.0f,
									(oct.origin.y + oct.size)/2.0f,
									(oct.origin.z - oct.size)/2.0f);
		oct.children[1] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin2);
		numOctants++;

		nID++;
		vector3 origin3 = vector3((oct.origin.x - oct.size)/2.0f,
									(oct.origin.y + oct.size)/2.0f,
									(oct.origin.z + oct.size)/2.0f);
		oct.children[2] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin3);
		numOctants++;

		nID++;
		vector3 origin4 = vector3((oct.origin.x + oct.size)/2.0f,
									(oct.origin.y + oct.size)/2.0f,
									(oct.origin.z + oct.size)/2.0f);
		oct.children[3] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin4);
		numOctants++;

		nID++;
		vector3 origin5 = vector3((oct.origin.x + oct.size)/2.0f,
									(oct.origin.y - oct.size)/2.0f,
									(oct.origin.z - oct.size)/2.0f);
		oct.children[4] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin5);
		numOctants++;

		nID++;
		vector3 origin6 = vector3((oct.origin.x - oct.size)/2.0f,
									(oct.origin.y - oct.size)/2.0f,
									(oct.origin.z - oct.size)/2.0f);
		oct.children[5] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin6);
		numOctants++;

		nID++;
		vector3 origin7 = vector3((oct.origin.x - oct.size)/2.0f,
									(oct.origin.y - oct.size)/2.0f,
									(oct.origin.z + oct.size)/2.0f);
		oct.children[6] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin7);
		numOctants++;

		nID++;
		vector3 origin8 = vector3((oct.origin.x + oct.size)/2.0f,
									(oct.origin.y - oct.size)/2.0f,
									(oct.origin.z + oct.size)/2.0f);
		oct.children[7] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin8);
		numOctants++;

		oct.isLeaf = false;

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

	std::vector<int> octantIDList = std::vector<int>();
	if(Contains(oct, box) == true)
	{
		if(oct.isLeaf == true)
		{
			octantIDList.push_back(oct.id);
		}
		else if(oct.isLeaf == false)
		{
			octantIDList.push_back(oct.id);
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

	std::cout<< "Oct Tree List: ";
	for(int i = 0; i < octantIDList.size(); i++)
	{
		std::cout << " " << octantIDList[i] << ", ";
	}
	std::cout << std::endl;

	return octantIDList;
}

void OctTreeManager::CalculateIntialSize()
{
	rootOrigin = vector3(0.0f,0.0f,0.0f);
	for(int i = 0; i < boundingObjects.size(); i++)
	{
		rootOrigin += boundingObjects[i]->GetCentroidGlobal();
	}
	rootOrigin /= boundingObjects.size();


	rootSize = 0.0f;
	for(int i = 0; i < boundingObjects.size(); i++)
	{
		vector3 object = boundingObjects[i]->GetCentroidGlobal();
		vector3 minObjPos = object - boundingObjects[i]->GetHalfWidth();
		vector3 maxObjPos = object + boundingObjects[i]->GetHalfWidth();

		if(glm::distance(rootOrigin, maxObjPos) > rootSize)
		{
			rootSize = glm::distance(rootOrigin, maxObjPos);
		}
		if(glm::distance(rootOrigin, minObjPos) > rootSize)
		{
			rootSize = glm::distance(rootOrigin, minObjPos);
		}
	}
}

void OctTreeManager::GenerateOctTree()
{
	nID = 0;
	numOctants = 0;

	CalculateIntialSize();

	root = new Octant(true, 1, 0, rootSize, *root, rootOrigin);
	numOctants++;
	
	for(int i = 0; i < boundingObjects.size(); i++)
	{
		Insert(*root, *boundingObjects[i], 1);
	}

	for(int i = 0; i < instances.size(); i++)
	{
		instances[i]->SetOctantList(TraverseOctTree(*root, *boundingObjects[i]));
	}
}


