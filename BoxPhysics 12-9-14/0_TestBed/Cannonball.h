#pragma once
#include "ME\MyEngine.h"
#include <SFML\Graphics.hpp>
#include <chrono>

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

using namespace MyEngine;
class Cannonball
{
public:
	//constructor
	Cannonball(void);
	//destructor
	~Cannonball(void);

	//Getters
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

	//Adds force to the ball
	void AddForce(vector4 forceToAdd);
	//Updates the movement logic
	void Update();
	//allows simple movement for the canonball
	void AddToPosition(vector4 posToAdd);

private:
	//member variables
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

