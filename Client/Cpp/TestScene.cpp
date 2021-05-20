#include "stdafx.h"
#include "..\Header\TestScene.h"
#include "Player_Move.h"
#include "Text.h"

#include "Mesh_Renderer.h"
#include "Camera_FPS.h"

#include "AnimationController.h"
#include "Line.h"
#include "StateController.h"
#include "Player_Idle.h"
#include "Player_Reload.h"

#include "SphereCollider.h"
#include "Player_Attack.h"
#include "Player_Status.h"
#include "Player_Fire.h"
#include "WeaponManager.h"
#include "Weapon.h"
#include "Player_Swap.h"
#include "UI.h"
#include "Sprite.h"
#include "HudManager.h"
#include "SkyBox.h"
#include "ZedManager.h"
#include "Zed_Status.h"
#include "Zed_Idle.h"
#include "Zed_Death.h"
#include "Zed_Hit.h"
#include "Zed_Att.h"
#include "Zed_Run.h"
#include "Zed_Walk.h"
#include "Zed.h"
#include "StageManager.h"
#include "Stage_1.h"
#include "..\..\Engine\Header\StateController.h"
#include "Stage_Shop.h"
#include "Stage_2.h"
#include "Stage_Boss.h"
#include "ShakeObject.h"
//#include "Anim_Controller.h"
//#include "../../Reference/Header/Camera.h"
 
TestScene::TestScene()
{

}
 

TestScene::~TestScene()
{
	
}

