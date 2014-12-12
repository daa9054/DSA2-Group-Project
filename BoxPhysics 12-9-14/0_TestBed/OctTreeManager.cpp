#include "OctTreeManager.h"

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

//Constructor, sets intial values and generates intial oct tree
OctTreeManager::OctTreeManager(ModelManagerSingleton* mm)
{
	maxBeforeSubDivide = 2;
	maxLevels = 3;
	numOctants = 0;

	m_pModelMnger = mm;
	GenerateOctTree();
}

//Destructor
OctTreeManager::~OctTreeManager(void)
{
	Release();
}

//Calls Root Octant Render function which recursively calls the children
void OctTreeManager::Render()
{
	root->Render();
}

//releases any allocated memory when created
void OctTreeManager::Release()
{
	delete root;
	root = nullptr;
	m_pModelMnger = nullptr;

	for(unsigned int i = 0; i < instances.size(); i++)
	{
		instances[i] = nullptr;
	}
	for(unsigned int i = 0; i < boundingObjects.size(); i++)
	{
		boundingObjects[i] = nullptr;
	}
}

//Helper method to see if an octant's bouningobject is colliding with
//an instance bounding object
//Used for traversal, insertion, and division
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

//Adds a data bounding object to a octant and then decides where it needs to go
void OctTreeManager::Insert(Octant& oct, BoundingObjectClass& box, int lvl)
{
	//if the octant stores the box
	if(Contains(oct, box) == true)
	{
		//if the octant has no children and has room to store box
		//add to data list
		if(oct.isLeaf == true && oct.data.size() < maxBeforeSubDivide)
		{
			oct.data.push_back(&box);
		}
		//if the octant has no children but has reached the limit of its capacity
		//add to list and then divide the octant and progate data down
		else if(oct.isLeaf == true && oct.data.size() >= maxBeforeSubDivide)
		{
			oct.data.push_back(&box);
			Divide(oct, lvl);
		}
		//if the octant has children already
		else if(oct.isLeaf == false)
		{
			//check each children and insert the box into those that contain the box
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

//Subdivides octant into eight section and passes data into 
//the approriate location in space
void OctTreeManager::Divide(Octant& oct, int level)
{
	//Check to see already divided already
	if(oct.isLeaf == true)
	{
		//increment id counter
		//find new origin for each octant in space based on size and origin position
		//create new children
		//increment total octant counter
		nID++;
		vector3 origin1 = vector3(oct.origin.x + (oct.size)/4.0f,
									oct.origin.y + (oct.size)/4.0f,
									oct.origin.z - (oct.size)/4.0f);
		oct.children[0] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin1);
		numOctants++;

		nID++;
		vector3 origin2 = vector3(oct.origin.x - (oct.size)/4.0f,
									oct.origin.y + (oct.size)/4.0f,
									oct.origin.z - (oct.size)/4.0f);
		oct.children[1] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin2);
		numOctants++;

		nID++;
		vector3 origin3 = vector3(oct.origin.x - (oct.size)/4.0f,
									oct.origin.y + (oct.size)/4.0f,
									oct.origin.z + (oct.size)/4.0f);
		oct.children[2] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin3);
		numOctants++;

		nID++;
		vector3 origin4 = vector3(oct.origin.x + (oct.size)/4.0f,
									oct.origin.y + (oct.size)/4.0f,
									oct.origin.z + (oct.size)/4.0f);
		oct.children[3] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin4);
		numOctants++;

		nID++;
		vector3 origin5 = vector3(oct.origin.x + (oct.size)/4.0f,
									oct.origin.y - (oct.size)/4.0f,
									oct.origin.z - (oct.size)/4.0f);
		oct.children[4] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin5);
		numOctants++;

		nID++;
		vector3 origin6 = vector3(oct.origin.x - (oct.size)/4.0f,
									oct.origin.y - (oct.size)/4.0f,
									oct.origin.z - (oct.size)/4.0f);
		oct.children[5] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin6);
		numOctants++;

		nID++;
		vector3 origin7 = vector3(oct.origin.x - (oct.size)/4.0f,
									oct.origin.y - (oct.size)/4.0f,
									oct.origin.z + (oct.size)/4.0f);
		oct.children[6] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin7);
		numOctants++;

		nID++;
		vector3 origin8 = vector3(oct.origin.x + (oct.size)/4.0f,
									oct.origin.y - (oct.size)/4.0f,
									oct.origin.z + (oct.size)/4.0f);
		oct.children[7] = new Octant(true,level + 1,nID,(oct.size/2.0f), oct , origin8);
		numOctants++;

		//finnally set the octants parent status so it is not subdivided multiple times
		oct.isLeaf = false;

		//for each child
		for(int i = 0; i < 8; i++)
		{
			//for each bounding object in data list
			for(unsigned int j = 0; j < oct.data.size(); j++)
			{
				//grab current child
				Octant& child = *oct.children[i];
				//grab current box
				BoundingObjectClass& box = *oct.data[j];
				//if box exists in child
				if(Contains(child, box) == true)
				{
					//add data to child's data list
					child.data.push_back(&box);
					//remove data from parent's data list
					oct.data.erase(oct.data.begin() + j);
				}
			}
		}

	}
}

