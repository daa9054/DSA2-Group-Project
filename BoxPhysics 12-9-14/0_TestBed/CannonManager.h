#pragma once
#include "ME\MyEngine.h"
#include "Cannonball.h"
#include "TargetBox.h"
#include <SFML\Graphics.hpp>
#include <chrono>

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

using namespace MyEngine;
class CannonManager
{
public:
	//Constructor
	CannonManager(void);
	//Destructor
	~CannonManager(void);
	
	//Getters and Setters
	vector4 GetPos();
	void SetPos(vector4 newPos);

	vector4 GetHeading();
	void SetHeading(vector4 newHeading);

	float GetPitch();
	void SetPitch(float newPitch);

	float GetYaw();
	void SetYaw(float newYaw);

	float GetPower();
	void SetPower(float newPower);

	//Calculates the Cannon Force based on Cannon's Z Heading vector
	vector4 CalculateForce();
	//Triggers the fire command by passing cannon force onto cannonball
	void Fire();
	void Update();

	//More Getters
	vector4 GetBallPos();
	Cannonball GetBall();

	//Physics
	void BounceOff();

private:

	//member variables
	matrix4 world;
	vector4 position;
	vector4 heading;
	Cannonball ball;
	float pitch;
	float yaw;
	float powerScalar;
};

