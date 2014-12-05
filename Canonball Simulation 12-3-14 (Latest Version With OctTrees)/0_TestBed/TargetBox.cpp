#include "TargetBox.h"


TargetBox::TargetBox(int boxNum, vector4 startingPos)
{
	boxNumber = boxNum;
	position = startingPos;
	isDestroyed = false;

	netForce = vector4(0.0f,0.0f,0.0f,1.0f);
	acceleration = vector4(0.0f,0.0f,0.0f,1.0f);
	velocity = vector4(0.0f,0.0f,0.0f,1.0f);
}

vector4 TargetBox::GetPos()
{
	return position;
}

void TargetBox::SetPos(vector4 newPos)
{
	position = newPos;
}

int TargetBox::GetBoxNumber()
{
	return boxNumber;
}

void TargetBox::SetBoxNumber(int newBoxNum)
{
	boxNumber = newBoxNum;
}


bool TargetBox::GetIfDestroyed()
{
	return isDestroyed;
}

void TargetBox::SetIfDestroyed(bool newIsDestroyed)
{
	isDestroyed = newIsDestroyed;
}

void TargetBox::CollisionResponse()
{
	//Set Color, Visibility, Pass in force
}

void TargetBox::Update()
{
	//Responsive Logic

	//Force Applications
	//Response;

	//AddForce(vector4(0.0f,0.1f,0.0f,1.0f))
	//acceleration
}

void TargetBox::AddForce(vector4 force)
{
	netForce += force;
}

TargetBox::~TargetBox(void)
{
}


