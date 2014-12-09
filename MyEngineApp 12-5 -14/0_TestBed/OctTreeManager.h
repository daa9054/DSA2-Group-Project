#pragma once
#include "ME\MyEngine.h"
#include <SFML\Graphics.hpp>
#include <chrono>
#include "Octant.h"
class OctTreeManager
{
public:
	OctTreeManager(void);
	~OctTreeManager(void);

	int numOctants;
	int maxLevels;
	int maxBeforeSubDivide;
	static int nID;
	Octant* root;

	void CaluclateIntialSize();
};

