#pragma once
#include "ME\MyEngine.h"

#include <SFML\Graphics.hpp>
#include <chrono>

using namespace MyEngine;
class Cannonball
{
public:
	Cannonball(void);
	~Cannonball(void);


	vector4 GetPos();
	vector4 GetVel();
	vector4 GetAccel();
	bool GetIsFired();

	//Setters
	void SetPos(vector4 pos);
	void SetVel(vector4 vel);
	void SetAccel(vector4 accel);
	void SetIsFired(bool pFired);
	void SetInitialShot(bool pInit);
	void AddForce(vector4 forceToAdd);
	void Update();

	void AddToPosition(vector4 posToAdd);

private:
	vector4 position;
	vector4 initialPosition;
	vector4 velocity;
	vector4 acceleration;
	vector4 gravity;
	vector4 netForce;
	bool isFired;
	bool initialShot;
	float mass; 
};

