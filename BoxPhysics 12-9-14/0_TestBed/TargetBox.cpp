#include "TargetBox.h"


TargetBox::TargetBox(int boxNum, vector4 startingPos)
{
	boxNumber = boxNum;
	position = startingPos;
	isDestroyed = false;
	isHit = false;
	onGround = false;
	mass = 1.0f;
	coefficientOfFriction = 0.9f; 

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
	if(isHit || onGround)
	{
		AddForce(gravity);

		//Apply friction
		if(onGround)
		{
			vector4 friction = glm::normalize(velocity);

			friction *= -1.0f;
			friction * coefficientOfFriction;

			/*if()
			{
				velocity *= 0.0f;
			}*/

			AddForce(friction);
		}

		netForce /= mass;

		acceleration += netForce;

 		velocity += acceleration;

		position += velocity;

		netForce = vector4(0.0f,0.0f,0.0f,1.0f);

		acceleration = vector4(0.0f,0.0f,0.0f,1.0f);
	}

	if(position.y < 0.0f)
	{
		//Get managers position
		isHit = false;
		onGround = true;
		
		position = vector4(position.x, 0.0, position.z, position.w);
		acceleration = vector4(acceleration.x, 0.0, acceleration.z, acceleration.w);
		velocity = vector4(velocity.x, 0.0, velocity.z, velocity.w);

		/*position = startPos;
		acceleration = vector4(0.0f,0.0f,0.0f,1.0f);
		velocity = vector4(0.0f,0.0f,0.0f,1.0f);
		netForce = vector4(0.0f,0.0f,0.0f,1.0f);*/
	}
}

TargetBox::~TargetBox(void)
{

}


