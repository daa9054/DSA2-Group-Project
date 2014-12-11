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
	shouldReset = true;
	for(int i = 0; i < boxes.size(); i++)
	{
		boxes[i].Update();
		if(boxes[i].onGround == false)
		{
			shouldReset = false;
		}
	}
	if(shouldReset == true)
	{
		for(int i = 0; i < boxes.size(); i++)
		{
			boxes[i].position = boxes[i].startPos;
			boxes[i].onGround = false;
		}
		shouldReset = true;
	}
}

void TargetBoxManager::ResetBoxes()
{
	for(int i = 0; i < boxes.size(); i++)
	{
		float x = (rand() % 20) - 10.0f;
		float y = (rand() % 5) + 1.0f;
		float z = (rand() % 20) - 30.0f;
		if(z < -8.0f)
		{
			z = -8.0f;
		}
		boxes[i].startPos = vector4(x, y, z, 0.0f);
		boxes[i].position = boxes[i].startPos;
		boxes[i].isHit = false;
		boxes[i].onGround = false;
		boxes[i].isDestroyed = false;
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
	//std::cout << "Bounce Off Target Box Manager" << std:: endl;
}