//Returns list of octant ids that each instance's object exists inside
std::vector<int> OctTreeManager::TraverseOctTree(Octant& oct, BoundingObjectClass& box)
{
	//create an empty list to return 
	std::vector<int> octantIDList = std::vector<int>();
	if(Contains(oct, box) == true)
	{
		//If it is leaf it means we've reached lowest level of
		//Oct Tree so add this octant to list
		if(oct.isLeaf == true)
		{
			octantIDList.push_back(oct.id);
		}
		//If is not a leaf it has children so we need to recursively check them
		else if(oct.isLeaf == false)
		{
			//used if we wanted to know parent's ids as well
			//octantIDList.push_back(oct.id);

			//for each child recursively traverse to see if octant contains bounding obj
			for(int i = 0; i < 8; i++)
			{
				//create temp vector for recursion to store into
				std::vector<int> temp;
				//grab current child
				Octant& child = *oct.children[i];
				//traverse the child's data list
				temp  = TraverseOctTree(child, box);
				//if temp list pulled back something
				if(temp.empty() == false)
				{
					//add each component to the total id list
					for(unsigned int i = 0; i < temp.size(); i++)
					{
						octantIDList.push_back(temp[i]);
					}
				}
			}
		}
	}

	return octantIDList;
}

//calculates the root size and origin based on scenes total instances
void OctTreeManager::CalculateIntialSize()
{
	//take average position of all objects
	rootOrigin = vector3(0.0f,0.0f,0.0f);
	for(unsigned int i = 0; i < boundingObjects.size(); i++)
	{
		rootOrigin += boundingObjects[i]->GetCentroidGlobal();
	}
	rootOrigin /= boundingObjects.size();

	//set size large enough to fit scene
	rootSize = 30.0f;

	//used if we wanted more percise octTree sizing
	//for(int i = 0; i < boundingObjects.size(); i++)
	//{
	//	vector3 object = boundingObjects[i]->GetCentroidGlobal();
	//	//vector3 minObjPos = boundingObjects[i]->
	//	vector3 minObjPos = vector3(object.x - boundingObjects[i]->GetRadius(), object.y - boundingObjects[i]->GetRadius(), object.z - boundingObjects[i]->GetRadius());
	//	vector3 maxObjPos = vector3(object.x + boundingObjects[i]->GetRadius(), object.y + boundingObjects[i]->GetRadius(), object.z + boundingObjects[i]->GetRadius());

	//	/*std::cout<< "MinObject: X: " << minObjPos.x << " Y: " << minObjPos.y << " Z: " << minObjPos.z << std::endl;
	//	std::cout<< "MaxObject: X: " << maxObjPos.x << " Y: " << maxObjPos.y << " Z: " << maxObjPos.z << std::endl;*/

	//	if(glm::distance(rootOrigin, maxObjPos) > rootSize)
	//	{
	//		rootSize = glm::distance(rootOrigin, maxObjPos);
	//	}
	//	if(glm::distance(rootOrigin, minObjPos) > rootSize)
	//	{
	//		rootSize = glm::distance(rootOrigin, minObjPos);
	//	}
	//}
}

//Generate Oct Tree based on scenes current state
void OctTreeManager::GenerateOctTree()
{
	//reset counters
	nID = 0;
	numOctants = 0;

	//clear instance lists
	instances.clear();
	boundingObjects.clear();

	//add lists of instances and bounding boxes to managers lists
	int numInstances = m_pModelMnger->GetNumberOfInstances();
	for(int i = 0; i < numInstances; i++)
	{
		InstanceClass* instance = m_pModelMnger->GetInstanceByIndex(i);
		instances.push_back(instance);
		boundingObjects.push_back(instance->GetGrandBoundingObject());
	}

	//set root size and origin
	CalculateIntialSize();

	//create root octant with the intial values
	root = new Octant(true, 1, 0, rootSize, *root, rootOrigin );

	//Wanted to use so that our size can dynamically change
	//But, the method Alberto provide breaks the program so its use was scrapped
	//root->bo->Reinitialize(boundingObjects);

	//increment the number of octants with the addition of the root node
	numOctants++;
	
	//start adding bounding objects to the root which will progate the data down the scene
	for(unsigned int i = 0; i < boundingObjects.size(); i++)
	{
		Insert(*root, *boundingObjects[i], 1);
	}

	//After Oct Tree is Generated, add the octant id lists to each instance 
	//to optimize collision detection
	for(unsigned int i = 0; i < instances.size(); i++)
	{
		instances[i]->SetOctantList(TraverseOctTree(*root, *boundingObjects[i]));
	}
}


