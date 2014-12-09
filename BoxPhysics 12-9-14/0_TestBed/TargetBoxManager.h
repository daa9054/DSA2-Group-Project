#pragma once
#include "ME\MyEngine.h"

#include <SFML\Graphics.hpp>
#include <chrono>

#include "TargetBox.h"
#include "Cannonball.h"
class TargetBoxManager
{
public:
	TargetBoxManager(void);
	~TargetBoxManager(void);

	std::vector<TargetBox> GetBoxes();
	void AddBox(TargetBox newBox);
	void ClearBoxes();
	int GetNumBoxes();
	void ResetHits();
	void Update();

	bool shouldReset;

	void ResetBoxes();

	void BounceOff(int index, Cannonball ball);


private:
	std::vector<TargetBox> boxes;

};

