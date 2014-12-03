#include "ApplicationClass.h"
void ApplicationClass::InitAppVariables()
{
	std::vector<vector3> vVectors;
	m_nCubes = 100;
	for(int n = 0 ; n < m_nCubes; n++)
	{	
		vVectors.push_back(vector3(0.0f, 2 * n + 2, -0.1 * n));
		m_pModelMngr->LoadModel("Cube.obj", "Cube", glm::translate(matrix4(1.0f), vVectors[n]), 1, 1, 0);
		//m_pModelMngr->LoadModel("03_Earth.obj", "Earth", glm::translate(matrix4(1.0f), vVectors[n]), 1, 1, 0);
	}

	//Setup world, Broadphase, collision configuration, solver
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));

	//Ground
	groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);

	//Cube
	fallShape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
	//fallShape = new btSphereShape(1.0);
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	for(int n = 0; n < m_nCubes; n++)
	{
		fallMotionState.push_back(
			new btDefaultMotionState(
					btTransform(
						btQuaternion(0, 0, 0, 1),
						btVector3(
								vVectors[n].x,
								vVectors[n].y,
								vVectors[n].z)))
			);
		btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState[n], fallShape, fallInertia);
		fallRigidBody.push_back(new btRigidBody(fallRigidBodyCI));
		dynamicsWorld->addRigidBody(fallRigidBody[n]);
	}
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

	m_pModelMngr->Update(false); //Update the model manager (need to be called every update call, this is how you update your model positions and such.)
	
	//The following section will position the camera
#pragma region first person and arcball position
	//Arcball rotation
	if(m_bArcBall == true)
		ArcBall();

	//First person camera movement
	if(m_bFPC == true)
		CameraRotation();
#pragma endregion
	
	float fFPS = static_cast<float>(m_pSystem->FPS);

	dynamicsWorld->stepSimulation(1 / 60.0f, 1);
	
	btTransform trans;
	for(int n = 0 ; n < m_nCubes; n++)
	{	
		fallRigidBody[n]->getMotionState()->getWorldTransform(trans);
		btVector3 position = trans.getOrigin();
		btQuaternion orientation = trans.getRotation();
		vector3 v3Position(position.getX(), position.getY(), position.getZ());
		glm::quat qOrientation(orientation.getW(),orientation.getX(),orientation.getY(),orientation.getZ());
		matrix4 mToWorld = glm::translate(matrix4(1.0f), v3Position) * glm::mat4_cast(qOrientation);
		m_pModelMngr->SetModelMatrix( mToWorld, n);
	}

	printf("FPS: %d \r", m_pSystem->FPS);//print the Frames per Second
}