#pragma once
#include "ME\MyEngine.h"
#include <SFML\Graphics.hpp>
#include <chrono>

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

class Octant
{
public:
	//variables

	//bool to see if octants contain any data members
	bool isEmpty;
	//checks to see if octant has children
	bool isLeaf;

	//what subdivision
	int level;
	//individualized octant id number used for traversal
	int id;

	//centroid of the octant bounding box
	vector3 origin;
	//szie of the bounding box
	float size;

	//pointer to the parent class
	Octant* parent;
	//pointers to subdivision children
	Octant* children[8];

	//list of bounding boxes of instances in scene that are contained in octant
	std::vector<BoundingObjectClass*> data;

	//bounding box of the octant
	BoundingObjectClass* bo;

	//Methods
	//Constuctor
	Octant(bool IL, int lvl, int ID, float siz, Octant &par, vector3 org);
	//Destructor
	~Octant(void);

	//calls the render of the bouning bound and then its children if they exist
	void Render();
	//release stored memory
	void Release();
	//Swap data with other octant (Unused)
	void Swap(Octant& other);
};

