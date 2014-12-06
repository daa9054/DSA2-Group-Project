#include "TargetBox.h"


TargetBox::TargetBox(int boxNum, vector4 startingPos)
{
	boxNumber = boxNum;
	position = startingPos;
	isDestroyed = false;
	isHit = false;
	mass = 1.0f;

	startPos = startingPos;

	netForce = vector4(0.0f,0.0f,0.0f,1.0f);
	acceleration = vector4(0.0f,0.0f,0.0f,1.0f);
	velocity = vector4(0.0f,0.0f,0.0f,1.0f);
	gravity = vector4(0.0f,-0.005f,0.0f,0.0f);

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

void TargetBox::AddForce(vector4 force)
{
	netForce += force;
}

void TargetBox::Update()
{
	if(isHit)
	{
		AddForce(gravity);

		netForce /= mass;

		acceleration += netForce;

 		velocity += acceleration;

		position += velocity;

		netForce = vector4(0.0f,0.0f,0.0f,1.0f);

		acceleration = vector4(0.0f,0.0f,0.0f,1.0f);

		std::cout<< "Box Position X: << " << position.x << " Y: " << position.y << " Z: " << position.z << std::endl;
	}
	if(position.y < 0.0f)
	{
		//Get managers position
		isHit = false;
		position = startPos;
		acceleration = vector4(0.0f,0.0f,0.0f,1.0f);
		velocity = vector4(0.0f,0.0f,0.0f,1.0f);
		netForce = vector4(0.0f,0.0f,0.0f,1.0f);
	}
}

TargetBox::~TargetBox(void)
{

}


