#include "ApplicationClass.h"
void ApplicationClass::ProcessKeyboard(void)
{
	static DWORD currentTime = GetTickCount();
	static DWORD lastTime = GetTickCount();
	currentTime = GetTickCount();
	DWORD difference = currentTime - lastTime;

	bool bModifier = false;
	bool spaceDown = false;
	static bool rDown = false;
	float fSpeed = 0.1f;
	int nMesh = m_pModelMngr->IdentifyInstance(m_sSelectedObject);

	int CannonMesh = m_pModelMngr->IdentifyInstance("Cannon");

	int TheBox = m_pModelMngr->IdentifyInstance("TargetBox0");

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		exit(0);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		spaceDown = true;
		cMnger.SetPower(cMnger.GetPower() + 0.0001f * difference);
		//std::cout<< "Power: " << cMnger.GetPower() << std::endl;
	}

	if(spaceDown == false)
	{
		if(cMnger.GetPower() > 0.0f)
		{
			cMnger.Fire();
			tbMnger.ResetHits();
			lastTime = currentTime;
		}
		cMnger.SetPower(0.0f);
	}
	m_pCamera->SetPosition(static_cast<vector3>(cMnger.GetBallPos()) + vector3(0.0f, 2.0f, 4.0f));

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if(rDown == false)
		{
			//std::cout<< "Size of Boxes: " << tbMnger.GetNumBoxes() << std::endl;
			/*for(int i = 0; i < tbMnger.GetNumBoxes(); i++)
			{
				m_pModelMngr->DeleteInstance("TargetBox" + i);
			}
			tbMnger.ClearBoxes();
			for(int i = 0; i < 10; i++)
			{
				float x = (rand() % 20) - 10.0f;
				float y = rand() % 5;
				float z = (rand() % 20) - 20.0f;
				m_pModelMngr->LoadModel("TargetBox.obj", "TargetBox" + i, glm::translate(matrix4(1.0f), vector3(x, y, z)));
				tbMnger.AddBox(TargetBox(i,vector4(x,y,z,1.0f)));
			}*/
			tbMnger.ResetBoxes();

			rDown = true;
		}
	}
	else
	{
		rDown = false;
	}
	//Modifiers
#pragma region Modifiers

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		fSpeed += 1.0f;
		bModifier = true;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		fSpeed += 1.0f;
		bModifier = true;
	}
	
#pragma endregion
	//Model Positioning
#pragma region Model Positioning
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		////matrix4 matrix = glm::translate( m_pModelMngr->GetModelMatrix(m_sSelectedObject), vector3(-0.1f,0.0f,0.0f));
		//matrix4 matrix = glm::translate( matrix4(1.0f), vector3(-0.1f,0.0f,0.0f)) * m_pModelMngr->GetModelMatrix(m_sSelectedObject);
		//m_pModelMngr->SetModelMatrix(matrix, m_sSelectedObject);

		//matrix4 m4Box = m_pModelMngr->GetModelMatrix("TargetBox");
		//m_pModelMngr->SetModelMatrix(glm::translate(m4Box, vector3(-0.1f, 0.0f, 0.0f)), "TargetBox");
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		/*matrix4 matrix = glm::translate( matrix4(1.0f), vector3(0.1f,0.0f,0.0f)) * m_pModelMngr->GetModelMatrix(m_sSelectedObject);
		m_pModelMngr->SetModelMatrix(matrix, m_sSelectedObject);
		matrix4 m4Box = m_pModelMngr->GetModelMatrix("TargetBox");
		m_pModelMngr->SetModelMatrix(glm::translate(m4Box, vector3(0.1f, 0.0f, 0.0f)), "TargetBox");*/
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		matrix4 matrix;
		if(bModifier)
		{
			/*matrix = glm::translate( matrix4(1.0f), vector3(0.0f,0.1f,0.0f)) * m_pModelMngr->GetModelMatrix(m_sSelectedObject);
			matrix4 m4Box = m_pModelMngr->GetModelMatrix("TargetBox");
			m_pModelMngr->SetModelMatrix(glm::translate(m4Box, vector3(0.0f, 0.0f, 0.1f)), "TargetBox");*/
		}
		else
		{
			/*matrix = glm::translate( matrix4(1.0f), vector3(0.0f,0.0f,-0.1f)) * m_pModelMngr->GetModelMatrix(m_sSelectedObject);
			matrix4 m4Box = m_pModelMngr->GetModelMatrix("TargetBox");
		m_pModelMngr->SetModelMatrix(glm::translate(m4Box, vector3(0.0f, 0.1f, 0.0f)), "TargetBox");*/
		}
		
		/*m_pModelMngr->SetModelMatrix(matrix, m_sSelectedObject);*/
		
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		matrix4 matrix;
		if(bModifier)
		{
			/*matrix = glm::translate( matrix4(1.0f), vector3(0.0f,-0.1f,0.0f)) * m_pModelMngr->GetModelMatrix(m_sSelectedObject);
			matrix4 m4Box = m_pModelMngr->GetModelMatrix("TargetBox");
		m_pModelMngr->SetModelMatrix(glm::translate(m4Box, vector3(0.0f, 0.0f, -0.1f)), "TargetBox");*/
		}
		else
		{
			/*matrix = glm::translate( matrix4(1.0f), vector3(0.0f,0.0f,0.1f)) * m_pModelMngr->GetModelMatrix(m_sSelectedObject);
			matrix4 m4Box = m_pModelMngr->GetModelMatrix("TargetBox");
			m_pModelMngr->SetModelMatrix(glm::translate(m4Box, vector3(0.0f, -0.1f, 0.0f)), "TargetBox");*/
		}
		
		//m_pModelMngr->SetModelMatrix(matrix, m_sSelectedObject);
		
	}
