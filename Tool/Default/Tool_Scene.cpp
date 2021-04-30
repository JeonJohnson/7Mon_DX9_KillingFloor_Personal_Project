#include "stdafx.h"
#include "Tool_Scene.h"
#include "..\..\Engine\Header\VIBuffer_Renderer.h"
#include "GameObject.h"
#include "..\..\Engine\Header\Camera.h"
#include "Camera_TestMove.h"


Tool_Scene::Tool_Scene()
{
}


Tool_Scene::~Tool_Scene()
{
}

void Tool_Scene::Initialize()
{
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

}
