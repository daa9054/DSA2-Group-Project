/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/10
*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_
#pragma warning(disable:4251)

#include "ME\MyEngine.h"
#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"
#include "CannonManager.h"
#include "TargetBoxManager.h"
#include "OctTreeManager.h"

#include <SFML\Graphics.hpp>
#include <chrono>

//#include <vld.h>

using namespace MyEngine;

class ApplicationClass
{
	bool m_bFPC;
	bool m_bArcBall;
	bool m_bForceNewConfig;

	int m_nCubes;

	//MeshClass* m_pMesh;
	static ApplicationClass* m_pInstance;
	SystemSingleton* m_pSystem;
	GLSystemSingleton* m_pGLSystem;
	WindowClass* m_pWindow;
	ModelManagerSingleton* m_pModelMngr;
	LightManagerSingleton* m_pLightMngr;
	MaterialManagerSingleton* m_pMatMngr;
	GridClass* m_pGrid;
	PrimitiveClass* m_pLightBulb;
	CameraSingleton* m_pCamera;
	MeshManagerSingleton* m_pMeshMngr;

	CannonManager cMnger;
	TargetBoxManager tbMnger;
	OctTreeManager* octTreeMnger;

	String m_sSelectedObject;

public:
	static ApplicationClass* GetInstance( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);//Singleton accessor 
	static void ReleaseInstance(void);	//Singleton Destructor
	void Run (void); //Main Loop

private:
	ApplicationClass();
	ApplicationClass(ApplicationClass const& input);
	ApplicationClass& operator=(ApplicationClass const& input);
	~ApplicationClass();

	void Update (void);
	void Display2X (void);
	void Display3X (void);
	void DisplayDX (void);
	void Idle (void);
	void Reshape(int a_nWidth, int a_nHeight);
	
	void InitAppSystem(void);
	void InitAppInternalVariables(void);
	void InitAppVariables(void);

	void ProcessKeyboard(void);
	void ProcessMouse(void);
	void ProcessJoystick(void);
	
	void Init( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
	void Release(void);
	void ArcBall(float a_fSensitivity = 0.1f);
	void CameraRotation(float a_fSpeed = 0.001f);
	void ReadConfig(void);
	void WriteConfig(void);
};
#endif //__APPLICATION_H_