#include "stdafx.h"
#include "..\Header\TestScene.h"
#include "Player_Move.h"
#include "Text.h"
#include "Camera_FreeMove.h"
#include "..\..\Engine\Header\Mesh_Renderer.h"
#include "AnimationTest.h"
//#include "../../Reference/Header/Camera.h"
 
TestScene::TestScene()
{
}
 

TestScene::~TestScene()
{
	
}

void TestScene::Initialize()
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

	EngineFunction->Load_StaticMesh(L"Test/StaticMesh/Truck.X",
		L"Test/StaticMesh/TruckOneCanvasDiffuseTGA.png", L"truck");

	{//Rect Color Test
		//GameObject* RectColor_Test = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_RectColor");
		//RectColor_Test->Set_Position(Vector3(0.f, 0.f, 80.f));
		//RectColor_Test->Set_Scale(Vector3(1.f, 1.f, 1.f));

		//VIBuffer_Renderer::Desc Test_Desc;
		//Test_Desc.wBufferName = L"Rect_Color";
		//Test_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_NonAlpha;
		//RectColor_Test->Add_Component<VIBuffer_Renderer>(&Test_Desc);
	}

	{//Rect Textrue Test
		GameObject* RectTexture_Test = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_RectTexture");
		RectTexture_Test->Set_Position(Vector3(0.f, 0.f,0.f));
		RectTexture_Test->Set_Scale(Vector3(1.f, 1.f, 1.f));

		VIBuffer_Renderer::Desc Test_Desc;
		Test_Desc.wBufferName = L"Rect_Color";
		Test_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_NonAlpha;
		RectTexture_Test->Add_Component<VIBuffer_Renderer>(&Test_Desc);
	}

	{ //Cube Color Test
		//GameObject* CubeColor_Test = INSTANTIATE(OBJECT_TAG_DEFAULT, L"CubeColor_Test");
		//CubeColor_Test->Set_Position(Vector3(0.f, 0.f, 0.f));
		//CubeColor_Test->Set_Scale(Vector3(1.f, 1.f, 1.f));

		//VIBuffer_Renderer::Desc Test_Desc;
		//Test_Desc.wBufferName = L"Cube_Color";
		//Test_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_NonAlpha;
		//CubeColor_Test->Add_Component<VIBuffer_Renderer>(&Test_Desc);
	}

	{ //Cube Textrue Test
		//GameObject* CubeTexture_Test = INSTANTIATE(OBJECT_TAG_DEFAULT, L"CubeTexture_Test");
		//CubeTexture_Test->Set_Position(Vector3(0.f, 0.f, 0.f));
		//CubeTexture_Test->Set_Scale(Vector3(1.f, 1.f, 1.f));


		//VIBuffer_Renderer::Desc Cube_Desc;
		//Cube_Desc.wBufferName = L"Cube_Texture";
		//Cube_Desc.wTextureName = L"Image_Boss";
		//Cube_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Priority;
		//CubeTexture_Test->Add_Component<VIBuffer_Renderer>(&Cube_Desc);
	}

	{//Cube DDs Test
		//GameObject* CubeDDs_Test = INSTANTIATE(OBJECT_TAG_DEFAULT, L"CubeDDs_Test");
		//CubeDDs_Test->Set_Position(Vector3(0.f, 0.f, 0.f));
		//CubeDDs_Test->Set_Scale(Vector3(1.f, 1.f, 1.f));

		//VIBuffer_Renderer::Desc Cube_dds_Desc;
		//Cube_dds_Desc.wBufferName = L"Cube_DDS";
		//Cube_dds_Desc.wTextureName = L"dds_Test";
		//Cube_dds_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Priority;
		//CubeDDs_Test->Add_Component<VIBuffer_Renderer>(&Cube_dds_Desc);
	}

	{//Static Mesh Test 
	 //GameObject* Test_Mesh = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_Mesh");
	 //Test_Mesh->Set_Position(Vector3(0.f, 0.f, 0.f));
	 //Test_Mesh->Set_Scale(Vector3(0.1f, 0.1f, 0.1f));
	 //Test_Mesh->RotateY(45.f);
	 ////Test_Mesh->RotateX(45.f);
	 ////Test_Mesh->RotateZ(45.f);

	 //Mesh_Renderer::Desc Mesh_desc;
	 //Mesh_desc.szMeshName = L"truck";
	 //Test_Mesh->Add_Component<Mesh_Renderer>(&Mesh_desc);
	}
	
	
	{//Dynamic Mesh Test
		//EngineFunction->Load_AnimMesh(L"Test/DynamicMesh/Reference/Player.X", L"reference");
		EngineFunction->Load_AnimMesh(L"Test/DynamicMesh/FPPOV_Revoloer.X", L"reference");
		GameObject* Test_AnimMesh = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_AnimMesh");
		//Test_AnimMesh->Set_Scale(0.01f, 0.01f, 0.01f);
		Test_AnimMesh->Set_Scale(1.f, 1.f, 1.f);
		//Test_AnimMesh->Set_RotationY(270.f);

		Mesh_Renderer::Desc dynamic_desc;
		dynamic_desc.szMeshName = L"reference";

		Test_AnimMesh->Add_Component<Mesh_Renderer>(&dynamic_desc);
		//Test_Cam->Add_Component<Mesh_Renderer>(&dynamic_desc);
		//Mesh_Renderer* temp = Test_AnimMesh->Get_NewComponent<Mesh_Renderer>();
		AnimationTest::Desc asdf;

		Test_AnimMesh->Add_Component<AnimationTest>(&asdf);
	}



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


