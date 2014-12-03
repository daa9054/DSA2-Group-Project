#include "CannonManager.h"


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

void CannonManager::SetPower(float newPower)
{
	powerScalar = newPower;
	if(powerScalar > 0.25f)
	{
		powerScalar = 0.25f;
	}
}

vector4 CannonManager::CalculateForce()
{
	vector4 cannonForce = vector4(0.0f,0.0f,0.0f,1.0f);	
	cannonForce = glm::normalize(heading);
	cannonForce *= powerScalar * 0.1;
	//matrix4 rotateX = glm::rotate(matrix4(1.0f), 180.0f, vector3(1.0f,0.0f,0.0f));
	//matrix4 rotateY = glm::rotate(matrix4(1.0f), 41.0f, vector3(0.0f,1.0f,0.0f));
	//cannonForce.z *= -1.0f;
	//cannonForce = rotateY * cannonForce;

	std::cout<<"CannonForce X: " << cannonForce.x << " Y: " << cannonForce.y << " Z: " << cannonForce.z << std::endl;

	return cannonForce;
}

void CannonManager::Fire()
{
	//if(ball.GetFired() == false)
	//{
	//	vector4 cannonForce =  CalculateForce();
	//	//ball.SetFired(True);
	//	//ball.Addforce(cannonForce);
	//}

	if(ball.GetIsFired() == false)
	{
		vector4 cannonForce =  CalculateForce();
		ball.SetIsFired(true);
		//ball.SetInitialShot(true);
		ball.AddForce(cannonForce);
	}
}

void CannonManager::Update()
{
	ball.Update();
}

vector4 CannonManager::GetBallPos()
{
	return ball.GetPos();
}

CannonManager::~CannonManager(void)
{
}
