#pragma once
#include "ME\MyEngine.h"
#include <SFML\Graphics.hpp>
#include <chrono>

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

class TargetBox
{
public:
	//Constructor
	TargetBox(int boxNum, vector4 startingPos);
	//Destructor
	~TargetBox(void);

	//Getters and Setters
	vector4 GetPos();
	void SetPos(vector4 newPos);

	int GetBoxNumber();
	void SetBoxNumber(int newNum);

	bool GetIfDestroyed();
	void SetIfDestroyed(bool newIsDestroyed);

	//Collision Logic for Boxes
	void CollisionResponse();
	//Handles Movement update
	void Update();
	//Adds forces to the boxes for physics based movement
	void AddForce(vector4 force);

	//Variables

	//bool to check if needs to start movement
	//allows us to have floating boxes
	bool isHit;
	//bool for whether boxes is at y = 0;
	bool onGround;
	//bool for destruction (Unused)
	bool isDestroyed;
	//stores position data
	vector4 position;
	//individualized box id number
	int boxNumber;
	//total mass used for physics calculations
	float mass;
	//used to stop box movement
	float coefficientOfFriction;
	
	//movement logic varaibles
	vector4 netForce;
	vector4 acceleration;
	vector4 velocity;
	vector4 gravity;

	//starting position for reset purposes
	vector4 startPos;

private:


};

