#include "stdafx.h"
#include "..\Header\Stage_Boss.h"
#include "StageManager.h"
#include "HudManager.h"
#include "StateController.h"

Stage_Boss::Stage_Boss()
{
}


Stage_Boss::~Stage_Boss()
{
}

void Stage_Boss::Initialize()
{
}

void Stage_Boss::EnterState()
{

	HudManager::Get_Instance()->Get_Hud(L"EnemyCount")->Set_Active(true);
	HudManager::Get_Instance()->Set_TextZedCount(L"Press\nEnter!");
	HudManager::Get_Instance()->Get_Hud(L"Clock")->Set_Active(false);

	StageManager::Get_Instance()->Set_CurStage(STAGE_NAME::STAGE_BOSS);


}

void Stage_Boss::UpdateState()
{

	DEBUG_LOG(L"CurStage : Stage_Boss");

	StageBoss_Skip();

	if (m_bFadeOut)
	{
		if (HudManager::Get_Instance()->Fade_Out())
		{
			m_bNextScene = true;
			m_bFadeOut = false;
		}
	}

	if (m_bNextScene)
	{
		m_bNextScene = false;
		m_pStateController->Set_State(L"Stage_Ending");
	}
}

void Stage_Boss::ExitState()
{
}

void Stage_Boss::StageBoss_Skip()
{
	//if (KeyPress(KEY_STATE_LCtrl) && KeyDown(KEY_STATE_F1))
	if(KeyDown(KEY_STATE_ENTER))
	{
		HudManager::Get_Instance()->All_HudOnOff(OFF);
		HudManager::Get_Instance()->Setting_FadeOut();
		m_bFadeOut = true;
	}
}

