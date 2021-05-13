#include "stdafx.h"
#include "Tool_Scene.h"
#include "..\..\Reference\Header\VIBuffer_Renderer.h"
#include "..\..\Reference\Header\Camera.h"
#include "Camera_TestMove.h"
#include "NaviMeshMaker.h"
#include "NaviMeshTestObj_Move.h"

Tool_Scene::Tool_Scene()
{
}


Tool_Scene::~Tool_Scene()
{
}

void Tool_Scene::Initialize()
{
	EngineFunction->Load_Mesh(L"Test/StaticMesh/DebugSphere.X", L"DebugSphere");
	EngineFunction->Load_Mesh(L"Mesh/Map/Objs/Statics/RedBus.X", L"RedBus");

	GameObject* Grid_Test = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_Grid");
	VIBuffer_Renderer::Desc Grid_Desc;
	Grid_Desc.wBufferName = L"Line_Grid";
	Grid_Test->Add_Component<VIBuffer_Renderer>(&Grid_Desc);

	GameObject*	Test_Cam = INSTANTIATE(OBJECT_TAG_MAINCAM, L"Test_Cam");
	Camera::Desc Cam_desc;
	Cam_desc.fFov_Degree = 45.f;
	Test_Cam->Add_Component<Camera>(&Cam_desc);
	Test_Cam->Set_Position(Vector3(0.f, 0.f, -100.f));

	Camera_TestMove::Desc move_desc;
	Test_Cam->Add_Component<Camera_TestMove>(&move_desc);

	//NaviMeshMaker::Desc maker_desc;
	//Test_Cam->Add_Component<NaviMeshMaker>(&maker_desc);

	GameObject* TestObj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"NaviMesh_Test");
	Mesh_Renderer::Desc Test_desc;
	Test_desc.szMeshName = L"RedBus";
	TestObj->Add_Component<Mesh_Renderer>(&Test_desc);

	NaviMeshTestObj_Move::Desc MoveTest_Desc;
	TestObj->Add_Component<NaviMeshTestObj_Move>(&MoveTest_Desc);

	

}
