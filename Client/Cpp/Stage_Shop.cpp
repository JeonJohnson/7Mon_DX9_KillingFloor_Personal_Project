#include "stdafx.h"
#include "..\Header\Stage_Shop.h"
#include "HudManager.h"
#include "StateController.h"
#include "StageManager.h"
#include "ShopManager.h"


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

	m_fLeftTime = 120.f;
}

void Stage_Shop::UpdateState()
{
	DEBUG_LOG(L"CurStage : Shop");

	m_fLeftTime -= fTime;
	Skip_Shop();
	Open_Shop();
	Exit_Shop();

	HudManager::Get_Instance()->Set_TextClock(m_fLeftTime);
	ShopManager::Get_Instance()->Set_LeftTime(m_fLeftTime);
	
	if (m_fLeftTime <= 0.f)
	{
		STAGE_NAME PastStage = StageManager::Get_Instance()->Get_PastStageName();



		if (PastStage == STAGE_NAME::STAGE_1)
		{
			m_pStateController->Set_State(L"Stage_2");
		}
		else if (PastStage == STAGE_NAME::STAGE_2)
		{
			m_pStateController->Set_State(L"Stage_Boss");
		}
	
	}

}


void Stage_Shop::ExitState()
{
}

void Stage_Shop::Create_Arrow()
{
	//
}

void Stage_Shop::Skip_Shop()
{
	if (KeyPress(KEY_STATE_LCtrl) && KeyDown(KEY_STATE_F1))
	{
		m_fLeftTime = 0.f;
	}
}

void Stage_Shop::Open_Shop()
{
	if (KeyDown(KEY_STATE_F))
	{
		HudManager::Get_Instance()->All_HudOnOff(false);
		ShopManager::Get_Instance()->Open_Shop();
	}
}

void Stage_Shop::Exit_Shop()
{
	if (KeyDown(KEY_STATE_ESC))
	{
		HudManager::Get_Instance()->All_HudOnOff(true);
		HudManager::Get_Instance()->Get_Hud(L"EnemyCount")->Set_Active(false);
		ShopManager::Get_Instance()->Exit_Shop();
	
	}
}
