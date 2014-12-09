#include "TargetBox.h"


TargetBox::TargetBox(int boxNum, vector4 startingPos)
{
	boxNumber = boxNum;
	position = startingPos;
	isDestroyed = false;
	isHit = false;
	onGround = false;
	mass = 1.0f;
	coefficientOfFriction = 20.0f; 

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
		acceleration += gravity;

		//Apply friction
		if(onGround)
		{
			float xVel = velocity.x;
			float zVel = velocity.z;
			vector4 friction = glm::normalize(velocity);

			friction *= -1.0f;
			friction * coefficientOfFriction;

			if(zVel < 0)
			{
				zVel *= -1.0f;
			}

			if(zVel < 0.09f && xVel < 0.09f)
			{
				velocity *= 0.0f;
			}
			else
			{
				AddForce(friction);
			}

			std::cout << "Velocity X: " << xVel << "\nVelocity Z: " << zVel <<std::endl;
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


