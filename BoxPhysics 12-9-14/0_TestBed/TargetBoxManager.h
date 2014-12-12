#pragma once
#include "ME\MyEngine.h"
#include <SFML\Graphics.hpp>
#include <chrono>
#include "TargetBox.h"
#include "Cannonball.h"

//Authors: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

class TargetBoxManager
{
public:
	//Constructor
	TargetBoxManager(void);
	//Destructor
	~TargetBoxManager(void);

	//Getter of all boxes in class
	std::vector<TargetBox> GetBoxes();
	//insert box into list
	void AddBox(TargetBox newBox);
	//clears list for new input
	void ClearBoxes();
	//getter for list of boxes' size
	int GetNumBoxes();
	//resets whether boxes have been hit
	void ResetHits();
	//calls the update of the boxes in list
	void Update();

	//control when it is time to reset box positions and status
	bool shouldReset;

	//resets all boxes to a new starting position 
	void ResetBoxes();

	//bounce logic for ball and target boxes
	void BounceOff(int index, Cannonball ball);


private:
	//list of Target boxes 
	std::vector<TargetBox> boxes;

};