void TestScene::Initialize()
{

	EngineFunction->MouseLock();
	//GameObject* Grid_Test = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_Grid");
	//Grid_Test->Set_Position(Vector3(0, 30.f, 200));
	//Grid_Test->Set_Scale(Vector3(10.f, 10.f, 10.f));
	//VIBuffer_Renderer::Desc Grid_Desc;
	////Grid_Desc.wBufferName = L"Sphere_Debug";
	//Grid_Desc.wBufferName = L"Line_VIBuffer_Grid";
	//Grid_Test->Add_Component<VIBuffer_Renderer>(&Grid_Desc);

	EngineFunction->Load_NaviMeshData(L"Data/NaviMesh.bin");

	{//UI Texture
		//192x64
		EngineFunction->Load_Texture(L"Texture/UI/Hud_Hp.png", L"Hud_Hp");
		EngineFunction->Load_Texture(L"Texture/UI/Hud_Armor.png", L"Hud_Armor");
		EngineFunction->Load_Texture(L"Texture/UI/Hud_Weight.png", L"Hud_Weight");
		EngineFunction->Load_Texture(L"Texture/UI/Hud_Bullet.png", L"Hud_Bullet");
		EngineFunction->Load_Texture(L"Texture/UI/Hud_Magazine.png", L"Hud_Magazine");
		EngineFunction->Load_Texture(L"Texture/UI/Hud_Granade.png", L"Hud_Granade");

		EngineFunction->Load_Texture(L"Texture/UI/Hud_Money.png", L"Hud_Money");

		EngineFunction->Load_Texture(L"Texture/UI/Hud_Clock.png", L"Hud_Clock");
		EngineFunction->Load_Texture(L"Texture/UI/Hud_EnemyCount.png", L"Hud_EnemyCount");
	}

	{ //Effect

		//Screen
		EngineFunction->Load_Texture(L"Texture/ScreenEffect/BluntSplash_GrayScale.png", L"HitEffect");
		//EngineFunction->Load_Texture(L"Texture/ScreenEffect/BluntSplash.png", L"HitEffect");

		//trace
		EngineFunction->Load_Texture(L"Texture/Effect/BulletTrace/BulletTrace01.png", L"BulletTrace01");
		EngineFunction->Load_Texture(L"Texture/Effect/BulletTrace/BulletTrace02.png", L"BulletTrace02");
		EngineFunction->Load_Texture(L"Texture/Effect/BulletTrace/BulletTrace03.png", L"BulletTrace03");

		//blood
		EngineFunction->Load_Texture(L"Texture/Effect/Blood/Drip_001.png", L"Drip_001");
		EngineFunction->Load_Texture(L"Texture/Effect/Blood/Drip_002.png", L"Drip_002");
		EngineFunction->Load_Texture(L"Texture/Effect/Blood/Drip_003.png", L"Drip_003");

		EngineFunction->Load_Texture(L"Texture/Effect/Blood/Splatter_001.png", L"Splatter_001");
		EngineFunction->Load_Texture(L"Texture/Effect/Blood/Splatter_002.png", L"Splatter_002");
		EngineFunction->Load_Texture(L"Texture/Effect/Blood/Splatter_003.png", L"Splatter_003");
		EngineFunction->Load_Texture(L"Texture/Effect/Blood/Splatter_004.png", L"Splatter_004");
		EngineFunction->Load_Texture(L"Texture/Effect/Blood/Splatter_005.png", L"Splatter_005");
		EngineFunction->Load_Texture(L"Texture/Effect/Blood/Splatter_006.png", L"Splatter_006");
		//EngineFunction->Load_Texture(L"Texture/Effect/Fire/BulletTrace01.png", L"Fire");

		//Fire
		auto FireEffect = EngineFunction->Load_Texture(L"Texture/Effect/Fire/Fire_00.png", L"Fire_Effect");
		
		for (int i = 1; i < 16; ++i)
		{
			wstring FileName = L"Fire_";
			if (i < 10)
			{
				FileName += L"0" + to_wstring(i) + L".png";
			}
			else
			{
				FileName += to_wstring(i) + L".png";
			}
			EngineFunction->Add_Texture(FireEffect, L"Texture/Effect/Fire/" + FileName);
		}
		
		

		//Muzzle
		for(int i = 0; i< 4; ++i)
		{			
			wstring FileName = L"Muzzle_0" + to_wstring(i) + L".png";
			EngineFunction->Load_Texture(L"Texture/Effect/Muzzle/" + FileName, FileName);
		}
	}


	{//weapon
		EngineFunction->Load_Mesh(L"Mesh/Weapon/Dynamic/AK47.X", L"AK47");
		EngineFunction->Load_Mesh(L"Mesh/Weapon/Dynamic/ShotGun.X", L"ShotGun");
		EngineFunction->Load_Mesh(L"Mesh/Weapon/Dynamic/M99.X", L"M99");

		EngineFunction->Load_Mesh(L"Mesh/Weapon/Dynamic/Beretta.X", L"Beretta");
		EngineFunction->Load_Mesh(L"Mesh/Weapon/Dynamic/Revolver.X", L"Revolver");

		EngineFunction->Load_Mesh(L"Mesh/Weapon/Dynamic/Knife.X", L"Knife");
		WeaponManager::Get_Instance()->Nogada_Data();
	}

	{ //Zed Meshes
		EngineFunction->Load_Mesh(L"Mesh/Zeds/Clot/Clot.X", L"Clot");
		EngineFunction->Load_Mesh(L"Mesh/Zeds/GoreFast/GoreFast.X", L"GoreFast");
		EngineFunction->Load_Mesh(L"Mesh/Zeds/Scrake/Scrake.X", L"Scrake");
		EngineFunction->Load_Mesh(L"Mesh/Zeds/Patriarch/Patriarch.X", L"Patriarch");

	}




	{//Hud
		HudManager::Get_Instance();

		//width = 96 | height = 32
		{
			UI*	Hud_Hp = INSTANTIATE_UI(L"Hp");
			Hud_Hp->Set_Position(Vector3(64.f, 690.f, 0.f));
			Hud_Hp->Set_Scale(Vector3(0.5f, 0.5f, 0.5f));

			Sprite::Desc hpSprite;
			hpSprite.TextureName = L"Hud_Hp";
			Hud_Hp->Add_UIComponent<Sprite>(&hpSprite);

			Text::Desc hpText;
			hpText.szScript = L"100";
			hpText.iHeight = 20;
			hpText.iWeight = 1000;
			hpText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
			hpText.vOffSet = Vector2(10.f, 0.f);
			Hud_Hp->Add_UIComponent<Text>(&hpText);

			HudManager::Get_Instance()->Insert_Hud(L"Hp", Hud_Hp);
		}

		{
			UI*	Hud_Armor = INSTANTIATE_UI(L"Armor");
			Hud_Armor->Set_Position(Vector3(160.f, 690.f, 0.f));
			Hud_Armor->Set_Scale(Vector3(0.5f, 0.5f, 0.5f));

			Sprite::Desc ArmorSprite;
			ArmorSprite.TextureName = L"Hud_Armor"; 
			Hud_Armor->Add_UIComponent<Sprite>(&ArmorSprite);

			Text::Desc ArmorText;
			ArmorText.szScript = L"50";
			ArmorText.iHeight = 20;
			ArmorText.iWeight = FW_HEAVY;
			ArmorText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
			ArmorText.vOffSet = Vector2(10.f, 0.f);
			Hud_Armor->Add_UIComponent<Text>(&ArmorText);

			HudManager::Get_Instance()->Insert_Hud(L"Armor", Hud_Armor);
		}

		{
			UI*	Hud_Weight = INSTANTIATE_UI(L"Weight");
			Hud_Weight->Set_Position(Vector3(254.f, 690.f, 0.f));
			Hud_Weight->Set_Scale(Vector3(0.5f, 0.5f, 0.5f));

			Sprite::Desc WeightSprite;
			WeightSprite.TextureName = L"Hud_Weight";
			Hud_Weight->Add_UIComponent<Sprite>(&WeightSprite);

			Text::Desc WeightText;
			WeightText.szScript = L"1/15";
			WeightText.iHeight = 20;
			WeightText.iWeight = FW_HEAVY;
			WeightText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
			WeightText.vOffSet = Vector2(10.f, 0.f);
			Hud_Weight->Add_UIComponent<Text>(&WeightText);

			HudManager::Get_Instance()->Insert_Hud(L"Weight", Hud_Weight);
		}

		{//bullet
			UI*	Hud_Bullet = INSTANTIATE_UI(L"Bullet");
			Hud_Bullet->Set_Position(Vector3(1024.f, 690.f, 0.f));
			Hud_Bullet->Set_Scale(Vector3(0.5f, 0.5f, 0.5f));

			Sprite::Desc BulletSprite;
			BulletSprite.TextureName = L"Hud_Bullet";
			Hud_Bullet->Add_UIComponent<Sprite>(&BulletSprite);

			Text::Desc BulletText;
			BulletText.szScript = L"30";
			BulletText.iHeight = 20;
			BulletText.iWeight = FW_HEAVY;
			BulletText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
			BulletText.vOffSet = Vector2(10.f, 0.f);
			Hud_Bullet->Add_UIComponent<Text>(&BulletText);

			HudManager::Get_Instance()->Insert_Hud(L"Bullet", Hud_Bullet);
		}

		{//Magazine
			UI*	Hud_Magazine = INSTANTIATE_UI(L"Magazine");
			Hud_Magazine->Set_Position(Vector3(1120.f, 690.f, 0.f));
			Hud_Magazine->Set_Scale(Vector3(0.5f, 0.5f, 0.5f));

			Sprite::Desc MagazineSprite;
			MagazineSprite.TextureName = L"Hud_Magazine";
			Hud_Magazine->Add_UIComponent<Sprite>(&MagazineSprite);

			Text::Desc MagazineText;
			MagazineText.szScript = L"7";
			MagazineText.iHeight = 20;
			MagazineText.iWeight = FW_HEAVY;
			MagazineText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
			MagazineText.vOffSet = Vector2(10.f, 0.f);
			Hud_Magazine->Add_UIComponent<Text>(&MagazineText);

			HudManager::Get_Instance()->Insert_Hud(L"Magazine", Hud_Magazine);
		}

		{//Granade
			UI*	Hud_Granade = INSTANTIATE_UI(L"Granade");
			Hud_Granade->Set_Position(Vector3(1216.f, 690.f, 0.f));
			Hud_Granade->Set_Scale(Vector3(0.5f, 0.5f, 0.5f));

			Sprite::Desc GranadeSprite;
			GranadeSprite.TextureName = L"Hud_Granade";
			Hud_Granade->Add_UIComponent<Sprite>(&GranadeSprite);

			Text::Desc GranadeText;
			GranadeText.szScript = L"3";
			GranadeText.iHeight = 20;
			GranadeText.iWeight = FW_HEAVY;
			GranadeText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
			GranadeText.vOffSet = Vector2(10.f, 0.f);
			Hud_Granade->Add_UIComponent<Text>(&GranadeText);

			HudManager::Get_Instance()->Insert_Hud(L"Granade", Hud_Granade);
		}

		{//Money
			UI*	Hud_Money = INSTANTIATE_UI(L"Money");
			Hud_Money->Set_Position(Vector3(1155.f, 610.f, 0.f));
			Hud_Money->Set_Scale(Vector3(0.75f, 0.75f, 0.75f));

			Sprite::Desc MoneySprite;
			MoneySprite.TextureName = L"Hud_Money";
			Hud_Money->Add_UIComponent<Sprite>(&MoneySprite);

			Text::Desc MoneyText;
			MoneyText.szScript = L"1200";
			MoneyText.iHeight = 30;
			MoneyText.iWeight = FW_HEAVY;
			MoneyText.ulOption = DT_VCENTER | DT_RIGHT | DT_NOCLIP;
			MoneyText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
			MoneyText.vOffSet = Vector2(75.f, 0.f);
			Hud_Money->Add_UIComponent<Text>(&MoneyText);

			HudManager::Get_Instance()->Insert_Hud(L"Money", Hud_Money);
		}
		
		{
			//Weapon
			UI*	Hud_WeaponName = INSTANTIATE_UI(L"WeaponName");
			Hud_WeaponName->Set_Position(Vector3(1215.f, 650.f, 0.f));
			Hud_WeaponName->Set_Scale(Vector3(1.f, 1.f, 1.f));

			Text::Desc WeaponText;
			WeaponText.szScript = L"가나다라마바사";
			WeaponText.iHeight = 30;
			WeaponText.iWeight = FW_HEAVY;
			WeaponText.ulOption = DT_VCENTER | DT_RIGHT | DT_NOCLIP;
			WeaponText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
			WeaponText.vOffSet = Vector2(0.f, 0.f);
			Hud_WeaponName->Add_UIComponent<Text>(&WeaponText);

			HudManager::Get_Instance()->Insert_Hud(L"WeaponName", Hud_WeaponName);
		}


		{
			//256x256
			UI*	Hud_Clock = INSTANTIATE_UI(L"Clock");
			//Hud_Clock->Set_Position(Vector3(64 + 5.f, 64 + 5.f, 0.f));
			Hud_Clock->Set_Position(Vector3(1216 - 5.f, 64 + 5.f, 0.f));
			Hud_Clock->Set_Scale(Vector3(0.5f, 0.5f, 0.5f));
			Hud_Clock->Set_Active(false);

			Sprite::Desc ClockSprite;
			ClockSprite.TextureName = L"Hud_Clock";
			Hud_Clock->Add_UIComponent<Sprite>(&ClockSprite);

			Text::Desc ClockText;
			ClockText.szScript = L"Left Time";
			ClockText.iHeight = 30;
			ClockText.iWeight = FW_HEAVY;
			ClockText.ulOption = DT_VCENTER | DT_CENTER | DT_NOCLIP;
			ClockText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
			ClockText.vOffSet = Vector2(0.f, 0.f);
			Hud_Clock->Add_UIComponent<Text>(&ClockText);


			HudManager::Get_Instance()->Insert_Hud(L"Clock", Hud_Clock);
		}

		{
			//256x256
			UI*	Hud_EnemyCount = INSTANTIATE_UI(L"EnemyCount");
			Hud_EnemyCount->Set_Position(Vector3(1216 - 5.f, 64 + 5.f, 0.f));
			Hud_EnemyCount->Set_Scale(Vector3(0.5f, 0.5f, 0.5f));

			Sprite::Desc EnemyCountSprite;
			EnemyCountSprite.TextureName = L"Hud_EnemyCount";
			Hud_EnemyCount->Add_UIComponent<Sprite>(&EnemyCountSprite);


			Text::Desc EnemyuCountText;
			EnemyuCountText.szScript = L"EnemyCount : ";
			EnemyuCountText.iHeight = 30;
			EnemyuCountText.iWeight = FW_HEAVY;
			EnemyuCountText.ulOption = DT_VCENTER | DT_CENTER | DT_NOCLIP;
			EnemyuCountText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
			EnemyuCountText.vOffSet = Vector2(0.f, 0.f);
			Hud_EnemyCount->Add_UIComponent<Text>(&EnemyuCountText);


			HudManager::Get_Instance()->Insert_Hud(L"EnemyCount", Hud_EnemyCount);
		}

		{
			
			UI*	HitEffect = INSTANTIATE_UI(L"HitEffect");
			HitEffect->Set_Position(Vector3(640.f,360.f, 0.f));
			//HitEffect->Set_Scale(Vector3(0f, 0.5f, 0.5f));
			HitEffect->Set_Active(false);

			Sprite::Desc HitEffect_Sprite;
			HitEffect_Sprite.TextureName = L"HitEffect";
			HitEffect->Add_UIComponent<Sprite>(&HitEffect_Sprite);


			HudManager::Get_Instance()->Insert_Hud(L"HitEffect", HitEffect);
		}
		
	}
	
	{//skybox
		EngineFunction->Load_Mesh(L"Mesh/SkyBox/SkyBox.X", L"SkyBox");
		
		GameObject*	SkyBoxObj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"SkyBox");
		SkyBoxObj->Set_Scale(Vector3(15.f, 15.f, 15.f));

		Mesh_Renderer::Desc SkyBoxDesc;
		SkyBoxDesc.szMeshName = L"SkyBox";
		SkyBoxObj->Add_Component<Mesh_Renderer>(&SkyBoxDesc);

		SkyBoxObj->Add_Component<SkyBox>();
	}

	{//map

		EngineFunction->Load_Mesh(L"Mesh/Map/WholeMap/WholeMap.X", L"WholeMap");

		GameObject*		Map = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Map");
		Map->Set_Position(Vector3(-100.f, 35.f, 250.f));
		Map->Set_Scale(Vector3(0.4f, 0.4f, 0.4f));
		Mesh_Renderer::Desc Map_desc;
		Map_desc.szMeshName = L"WholeMap";
		Map->Add_Component<Mesh_Renderer>(&Map_desc);
	
	}


	{
		GameObject* Player = INSTANTIATE(OBJECT_TAG_PLAYER, L"Player");
		Player->Set_Position(Vector3(0.f, 20.f, 0.f));

		Player->Add_Component<StateController>();
		auto PlayerStateCtrl = Player->Get_NewComponent<StateController>();
		PlayerStateCtrl->Add_State<Player_Idle>(L"Player_Idle");
		PlayerStateCtrl->Add_State<Player_Fire>(L"Player_Fire");
		PlayerStateCtrl->Add_State<Player_Reload>(L"Player_Reload");
		PlayerStateCtrl->Add_State<Player_Swap>(L"Player_Swap");
		PlayerStateCtrl->Set_InitState(L"Player_Idle");
		
		Player->Add_Component<ShakeObject>();

		Mesh_Renderer::Desc	Hand_Desc;
		Hand_Desc.szMeshName = L"M99";
		Hand_Desc.vRot = Vector3{ 0.f, -90.f, 0.f };
		//nd_Desc.vPos = Vector3{ 0.f, 20.f, 0.f };
		Player->Add_Component<Mesh_Renderer>(&Hand_Desc);
		//AnimTest->Add_Component<Mesh_Renderer>(&Hand_Desc);

		Player_Move::Desc player_Desc;
		player_Desc.fWalkSpd = 60.f;
		player_Desc.fSprintSpd = 70.f;
		player_Desc.pNaviMesh = EngineFunction->Get_NaviMesh();
		Player->Add_Component<Player_Move>(&player_Desc);

		Camera::Desc Cam_desc;
		Cam_desc.fFov_Degree = 45.f;
		Cam_desc.fzFar = 1200.f;
		Player->Add_Component<Camera>(&Cam_desc);

		Camera_FPS::Desc Fps_Desc;
		Fps_Desc.fSensitive = 30.f;
		Player->Add_Component<Camera_FPS>(&Fps_Desc);

		AnimationController::Desc	Anim_desc;
		Anim_desc.dAnimSpd = 1.0;
		Anim_desc.bLoop = false;
		Anim_desc.bPlay = true;
		Player->Add_Component<AnimationController>(&Anim_desc);

		
		//playerAtt
		Player_Attack::Desc playerAtt;
		playerAtt.szInitWeapon = L"AK47";
		Player->Add_Component<Player_Attack>(&playerAtt);

		//PlayerStatus
		Player_Status::Desc playerStat;
		Player->Add_Component<Player_Status>(&playerStat);

		

		SphereCollider::Desc  colDesc;
		colDesc.fRadius = 15.f;
		colDesc.szColName = L"Player";
		Player->Add_Component<SphereCollider>(&colDesc);
	}
	
	{//Zeds

	//for(int i =0; i < 3; ++i)
	//{
	//	float x = 50 * i;
	//	
		ZedManager::Get_Instance();

		//GameObject* TestClot = INSTANTIATE(OBJECT_TAG_ZED, L"Clot" );
		//TestClot->Set_Position(Vector3(0, 0.f, 10.f));
		//TestClot->Set_Scale(Vector3(0.3f, 0.3f, 0.3f));

		//TestClot->Add_Component<StateController>();
		//auto ZedStateCtrl = TestClot->Get_Component<StateController>();
		//ZedStateCtrl->Add_State<Zed_Idle>(L"Zed_Idle");
		//ZedStateCtrl->Add_State<Zed_Walk>(L"Zed_Walk");
		//ZedStateCtrl->Add_State<Zed_Run>(L"Zed_Run");
		//ZedStateCtrl->Add_State<Zed_Att>(L"Zed_Att");
		//ZedStateCtrl->Add_State<Zed_Hit>(L"Zed_Hit");
		//ZedStateCtrl->Add_State<Zed_Death>(L"Zed_Death");
		//ZedStateCtrl->Set_InitState(L"Zed_Idle");

		//Mesh_Renderer::Desc Clot_Test;
		//Clot_Test.szMeshName = L"Clot";
		//TestClot->Add_Component<Mesh_Renderer>(&Clot_Test);

		//AnimationController::Desc Clot_Anim;
		//Clot_Anim.InitIndex = 0;
		//Clot_Anim.bLoop = true;
		//Clot_Anim.bClone = true;
		//TestClot->Add_Component<AnimationController>(&Clot_Anim);

		//SphereCollider::Desc Clot_Col;
		//Clot_Col.fRadius = 12.5f;
		//Clot_Col.vOffset = Vector3(0.f, 15.f, 0.f);
		//Clot_Col.szColName = L"Body";
		//TestClot->Add_Component<SphereCollider>(&Clot_Col);

		//Zed::Desc Clot_Default;
		//TestClot->Add_Component<Zed>(&Clot_Default);
	
		//Zed_Status::Desc Clot_Status;
		//TestClot->Add_Component<Zed_Status>(&Clot_Status);


	//}
		
	//GameObject* TestClot = INSTANTIATE(OBJECT_TAG_ZED, L"Clot");
	//	TestClot->Set_Position(Vector3(50.f, 0.f, 10.f));
	//	TestClot->Set_Scale(Vector3(0.3f, 0.3f, 0.3f));

	//	Mesh_Renderer::Desc Clot_Test;
	//	Clot_Test.szMeshName = L"Clot";
	//	TestClot->Add_Component<Mesh_Renderer>(&Clot_Test);

	//	AnimationController::Desc Clot_Anim;
	//	Clot_Anim.InitIndex = 0;
	//	aClot_Anim.bLoop = true;
	//	TestClot->Add_Component<AnimationController>(&Clot_Anim);

	
	}

	{ //StageState Setting

		auto StageMgr = StageManager::Get_Instance();

		auto gameObject = StageMgr->Get_GameObject();
		gameObject->Add_Component<StateController>();

		auto StageCtrl = gameObject->Get_Component<StateController>();

		StageCtrl->Add_State<Stage_Shop>(L"Stage_Shop");
		StageCtrl->Add_State<Stage_1>(L"Stage_1");
		StageCtrl->Add_State<Stage_2>(L"Stage_2");
		StageCtrl->Add_State<Stage_Boss>(L"Stage_Boss");

		StageCtrl->Set_InitState(L"Stage_1");
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



