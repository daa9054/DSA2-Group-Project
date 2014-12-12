#include "Cannonball.h"

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

//Cannon Constructor loads intial values
Cannonball::Cannonball(void)
{
	position = vector4(0.0f,0.5f,0.0f,0.0f);
	velocity = vector4(0.0f,0.0f,0.0f,0.0f);
	acceleration = vector4(0.0f,0.0f,0.0f,0.0f);
	gravity = vector4(0.0f,-0.005f,0.0f,0.0f);
	netForce = vector4(0.0f,0.0f,0.0f,0.0f);
	isFired = false;
	initialShot = false;
	mass = 1.0f;
}

//Destructor
Cannonball::~Cannonball(void)
{

}

// Getters
vector4 Cannonball::GetPos()
{
	return position;
}
vector4 Cannonball::GetVel()
{
	return velocity;
}
vector4 Cannonball::GetAccel()
{
	return acceleration;
}
bool Cannonball::GetIsFired()
{
	return isFired;
}

// Setters
void Cannonball::SetPos(vector4 pos)
{
	position = pos;
}
void Cannonball::SetVel(vector4 vel)
{
	velocity = vel;
}
void Cannonball::SetAccel(vector4 accel)
{
	acceleration = accel;
}


void Cannonball::SetIsFired(bool pFired)
{
	isFired = pFired;
}

void Cannonball::SetInitialShot(bool pInit)
{
	initialShot = pInit;
}

void Cannonball::AddForce(vector4 forceToAdd)
{
	netForce += forceToAdd;
}

void Cannonball::AddToPosition(vector4 posToAdd)
{
	position += posToAdd;
}

//Movement Logic
void Cannonball::Update()
{
	//Has the player fired the cannon with the space bar?
	if(isFired)
	{
		//add gravity
		AddForce(gravity);

		//divide force by mass to get acceleration
		netForce /= mass;

		//add force to acceleration
		acceleration += netForce;

		//add acceleration to velocity
 		velocity += acceleration;

		//add velocity to position
		position += velocity;

		//reset accleration and netforce 
		netForce = vector4(0.0f,0.0f,0.0f,1.0f);

		acceleration = vector4(0.0f,0.0f,0.0f,1.0f);

	}
	//If Cannonball hits the ground, reset back into cannon's chamber
	if(position.y < 0.0f)
	{
		isFired = false;
		position = vector4(0.0f, 0.5f, 0.0f, 1.0f);
		acceleration = vector4(0.0f,0.0f,0.0f,1.0f);
		velocity = vector4(0.0f,0.0f,0.0f,1.0f);
		netForce = vector4(0.0f,0.0f,0.0f,1.0f);
	}
}


