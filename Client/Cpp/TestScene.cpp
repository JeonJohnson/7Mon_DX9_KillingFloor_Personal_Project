#include "stdafx.h"
#include "..\Header\TestScene.h"
#include "Player_Move.h"
#include "Text.h"
#include "Camera_FreeMove.h"
#include "Mesh_Renderer.h"
#include "Camera_FPS.h"
#include "Player_Attack.h"
#include "Anim_Controller.h"
#include "Line.h"
//#include "../../Reference/Header/Camera.h"
 
TestScene::TestScene()
{
}
 

TestScene::~TestScene()
{
	
}

void TestScene::Initialize()
{
	//D3DXCOLOR	colorTemp = D3DCOLOR_RGBA(196, 220, 229, 255);
	//D3DXCOLOR	colorTemp = D3DCOLOR_RGBA(253, 251, 211, 255);
	//
	//D3DLIGHT9*	Temp = new D3DLIGHT9;
	//ZeroMemory(Temp, sizeof(D3DLIGHT9));
	//Temp->Type = D3DLIGHT_DIRECTIONAL;
	//Temp->Diffuse = colorTemp;
	//Temp->Ambient = colorTemp * 0.05f;
	//Temp->Specular = colorTemp * 0.8f;
	//Vector3 vTemp = { 1.f, -1.f, 1.f };
	//Temp->Direction = vTemp;

	//EngineFunction->Insert_Light(Temp, L"HatBit");
	//delete Temp;
	


	GameObject* Grid_Test = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_Grid");
	VIBuffer_Renderer::Desc Grid_Desc;
	Grid_Desc.wBufferName = L"Line_Grid";
	Grid_Test->Add_Component<VIBuffer_Renderer>(&Grid_Desc);

	//EngineFunction->Load_TerrainLayout(L"Data/temp.bin");
		
	EngineFunction->Load_Texture(L"Test/box_diffuse.png", L"Image_Box");
	EngineFunction->Load_Texture(L"Test/boss.png", L"Image_Boss");
	EngineFunction->Load_Texture(L"Test/test_Cube.dds", L"dds_Test");
	EngineFunction->Load_Texture(L"Test/PangDongE.png", L"PangDongE");

	EngineFunction->Load_Texture(L"Test/HitEffect_size.png", L"HitEffect");
	EngineFunction->Load_Texture(L"Test/PangDongE_UI.png", L"PangDongE_UI");
	EngineFunction->Load_Texture(L"Test/PosTest.png", L"UI_Test");
	EngineFunction->Load_Texture(L"Test/PosTest2.png", L"UI_Test2");

	//EngineFunction->Load_Mesh(L"Mesh/DynamicMesh/FPPOV_Revolver.X", L"Hand_Revolver");
	EngineFunction->Load_Mesh(L"Mesh/Weapon/Rifle/M4.X", L"M4");
	EngineFunction->Load_Mesh(L"Mesh/Weapon/Secondary/BerettaM9.X", L"BerettaM9");
	EngineFunction->Load_Mesh(L"Mesh/Weapon/Melee/Knife_M9.X", L"Knife_M9");

	EngineFunction->Load_Mesh(L"Mesh/Map/Temp/Map.X", L"Map");
	EngineFunction->Load_Mesh(L"Test/StaticMesh/PoliceCar.X", L"PoliceCar");
	EngineFunction->Load_Mesh(L"Mesh/Map/Objs/Statics/Taxi.X", L"Taxi");
	EngineFunction->Load_Mesh(L"Test/StaticMesh/stone.X", L"Stone");
	//EngineFunction->Load_Mesh(L"Test/StaticMesh/Boss_AgentSanwaMoney_000.X", L"Test_01");
	

	{

		//GameObject*		PoliceCar = INSTANTIATE(OBJECT_TAG_DEFAULT, L"PoliceCar");
		//PoliceCar->Set_Scale(Vector3(1.f, 1.f, 1.f));
		//PoliceCar->Set_Position(Vector3(-100.f, 0.f, -100.f));
		//Mesh_Renderer::Desc Policecar_desc;
		//Policecar_desc.szMeshName = L"PoliceCar";
		//PoliceCar->Add_Component<Mesh_Renderer>(&Policecar_desc);

		//GameObject*		Taxi = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Taxi");
		//Taxi->Set_Scale(Vector3(1.f, 1.f, 1.f));
		//Taxi->Set_Position(Vector3(50.f, 0.f, 50.f));
		//Mesh_Renderer::Desc Taxi_Desc;
		//Taxi_Desc.szMeshName = L"Taxi";
		//Taxi->Add_Component<Mesh_Renderer>(&Taxi_Desc);
		//
		//GameObject*		Test2 = INSTANTIATE(OBJECT_TAG_DEFAULT, L"TestObj");
		//Test2->Set_Scale(Vector3(0.1f, 0.1f, 0.1f));
		//Test2->Set_Position(Vector3(500.f, 0.f, 100.f));
		//Mesh_Renderer::Desc Test2desc;
		//Test2desc.szMeshName = L"Stone";
		//Test2->Add_Component<Mesh_Renderer>(&Test2desc);


		GameObject* Player = INSTANTIATE(OBJECT_TAG_PLAYER, L"Player");
		Player->Set_Position(Vector3(0.f, 20.f, 0.f));


		Camera::Desc Cam_desc;
		Cam_desc.fFov_Degree = 45.f;
		Player->Add_Component<Camera>(&Cam_desc);

		Camera_FPS::Desc Fps_Desc;
		Fps_Desc.fSensitive = 50.f;
		Player->Add_Component<Camera_FPS>(&Fps_Desc);


		//Mesh_Renderer::Desc	Hand_Desc;
		//Hand_Desc.szMeshName = L"M4";
		//Player->Add_Component<Mesh_Renderer>(&Hand_Desc);

		//Anim_Controller::Desc Anim_Desc;
		//Anim_Desc.fAnimSpd = 1.f;
		//Anim_Desc.iInitIndex = 6;
		//Anim_Desc.pGameObject = Player;
		//Player->Add_Component<Anim_Controller>(&Anim_Desc);


		Player_Move::Desc player_Desc;
		player_Desc.fWalkSpd = 40.f;
		player_Desc.fSprintSpd = 55.f;
		Player->Add_Component<Player_Move>(&player_Desc);

		//Player_Attack::Desc Att_Desc;
		//Att_Desc.pAnimCtrl = Player->Get_NewComponent<Anim_Controller>();
		//Att_Desc.pMeshRenderer = Player->Get_NewComponent<Mesh_Renderer>();
		//Att_Desc.szPrimary = L"M4";
		//Att_Desc.szSecondary = L"BerettaM9";
		//Att_Desc.szMelee = L"Knife_M9";
		//Player->Add_Component<Player_Attack>(&Att_Desc);

	

		//GameObject*		Map = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Map");
		//Map->Set_Position(Vector3(0, 0, 0.f));
		//Map->Set_Scale(Vector3(0.1f, 0.1f, 0.1f));
		//Mesh_Renderer::Desc Map_desc;
		//Map_desc.szMeshName = L"Map";
		//Map->Add_Component<Mesh_Renderer>(&Map_desc);
		
	}


#pragma region Test
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
		//GameObject* RectTexture_Test = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_RectTexture");
		//RectTexture_Test->Set_Position(Vector3(0.f, 50.f,0.f));
		//RectTexture_Test->Set_Scale(Vector3(50.f, 50.f, 50.f));

		//VIBuffer_Renderer::Desc Test_Desc;
		//Test_Desc.wBufferName = L"Rect_Texture";
		//Test_Desc.wTextureName = L"PangDongE"; 
		//Test_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_NonAlpha;
		//RectTexture_Test->Add_Component<VIBuffer_Renderer>(&Test_Desc);
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
		////EngineFunction->Load_AnimMesh(L"Test/DynamicMesh/Reference/Player.X", L"reference");
		//EngineFunction->Load_AnimMesh(L"Test/DynamicMesh/ArmyTruck.X", L"reference");
 	//	GameObject* Test_AnimMesh = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_AnimMesh");
		////Test_AnimMesh->Set_Scale(0.01f, 0.01f, 0.01f);
		//Test_AnimMesh->Set_Scale(1.f, 1.f, 1.f);
		////Test_AnimMesh->Set_RotationY(270.f);

		//Mesh_Renderer::Desc dynamic_desc;
		//dynamic_desc.szMeshName = L"reference";

		//Test_AnimMesh->Add_Component<Mesh_Renderer>(&dynamic_desc);
		////Test_Cam->Add_Component<Mesh_Renderer>(&dynamic_desc);
		////Mesh_Renderer* temp = Test_AnimMesh->Get_NewComponent<Mesh_Renderer>();
		////AnimationTest::Desc asdf;

		////Test_AnimMesh->Add_Component<AnimationTest>(&asdf);
	}

	{//StaticMesh Merge Test	
		//EngineFunction->Load_Mesh(L"Test/DynamicMesh/ArmyTruck.X", L"ArmyTruck_Static");
		//GameObject*		Test_Merge = INSTANTIATE(OBJECT_TAG_DEFAULT, L"ArmyTruck_Static");

		//Mesh_Renderer::Desc Merge_Desc;
		//Merge_Desc.szMeshName = L"ArmyTruck_Static";

		//Test_Merge->Add_Component<Mesh_Renderer>(&Merge_Desc);
	}

	{//DynamicMesh Merge Test
		//EngineFunction->Load_Mesh(L"Test/DynamicMesh/FPPOV_Revolver.X", L"Revolver_Test");
		//GameObject*		Test_Merge = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Revolver_Test");

		//Mesh_Renderer::Desc Merge_Desc;
		//Merge_Desc.szMeshName = L"Revolver_Test";
		//Merge_Desc.iAnimIndex = 1;
		//Test_Merge->Add_Component<Mesh_Renderer>(&Merge_Desc);	
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
#pragma endregion
}



