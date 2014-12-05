#include "TargetBoxManager.h"


TargetBoxManager::TargetBoxManager(void)
{
	boxes = std::vector<TargetBox>();
}


TargetBoxManager::~TargetBoxManager(void)
{
}

std::vector<TargetBox> TargetBoxManager::GetBoxes()
{
	return boxes;
}

int TargetBoxManager::GetNumBoxes()
{
	return boxes.size();
}

void TargetBoxManager::AddBox(TargetBox newBox)
{
	boxes.push_back(newBox);
}

void TargetBoxManager::ClearBoxes()
{
	boxes.clear();
}