#pragma once
#include "ME\MyEngine.h"
#include "Cannonball.h"
#include "TargetBox.h"


#include <SFML\Graphics.hpp>
#include <chrono>

using namespace MyEngine;
class CannonManager
{
public:
	CannonManager(void);
	~CannonManager(void);
	
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

	vector4 CalculateForce();
	void Fire();
	void Update();

	vector4 GetBallPos();
	Cannonball GetBall();

	//Physics
	void BounceOff();

private:

	matrix4 world;
	vector4 position;
	vector4 heading;
	Cannonball ball;
	float pitch;
	float yaw;
	float powerScalar;
};