#pragma endregion
	//Model Loading
#pragma region Model Loading
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		FileReaderClass pFile;
		String sFileName = pFile.RetriveFileNameFromExplorer(L"OBJ Files (*.obj)\0*.obj\0WRL Files (*.wrl)\0*.wrl\0", L"obj");
		if(sFileName != "")
		{
			m_pModelMngr->DeleteInstance();
			sFileName = pFile.GetFileNameAndExtension(sFileName);
			m_pModelMngr->LoadModel(sFileName, sFileName);
		}
		m_sSelectedObject = sFileName;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		m_pModelMngr->DeleteInstance(m_sSelectedObject);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
	{
		m_pModelMngr->DeleteInstance();//Nuke em all
	}
#pragma endregion
	//Model States
#pragma region Model States
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
	{
		m_pModelMngr->SetNextState( m_sSelectedObject, 0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
	{
		m_pModelMngr->SetNextState( m_sSelectedObject, 1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
	{
		m_pModelMngr->SetNextState( m_sSelectedObject, 2);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
	{
		m_pModelMngr->SetNextState( m_sSelectedObject, 3);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
	{
		m_pModelMngr->SetNextState( m_sSelectedObject, 4);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
	{
		m_pModelMngr->SetNextState( m_sSelectedObject, 5);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
	{
		m_pModelMngr->SetNextState( m_sSelectedObject, 6);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
	{
		m_pModelMngr->SetNextState( m_sSelectedObject, 7);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
	{
		m_pModelMngr->SetNextState( m_sSelectedObject, 8);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
	{
		m_pModelMngr->SetNextState( m_sSelectedObject, 9);
	}
#pragma endregion
	//Debug
#pragma region Debug
	static bool bDebug = false;
	static bool bWasF4Pressed = false; //Was pressed keeps its value for the rest of the program even if it leaves the scope
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F4))//Check the current state to see if its pressed right now
	{
		bWasF4Pressed = true;//if it is flag it
	}
	else if(bWasF4Pressed == true)//if its not currently pressed but it was pressed last...
	{
		bWasF4Pressed = false;//reset the flag
	}

	static bool bWasF5Pressed = false; //Was pressed keeps its value for the rest of the program even if it leaves the scope
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))//Check the current state to see if its pressed right now
	{
		bWasF5Pressed = true;//if it is flag it
	}
	else if(bWasF5Pressed == true)//if its not currently pressed but it was pressed last...
	{
		bDebug = !bDebug;
		m_pModelMngr->SetVisibleGrandBoundingObjectByName(bDebug);
		bWasF5Pressed = false;//reset the flag
	}
	
	static bool bWasF6Pressed = false; //Was pressed keeps its value for the rest of the program even if it leaves the scope
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F6))//Check the current state to see if its pressed right now
	{
		bWasF6Pressed = true;//if it is flag it
	}
	else if(bWasF6Pressed == true)//if its not currently pressed but it was pressed last...
	{
		static bool bAxisVisible = false;
		bAxisVisible = ! bAxisVisible;
		m_pModelMngr->SetVisibleAxis( bAxisVisible, "All", true);
		bWasF6Pressed = false;//reset the flag
	}
#pragma endregion
	//Camera
#pragma region Camera

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//m_pCamera0->MoveForward(fSpeed);
		cMnger.SetYaw(cMnger.GetYaw() + 1.0f);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//m_pCamera0->MoveForward(-fSpeed);
		cMnger.SetYaw(cMnger.GetYaw() - 1.0f);
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//m_pCamera0->MoveSideways(-fSpeed);
		cMnger.SetPitch(cMnger.GetPitch() + 1.0f);
		//if(cMnger.GetPitch() < 60.0f)
		//{
		//	m_pCamera0->Rotate(0.0f, 0.01f);
		//}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{

		//m_pCamera0->MoveSideways(-fSpeed);
		cMnger.SetPitch(cMnger.GetPitch() - 1.0f);
		/*if(cMnger.GetPitch() > -60.0f)
		{
			m_pCamera0->Rotate(0.0f, -0.01f);
		}*/
	}

	matrix4 pitchRotation = glm::rotate(matrix4(1.0f),cMnger.GetPitch(), vector3(0.0f,1.0f,0.0f));
	matrix4 yawRotation = glm::rotate(matrix4(1.0f),cMnger.GetYaw(), vector3(1.0f,0.0f,0.0f));
	matrix4 translation = glm::translate(matrix4(1.0f), vector3(0.0f,0.5f,0.0f));
	matrix4 transform = pitchRotation * yawRotation * translation;
	m_pModelMngr->SetModelMatrix(transform,"Cannon");

	m_pCamera->CalculateView();
#pragma endregion
}
void ApplicationClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;

	static bool bLeft_Released = false;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		bLeft_Released = true;
	}
	else
	{
		if(bLeft_Released == true)
		{
			m_pModelMngr->SetVisibleFrameBoundingObjectByName(false);
			vector2 v2Intersection = m_pModelMngr->ShootRay(	sf::Mouse::getPosition().x,
																sf::Mouse::getPosition().y,
																m_pCamera, false);
			if(v2Intersection.x >= 0 && v2Intersection.y >= 0)
			{
				m_pModelMngr->SetVisibleFrameBoundingObjectByNumber(true, static_cast<int>(v2Intersection.x), static_cast<int>(v2Intersection.y));
				m_sSelectedObject = m_pModelMngr->GetInstanceName(static_cast<int>(v2Intersection.x));
			}
		}
		bLeft_Released = false;
	}
}
void ApplicationClass::ProcessJoystick(void)
{
	sf::Joystick::update();

	int nPad = 0;
	if(sf::Joystick::isConnected(nPad))
	{
		if(sf::Joystick::isButtonPressed(nPad, 4) && sf::Joystick::isButtonPressed(nPad, 5))
			exit(0);

		static float fAngleX = 0.0f;
		static float fAngleY = 0.0f;

		if(sf::Joystick::isButtonPressed(nPad, 8) && sf::Joystick::isButtonPressed(nPad, 9))	
		{
			fAngleX = 0.0f;
			fAngleY = 0.0f;
			m_pCamera->SetPosition(glm::vec3( 0.0f, 0.0f, 10.0f));
		}

		float fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::Y);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera->MoveForward(-fDelta);
		}
		
		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::X);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera->MoveSideways(fDelta);
		}

		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::Z);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera->MoveVertical(fDelta);
		}

		fDelta = -sf::Joystick::getAxisPosition(nPad, sf::Joystick::R);
		if(fDelta > 25 || fDelta < -25)
		{
			fAngleX -= fDelta/10000.0f;
		}
		
		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::U);
		if(fDelta > 25 || fDelta < -25)
		{
			fAngleY -= fDelta/10000.0f;
		}

		m_pCamera->Rotate(fAngleX, fAngleY);
		m_pCamera->CalculateView();
		
	}
}
void ApplicationClass::CameraRotation(float a_fSpeed)
{
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = m_pSystem->WindowX + m_pSystem->WindowWidth / 2;
	CenterY = m_pSystem->WindowY + m_pSystem->WindowHeight / 2;
	
	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);
	
	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	static float fAngleX = 0.0f;
	static float fAngleY = 0.0f;

	if(MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		fAngleY += DeltaMouse * a_fSpeed;
	}
	else if(MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		fAngleY -= DeltaMouse * a_fSpeed;
	}

	if(MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		fAngleX -= DeltaMouse * a_fSpeed;
	}
	else if(MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		fAngleX += DeltaMouse * a_fSpeed;
	}
	m_pCamera->Rotate(fAngleX, fAngleY);
}
void ApplicationClass::ArcBall(float a_fSensitivity)
{
	static matrix4 arcball = matrix4(1.0);
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = m_pSystem->WindowX + m_pSystem->WindowWidth / 2;
	CenterY = m_pSystem->WindowY + m_pSystem->WindowHeight / 2;
	
	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);
	
	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	static float fVerticalAngle = 0.0f;
	static float fHorizontalAngle = 0.0f;

	float fSpeed = 0.001f;

	if(MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, vector3(0.0f, 1.0f, 0.0f));
	}
	else if(MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, vector3(0.0f, 1.0f, 0.0f));
	}

	if(MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, vector3(1.0f, 0.0f, 0.0f));
	}
	else if(MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, vector3(1.0f, 0.0f, 0.0f));
	}
	m_pModelMngr->SetModelMatrix(arcball, m_sSelectedObject, true);
}