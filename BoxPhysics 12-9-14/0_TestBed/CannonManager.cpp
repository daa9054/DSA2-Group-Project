#include "CannonManager.h"

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

//Constructor, Loads intial values
CannonManager::CannonManager()
{
	world = matrix4(1.0f);
	position = vector4(0.0f,0.5f,0.0f,1.0f);
	heading  = vector4(0.0f,0.0f,0.0f,1.0f);
	ball = Cannonball();
	pitch = 0.0f;
	yaw = 10.0f;
	powerScalar = 0.0f;
}

//Getters and Setters
Cannonball CannonManager::GetBall()
{
	return ball;
}
vector4 CannonManager::GetPos()
{
	return position;
}

void CannonManager::SetPos(vector4 newPos)
{
	position = newPos;
}

vector4 CannonManager::GetHeading()
{
	return heading;
}

void CannonManager::SetHeading(vector4 newHeading)
{
	heading = newHeading;
}

float CannonManager::GetPitch()
{
	return pitch;
}

//Limits Pitch to Set Range
void CannonManager::SetPitch(float newPitch)
{
	pitch = newPitch;
	
	if(pitch < -60.0f)
	{
		pitch = -60.0f;
	}
	if(pitch > 60.0f)
	{
		pitch = 60.0f;
	}
}

float CannonManager::GetYaw()
{
	return yaw;
}

//Limits Yaw to set range
void CannonManager::SetYaw(float newYaw)
{
	yaw = newYaw;
	if(yaw < 10.0f)
	{
		yaw = 10.0f;
	}
	if(yaw > 85.0f)
	{
		yaw = 85.0f;
	}
}

float CannonManager::GetPower()
{
	return powerScalar;
}

//limits power to a max value
void CannonManager::SetPower(float newPower)
{
	powerScalar = newPower;
	if(powerScalar > 5.0f)
	{
		powerScalar = 5.0f;
	}
}

//Calculates force applied to cannon ball
vector4 CannonManager::CalculateForce()
{
	vector4 cannonForce = vector4(0.0f,0.0f,0.0f,1.0f);	
	cannonForce = glm::normalize(heading);
	cannonForce *= powerScalar * 0.1;

	//std::cout<<"CannonForce X: " << cannonForce.x << " Y: " << cannonForce.y << " Z: " << cannonForce.z << std::endl;

	return cannonForce;
}

//fires cannonball by releasing bools and adding a power force vector
void CannonManager::Fire()
{
	if(ball.GetIsFired() == false)
	{
		vector4 cannonForce =  CalculateForce();
		ball.SetIsFired(true);
		ball.AddForce(cannonForce);
	}
}

//handles collision logic for the cannonball
void CannonManager::BounceOff()
{
	vector4 velocity = ball.GetVel();

	velocity *= vector4(-1.0f,-1.0f,-1.0f, 1.0f);

	velocity *= 0.4f;

	ball.SetVel(velocity);
}

//calls the balls update method
void CannonManager::Update()
{
	ball.Update();
}

//returns the balls current position
vector4 CannonManager::GetBallPos()
{
	return ball.GetPos();
}

//destructor
CannonManager::~CannonManager(void)
{
}
