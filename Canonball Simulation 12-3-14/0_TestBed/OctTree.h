#pragma once
#include "ME\MyEngine.h"
#include <SFML\Graphics.hpp>
#include <chrono>
#include "TargetBoxManager.h"
#include "TargetBox.h"
#include <vector>

class OctTree
{
public:
	OctTree(vector3 aOrigin, TargetBoxManager aBoxMngr, int aMaxSize,
				vector3 aMinOct, vector3 aMaxOct);
	~OctTree(void);

	bool IsEmpty();
	void Insert(TargetBox box);
	OctTree GetOctantContainingPoint(vector3 point);
	void Divide();
	void Render();

	std::vector<TargetBox> GetListofTargetBoxes(OctTree oct);

	vector3 GetOrigin();
	void SetOrigin(vector3 origin);

	vector3 GetHalfDepth();
	void SetHalfDepth(vector3 depth);

	TargetBoxManager GetBoxManager();

	std::vector<TargetBox> GetData();

	int GetMaxOctantSize();
	void SetMaxOctantSize(int size);

	vector3 GetMinOct();
	void SetMinOct(vector3 min);

	vector3 GetMaxOct();
	void SetMaxOct(vector3 mx);

	std::vector<OctTree*> releaseList;

protected:
	vector3 origin;
	vector3 halfDepth;

	std::vector<OctTree> children;
	TargetBoxManager boxMngr;
	std::vector<TargetBox> data;
	int maxPerOctant;

	vector3 minOct;
	vector3 maxOct;


};

