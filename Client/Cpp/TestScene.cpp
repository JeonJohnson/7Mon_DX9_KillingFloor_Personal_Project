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
	Test_Cam->Add_Component<Camera>(&Cam_desc);
	Test_Cam->Set_Position(Vector3(0.f, 0.f, -10.f));
	


	GameObject* Test_Triangle = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_Rect");
	Test_Triangle->Set_Position(Vector3(0.f, 0.f, 0.f));

	//VIBuffer_Renderer::Desc Test_Desc;
	//Test_Desc.wBufferName = L"Rect_Color";
	//Test_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Priority;
	//Test_Triangle->Add_Component<VIBuffer_Renderer>(&Test_Desc);

	EngineFuction->Load_Texture(L"Test/boss.png", L"Image_Boss");

	VIBuffer_Renderer::Desc Test_Desc;
	Test_Desc.wBufferName = L"Rect_Texture";
	Test_Desc.wTextureName = L"Image_Boss";
	Test_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Priority;
	Test_Triangle->Add_Component<VIBuffer_Renderer>(&Test_Desc);

	Player_Move::Desc Test_Move;
	Test_Triangle->Add_Component<Player_Move>(&Test_Move);
}
