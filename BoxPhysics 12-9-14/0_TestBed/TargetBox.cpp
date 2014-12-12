#include "TargetBox.h"

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

//Constructor, sets up intial values for box
TargetBox::TargetBox(int boxNum, vector4 startingPos)
{
	boxNumber = boxNum;
	position = startingPos;
	isDestroyed = false;
	isHit = false;
	onGround = false;
	mass = 1.0f;
	coefficientOfFriction = 15.0f; 

	startPos = startingPos;

	netForce = vector4(0.0f,0.0f,0.0f,1.0f);
	acceleration = vector4(0.0f,0.0f,0.0f,1.0f);
	velocity = vector4(0.0f,0.0f,0.0f,1.0f);
	gravity = vector4(0.0f,-0.005f,0.0f,0.0f);
}

//Getters and Setters
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


//Unused as Update of Application.cpp has to handle collision response call
void TargetBox::CollisionResponse()
{
	//Set Color, Visibility, Pass in force
}

//adds force vector to net
void TargetBox::AddForce(vector4 force)
{
	netForce += force;
}

//update movement physics logic
void TargetBox::Update()
{
	//checks to see if hit or on the ground (y == 0)
	if(isHit || onGround)
	{
		//add accleration to gravity as it is mass indepent of mass
		acceleration += gravity;

		//Apply friction
		if(onGround)
		{
			//friction calculation for when on ground
			float xVel = glm::abs(velocity.x);
			float zVel = glm::abs(velocity.z);

			float speed = glm::sqrt((xVel*xVel) + (zVel*zVel));

			vector4 friction = velocity;

			friction *= -0.07f;
			//friction *= -1.0f

			//sets limits so that box stops sooner
			if(speed <  0.03f)
			{
				velocity *= 0.0f;
			}
			else
			{
				AddForce(friction);
			}

			isHit = false;

			//std::cout << "Speed: " << speed <<std::endl;
		}

		// divide net mass by force to get accleration
		netForce /= mass;

		//add netforce to acceleration
		acceleration += netForce;

		//add acceleration to velocity
 		velocity += acceleration;

		//add velocity to position
		position += velocity;

		//reset force and acceleration
		netForce = vector4(0.0f,0.0f,0.0f,1.0f);

		acceleration = vector4(0.0f,0.0f,0.0f,1.0f);
	}

	//if on ground
	if(position.y < 0.0f)
	{
		//Get managers position
		isHit = false;
		onGround = true;
		
		//slide logic
		position = vector4(position.x, 0.0, position.z, position.w);
		acceleration = vector4(acceleration.x, 0.0, acceleration.z, acceleration.w);
		velocity = vector4(velocity.x, 0.0, velocity.z, velocity.w);
	}
}

//destructor
TargetBox::~TargetBox(void)
{

}


