#include "stdafx.h"
#include "..\Header\Stage_Shop.h"
#include "HudManager.h"
#include "StateController.h"
#include "StageManager.h"


Stage_Shop::Stage_Shop()
{
}


Stage_Shop::~Stage_Shop()
{
}

void Stage_Shop::Initialize()
{

}

void Stage_Shop::EnterState()
{
	HudManager::Get_Instance()->Get_Hud(L"EnemyCount")->Set_Active(false);
	HudManager::Get_Instance()->Get_Hud(L"Clock")->Set_Active(true);
	StageManager::Get_Instance()->Set_CurStage(STAGE_NAME::STAGE_SHOP);

}

void Stage_Shop::UpdateState()
{
	DEBUG_LOG(L"CurStage : Shop");

	m_fLeftTime -= fTime;

	HudManager::Get_Instance()->Set_TextClock(m_fLeftTime);

	if (m_fLeftTime <= 0.f)
	{


		m_pStateController->Set_State(L"State_2");
	}

}


void Stage_Shop::ExitState()
{
}

void Stage_Shop::Create_Arrow()
{
	//
}
