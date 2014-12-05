#pragma once
#include "ME\MyEngine.h"

#include <SFML\Graphics.hpp>
#include <chrono>

#include "TargetBox.h"
class TargetBoxManager
{
public:
	TargetBoxManager(void);
	~TargetBoxManager(void);

	std::vector<TargetBox> GetBoxes();
	void AddBox(TargetBox newBox);
	void ClearBoxes();
	int GetNumBoxes();


private:
	std::vector<TargetBox> boxes;

};

