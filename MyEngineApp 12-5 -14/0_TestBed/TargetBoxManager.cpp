#include "TargetBoxManager.h"


TargetBoxManager::TargetBoxManager(void)
{
	boxes = std::vector<TargetBox>();
}


TargetBoxManager::~TargetBoxManager(void)
{
}

void TargetBoxManager::Update()
{
	for(int i = 0; i < boxes.size(); i++)
	{
		boxes[i].Update();
	}
}

std::vector<TargetBox> TargetBoxManager::GetBoxes()
{
	return boxes;
}

int TargetBoxManager::GetNumBoxes()
{
	return boxes.size();
}


void TargetBoxManager::ResetHits()
{
	for(int i = 0; i < boxes.size(); i++)
	{
		boxes[i].isHit = false;
	}
}


void TargetBoxManager::AddBox(TargetBox newBox)
{
	boxes.push_back(newBox);
}

void TargetBoxManager::ClearBoxes()
{
	boxes.clear();
}

void TargetBoxManager::BounceOff(int index, Cannonball ball)
{
	boxes[index].isHit = true;
	vector4 velocity = ball.GetVel();

	//vector4 ballHeading = glm::normalize(velocity);

	//ballHeading *= -10.0f;

	//ball.AddToPosition(ballHeading);

	//velocity *= 1000.0f;
	velocity *= vector4(-1.0f,-1.0f,-1.0f, 1.0f);

	//velocity *= 0.4f;

	boxes[index].AddForce(velocity);
	//boxes[index].velocity = velocity;
	std::cout << "Bounce Off Target Box Manager" << std:: endl;
}