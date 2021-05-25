#include "stdafx.h"
#include "..\Header\Stage_Ending.h"
#include "Mesh_Renderer.h"
#include "AnimationController.h"
#include "SphereCollider.h"
#include "HudManager.h"
#include "Player_Attack.h"
#include "Camera_FPS.h"
#include "Mesh.h"
#include "StageManager.h"


Stage_Ending::Stage_Ending()
{
}


Stage_Ending::~Stage_Ending()
{
}

void Stage_Ending::Initialize()
{
}

void Stage_Ending::EnterState()
{
	m_pChopper = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Chopper");
	m_pChopper->Set_Position(137.f, 0.f, 472.f);
	m_pChopper->Set_Scale(Vector3(0.25f, 0.25f, 0.25f));
	//Chopper->Set_Active(false);

	Mesh_Renderer::Desc ChopperRender;
	ChopperRender.iRenderLayer = RENDER_LAYER_Alpha;
	ChopperRender.szMeshName = L"Chopper";
	m_pChopper->Add_Component<Mesh_Renderer>(&ChopperRender);

	SphereCollider::Desc Chopper_Col;
	Chopper_Col.fRadius = 12.5f;
	Chopper_Col.vOffset = Vector3(0.f, 15.f, 0.f);
	Chopper_Col.szColName = L"Body";
	m_pChopper->Add_Component<SphereCollider>(&Chopper_Col);

	AnimationController::Desc ChopperAnim;
	ChopperAnim.InitIndex = 0;
	ChopperAnim.bPlay = true;
	ChopperAnim.bLoop = false;
	m_pChopper->Add_Component<AnimationController>(&ChopperAnim);

	m_pChopperRender = m_pChopper->Get_Component<Mesh_Renderer>();

	HudManager::Get_Instance()->All_HudOnOff(OFF);


	StageManager::Get_Instance()->Set_CurStage(STAGE_ENDING);

	m_pPlayer = EngineFunction->Get_GameObjectbyTag(OBJECT_TAG_PLAYER);
	auto temp = m_pPlayer->Get_Component<Player_Attack>();
	temp->Player_Ending();
	auto temp2 = m_pPlayer->Get_Component<Camera_FPS>();
	temp2->Disable_Mouse(OFF);

	m_pPlayer->Set_Position(Vector3(255.f, 20.f, 600.f));

	m_pPlayer->Set_Rotation(Vector3(0.f, 210.f, 0.f));
	EngineFunction->PlayBGM(L"BGM_Ending.wav");


}

void Stage_Ending::UpdateState()
{
	DEBUG_LOG(L"CurStage : Stage_Ending");
	if (m_fEndingTime <= 10.f)
	{
		HudManager::Get_Instance()->Fade_In();
	}

	Matrix ChopperMat = m_pChopperRender->Get_Mesh()->Get_BoneLocalPosByName(L"Helicopter");
	Matrix WorldMat =  m_pChopper->Get_Transform()->Get_WorldMatrix();
	Matrix ResultMat = ChopperMat* WorldMat;

	Vector3 ChooperPos;
	ChooperPos.x = ResultMat._41;
	ChooperPos.y = ResultMat._42;
	ChooperPos.z = ResultMat._43;

	m_pPlayer->Get_Transform()->LookAt(ChooperPos, 1.f);

	m_fEndingTime += fTime;
	
	if (m_fEndingTime >= 20.f)
	{
		HudManager::Get_Instance()->Fade_Out();
	}



	if (m_fEndingTime >= 25.f)
	{
		EngineFunction->Load_Scene(L"MainMenu_Scene");
	}

}

void Stage_Ending::ExitState()
{
	
}
