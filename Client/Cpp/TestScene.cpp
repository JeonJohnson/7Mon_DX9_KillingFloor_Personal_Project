#include "stdafx.h"
#include "..\Header\TestScene.h"
#include "Player_Move.h"
//#include "../../Reference/Header/Camera.h"

TestScene::TestScene()
{
}


TestScene::~TestScene()
{
	
}

void TestScene::Initialize()
{
	GameObject*	Test_Cam = INSTANTIATE(OBJECT_TAG_MAINCAM, L"Test_Cam");
	Camera::Desc Cam_desc;
	Cam_desc.fFov_Degree =  45.f;
	Test_Cam->Add_Component<Camera>(&Cam_desc);
	Test_Cam->Set_Position(Vector3(0.f, 0.f, -10.f));
	


	GameObject* Test_Obj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_Rect");
	Test_Obj->Set_Position(Vector3(0.f, 0.f, 0.f));
	Test_Obj->Set_Scale(Vector3(1.f, 1.f, 1.f));

	//VIBuffer_Renderer::Desc Test_Desc;
	//Test_Desc.wBufferName = L"Rect_Color";
	//Test_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Priority;
	//Test_Triangle->Add_Component<VIBuffer_Renderer>(&Test_Desc);

	//EngineFuction->Load_Texture(L"Test/box_diffuse.png", L"Image_Boss");
	EngineFuction->Load_Texture(L"Test/boss.png", L"Image_Boss");
	EngineFuction->Load_Texture(L"Test/test_Cube.dds", L"dds_Test");

	//VIBuffer_Renderer::Desc Test_Desc;
	//Test_Desc.wBufferName = L"Rect_Texture";
	//Test_Desc.wTextureName = L"Image_Boss";
	//Test_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Priority;
	//Test_Obj->Add_Component<VIBuffer_Renderer>(&Test_Desc);

	//VIBuffer_Renderer::Desc Cube_Desc;
	//Cube_Desc.wBufferName = L"Cube_Texture";
	//Cube_Desc.wTextureName = L"Image_Boss";
	//Cube_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Priority;
	//Test_Obj->Add_Component<VIBuffer_Renderer>(&Cube_Desc);

	VIBuffer_Renderer::Desc Cube_dds_Desc;
	Cube_dds_Desc.wBufferName = L"Cube_DDS";
	Cube_dds_Desc.wTextureName = L"dds_Test";
	Cube_dds_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Priority;
	Test_Obj->Add_Component<VIBuffer_Renderer>(&Cube_dds_Desc);



	Player_Move::Desc Test_Move;
	Test_Obj->Add_Component<Player_Move>(&Test_Move);
}

