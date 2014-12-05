#include "Cannonball.h"

Cannonball::Cannonball(void)
{
	position = vector4(0.0f,0.5f,0.0f,0.0f);
	velocity = vector4(0.0f,0.0f,0.0f,0.0f);
	acceleration = vector4(0.0f,0.0f,0.0f,0.0f);
	gravity = vector4(0.0f,-0.0001f,0.0f,0.0f);
	netForce = vector4(0.0f,0.0f,0.0f,0.0f);
	isFired = false;
	initialShot = false;
}

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

void Cannonball::Update()
{
	if(isFired)
	{
		AddForce(gravity);

		acceleration += netForce;

		velocity += acceleration;

		position += velocity;

		netForce = vector4(0.0f,0.0f,0.0f,1.0f);

		//std::cout<< "Ball Pos X: << " << position.x << " Y: " << position.y << " Z: " << position.z << std::endl;
	}
	if(position.y < 0.0f)
	{
		//position =
		//Get managers position
		isFired = false;
		position = vector4(0.0f, 0.5f, 0.0f, 1.0f);
		acceleration = vector4(0.0f,0.0f,0.0f,1.0f);
		velocity = vector4(0.0f,0.0f,0.0f,1.0f);
		netForce = vector4(0.0f,0.0f,0.0f,1.0f);
	}
}

// Calculates the projectile motion physics for the cannonball
