#include "ApplicationClass.h"

//Modified By: David Amata, Joe Coppola, and Derek Lescarbeau
//Date: Novmber 18th - December 12, 2014

void ApplicationClass::InitAppVariables()
{
	//Load in Cannon Model First
	m_pModelMngr->LoadModel("Cannon.obj", "Cannon", glm::translate(matrix4(1.0f), vector3(0.0f, 0.5f, 0.0f)));

	//Load in Target Boxes Intially at random position in front of Cannon
	//Add them into TargetBox Manager
	for(int i = 0; i < 10; i++)
	{
		float x = (rand() % 20) - 10.0f;
		float y = rand() % 5;
		float z = (rand() % 20) - 20.0f;
		m_pModelMngr->LoadModel("TargetBox.obj", "TargetBox", glm::translate(matrix4(1.0f), vector3(x, y, z))); // vector3(0, i+3, -i-3)
		tbMnger.AddBox(TargetBox(i,vector4(x, y, z, 1.0f)));
	}

	//Load in Cannonball Model
	m_pModelMngr->LoadModel("CannonBall.obj", "Ball", glm::translate(matrix4(1.0f), vector3(0.0f, 0.5f, 0.0f)));

	//Create the OctTree Manager
	octTreeMnger = new OctTreeManager(m_pModelMngr);
}
void ApplicationClass::Update (void)
{
	m_pSystem->UpdateTime(); //Update the system

	//The following section will position the light source and the lightbulb
#pragma region Update Light Position
	float fHeight = 2.0f;
	float radius = 1.5f;
	static float theta = static_cast<float> (PI + PI / 4.0);
	theta += 0.01f;
	if(theta > PI * 2)
		theta = 0.0f;

	vector3 position = vector3(	static_cast<GLfloat>(cos(theta)) * radius,	fHeight, -static_cast<GLfloat>(sin(theta)) * radius);
	m_pLightMngr->SetPosition(position);
	m_pLightBulb->SetModelMatrix(glm::translate(matrix4(1.0), m_pLightMngr->GetLight()->Position)); //update cube position at light position
#pragma endregion

	m_pModelMngr->Update(true); //Update the model manager (need to be called every update call, this is how you update your model positions and such.)
	
	//The following section will position the camera
#pragma region first person and arcball position
	//Arcball rotation
	if(m_bArcBall == true)
		ArcBall();

	//First person camera movement
	if(m_bFPC == true)
		CameraRotation();
#pragma endregion

	m_pModelMngr->SetShaderProgramByName("All", "Original");
	
	std::vector<vector4> vCollisionList = m_pModelMngr->GetCollisionList();
	int nListSize = static_cast<int> (vCollisionList.size());
	for(int n = 0; n < nListSize; n++)
	{
		vector4 entry = vCollisionList[n];

		if(entry.x == 11 || entry.z == 11)
		{
			//do nothing as nothing should collide with the cannon
		}
		//entry 10 is the cannonball
		//only care about entry x because we do not want duplicate responses
		else if(entry.x == 10)
		{
			m_pModelMngr->SetShaderProgramByNumber(static_cast<int>(entry.x),static_cast<int>(entry.y), "GrayScale");

			//Bouncing the ball and Target Box upon collsiion
			if(tbMnger.GetBoxes()[entry.z].isHit == false)
			{
				cMnger.BounceOff();
				tbMnger.BounceOff(entry.z, cMnger.GetBall());
				//tbMnger.GetBoxes()[entry.z].isHit = true;
			}
		}
	}

	//Updates Cannon logic
	vector4 cannonVec4 = vector4(0.0f,0.0f,-1.0f,0.0f);
	cannonVec4 = m_pModelMngr->GetModelMatrix("Cannon") * cannonVec4;
	cMnger.SetHeading(cannonVec4);
	cMnger.Update();

	//Set the balls position based on its movement
	m_pModelMngr->SetModelMatrix(glm::translate(matrix4(1.0f), static_cast<vector3>(cMnger.GetBallPos())), "Ball");
	
	//updates the target boxes
	tbMnger.Update();
	//Handles the positioning of Target Box modle positions
	for(int i = 0; i < 10; i++)
	{
		if (i == 0)
		{
			m_pModelMngr->SetModelMatrix(glm::translate(matrix4(1.0f), static_cast<vector3>(tbMnger.GetBoxes()[i].GetPos())), i);
		}
		if (i > 0)
		{
			m_pModelMngr->SetModelMatrix(glm::translate(matrix4(1.0f), static_cast<vector3>(tbMnger.GetBoxes()[i].GetPos())), i);
		}
	}

	//Generate OctTree based on scene's current state.
	octTreeMnger->GenerateOctTree();
	printf("FPS: %d \r", m_pSystem->FPS);//print the Frames per Second
}