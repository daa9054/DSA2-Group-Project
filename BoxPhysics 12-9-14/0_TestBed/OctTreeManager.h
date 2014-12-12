#pragma once
#include "ME\MyEngine.h"
#include <SFML\Graphics.hpp>
#include <chrono>
#include "Octant.h"

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

class OctTreeManager
{
public:
	//Variables

	//counter for the total number of octants 
	int numOctants;
	//limiter for the number of subdivisions
	int maxLevels;
	//limit of how many objects can be stored in a single octant before subdividing
	unsigned int maxBeforeSubDivide;
	//counter used for assigning individualized octant id numbers
	int nID;
	//pointer to store root octant
	Octant* root;
	
	//pointer to modelmanager in order to retrieve instances in scene
	ModelManagerSingleton* m_pModelMnger;

	//std vectors of the instances in the scene and thier associated bounding objects
	std::vector<InstanceClass*> instances;
	std::vector<BoundingObjectClass*> boundingObjects;

	//size of the root octant's bounding box
	float rootSize;
	//root origin is the centroid of the average of all the instances used for the root octants position
	vector3 rootOrigin;

	//Methods
	//Constructor
	OctTreeManager(ModelManagerSingleton* mm);
	//Destructor
	~OctTreeManager(void);

	//intializes root octant's size and origin based on total instances
	void CalculateIntialSize();

	//creates root node and starts feeding data into which in turn causes things to subdivide
	void GenerateOctTree();

	//calls the root nodes render method which recursively calls the children
	void Render();
	//released allocated memory
	void Release();
	//passes instance data into octant which in turn decides where to store it
	void Insert(Octant& oct, BoundingObjectClass& box, int level);
	//creates subdivisions of an octant and passing data down into children
	void Divide(Octant& oct, int level);
	//helper method to check to see if an octant contains a bouning object
	bool Contains(Octant& oct, BoundingObjectClass& box);
	//After Oct Tree is generated returns list of octant ids and passes them into 
	//instaces to use for collision detection
	std::vector<int> TraverseOctTree(Octant& oct, BoundingObjectClass& box);

};

