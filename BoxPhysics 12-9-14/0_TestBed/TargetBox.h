#pragma once
#include "ME\MyEngine.h"

#include <SFML\Graphics.hpp>
#include <chrono>
class TargetBox
{
public:
	TargetBox(int boxNum, vector4 startingPos);
	~TargetBox(void);

	vector4 GetPos();
	void SetPos(vector4 newPos);

	int GetBoxNumber();
	void SetBoxNumber(int newNum);

	bool GetIfDestroyed();
	void SetIfDestroyed(bool newIsDestroyed);

	void CollisionResponse();
	void Update();
	void AddForce(vector4 force);

	bool isHit;
	bool onGround;
	bool isDestroyed;
	vector4 position;
	int boxNumber;
	float mass;
	float coefficientOfFriction;
	
	vector4 netForce;
	vector4 acceleration;
	vector4 velocity;
	vector4 gravity;

	vector4 startPos;

private:


};

