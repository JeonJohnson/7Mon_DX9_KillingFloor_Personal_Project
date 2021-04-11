#include "stdafx.h"
#include "..\Header\TestScene.h"
#include "Player_Move.h"
#include "Text.h"
#include "Camera_FreeMove.h"
#include "..\..\Engine\Header\MeshRenderer.h"
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
	Cam_desc.fFov_Degree = 45.f;
	Test_Cam->Add_Component<Camera>(&Cam_desc);
	Test_Cam->Set_Position(Vector3(0.f, 0.f, -100.f));

	Camera_FreeMove::Desc move_desc;
	Test_Cam->Add_Component<Camera_FreeMove>(&move_desc);


	EngineFunction->Load_Texture(L"Test/box_diffuse.png", L"Image_Box");
	EngineFunction->Load_Texture(L"Test/boss.png", L"Image_Boss");
	EngineFunction->Load_Texture(L"Test/test_Cube.dds", L"dds_Test");
	EngineFunction->Load_Texture(L"Test/PangDongE.png", L"PangDongE");
	
	EngineFunction->Load_Texture(L"Test/HitEffect_size.png", L"HitEffect");
	EngineFunction->Load_Texture(L"Test/PangDongE_UI.png", L"PangDongE_UI");
	EngineFunction->Load_Texture(L"Test/PosTest.png", L"UI_Test");
	EngineFunction->Load_Texture(L"Test/PosTest2.png", L"UI_Test2");
	
	{ //meshRender Test
		GameObject* Test_Mesh = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_Mesh");

		MeshRenderer::Desc Mesh_desc;
		Test_Mesh->Add_Component<MeshRenderer>(&Mesh_desc);
	}

{ //RectColor & Cube Test
	GameObject* Test_Obj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_Rect");
	Test_Obj->Set_Position(Vector3(0.f, 0.f, -80.f));
	Test_Obj->Set_Scale(Vector3(1.f, 1.f, 1.f));

//	//VIBuffer_Renderer::Desc Test_Desc;
//	//Test_Desc.wBufferName = L"Rect_Color";
//	//Test_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Priority;
//	//Test_Triangle->Add_Component<VIBuffer_Renderer>(&Test_Desc);
//
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
	//�����ӵ�� �̻���������. �ǤǤǤǤ�



//
	Player_Move::Desc Test_Move;
	Test_Obj->Add_Component<Player_Move>(&Test_Move);
}

	//{ //RectRender Test
	//	GameObject* Test_BoxRect = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_Rect");
	//	Test_BoxRect->Set_Position(Vector3(0.f, 0.5f, 10.f));
	//	//�����ǰ� �� ������ �� ���� ��¥
	//	Test_BoxRect->Set_Scale(Vector3(1.f, 1.f, 1.f));

	//	VIBuffer_Renderer::Desc Test_Desc;
	//	Test_Desc.wBufferName = L"Rect_Texture";
	//	Test_Desc.wTextureName = L"PangDongE";
	//	Test_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Priority;
	//	Test_BoxRect->Add_Component<VIBuffer_Renderer>(&Test_Desc);
	//
	//	//�굵 �� ���� 2 �ǤǤǤǤǤ�

	//	//Player_Move::Desc Test_Move;
	//	//Test_BoxRect->Add_Component<Player_Move>(&Test_Move);
	//}

	{//Uis Test
		//UI* Test_Text = INSTANTIATE_UI(L"Test_Text");
		//Test_Text->Set_Position(Vector3(640.f, 360.f, 0.f));
		//Test_Text->Set_Scale(Vector3(1.f, 1.f, 1.f));

		//Text::Desc textInfo;
		//textInfo.iHeight = 56;
		//textInfo.iWeight = FW_HEAVY;
		//textInfo.szScript = L"Test Test Test Test";


		//Sprite::Desc spriteInfo;
		//spriteInfo.TextureName = L"PangDongE_UI";
	

		//Test_Text->Add_UIComponent<Sprite>(&spriteInfo);
		//Test_Text->Add_UIComponent<Text>(&textInfo);

		

	}
}


