#include "TargetBoxManager.h"

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

//Constructor, creates the intial list of boxes
TargetBoxManager::TargetBoxManager(void)
{
	boxes = std::vector<TargetBox>();
}

//Destructor
TargetBoxManager::~TargetBoxManager(void)
{
}

//Based on all box state decides if position needs to be changed
//calls the update logic for each of the boxes
void TargetBoxManager::Update()
{
	shouldReset = true;
	for(unsigned int i = 0; i < boxes.size(); i++)
	{
		boxes[i].Update();
		if(boxes[i].onGround == false)
		{
			shouldReset = false;
		}
	}
	if(shouldReset == true)
	{
		for(unsigned int i = 0; i < boxes.size(); i++)
		{
			boxes[i].position = boxes[i].startPos;
			boxes[i].onGround = false;
		}
		shouldReset = true;
	}
}

//Resets the status and position of each the boxes positions to a random new location
//in front of the cannon.
void TargetBoxManager::ResetBoxes()
{
	for(unsigned int i = 0; i < boxes.size(); i++)
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

//return the Target Box List
std::vector<TargetBox> TargetBoxManager::GetBoxes()
{
	return boxes;
}

//Returns box list size
int TargetBoxManager::GetNumBoxes()
{
	return boxes.size();
}

//Resets hit status of all the boxes
void TargetBoxManager::ResetHits()
{
	for(unsigned int i = 0; i < boxes.size(); i++)
	{
		boxes[i].isHit = false;
	}
}

//Adds a box to total manager list
void TargetBoxManager::AddBox(TargetBox newBox)
{
	boxes.push_back(newBox);
}

//clears the box list
void TargetBoxManager::ClearBoxes()
{
	boxes.clear();
}

//Handles box bounce logic when collided with a ball
void TargetBoxManager::BounceOff(int index, Cannonball ball)
{
	boxes[index].isHit = true;
	vector4 velocity = ball.GetVel();
	velocity *= vector4(-1.0f,-1.0f,-1.0f, 1.0f);
	boxes[index].AddForce(velocity);
	//std::cout << "Bounce Off Target Box Manager" << std:: endl;
}