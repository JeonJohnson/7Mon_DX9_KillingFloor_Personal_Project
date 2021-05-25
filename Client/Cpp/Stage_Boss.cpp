#include "stdafx.h"
#include "..\Header\Stage_Boss.h"
#include "StageManager.h"
#include "HudManager.h"
#include "StateController.h"
#include "ZedManager.h"

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
	HudManager::Get_Instance()->Set_TextZedCount(L"Wait!");
	HudManager::Get_Instance()->Get_Hud(L"Clock")->Set_Active(false);

	StageManager::Get_Instance()->Set_CurStage(STAGE_NAME::STAGE_BOSS);


}

void Stage_Boss::UpdateState()
{

	DEBUG_LOG(L"CurStage : Stage_Boss");
	

	m_fTime -= fTime;
	if (m_fTime <= 0.f)
	{
		m_fTime = 0.f;
	}
	m_fGeneTime += fTime;
	wstring script;
	int iTime = (int)m_fTime;
	script = L"Wait!\n" + to_wstring(iTime) + L"Sec";
	HudManager::Get_Instance()->Set_TextZedCount(script);

	Generate_Rand();

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
	if(KeyDown(KEY_STATE_ENTER) || m_fTime <=0.f )
	{
		if (!m_bFadeOut)
		{
			HudManager::Get_Instance()->All_HudOnOff(OFF);
			HudManager::Get_Instance()->Setting_FadeOut();
			m_bFadeOut = true;
		}
	}
}

void Stage_Boss::Generate_Rand()
{
	if (m_fGeneTime >= 0.5f)
	{
		int iLocateRand = rand() % 4;

		int iZedRand = rand() % 3;

		switch (iZedRand)
		{
		case 0:
		{
			ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(iLocateRand));
		}
		break;
		case 1:
		{
			ZedManager::Get_Instance()->Generate_GoreFast(ZedManager::Get_Instance()->Get_ZedGenLocate(iLocateRand));
		}
		break;
		case 2:
		{
			ZedManager::Get_Instance()->Generate_Scrake(ZedManager::Get_Instance()->Get_ZedGenLocate(iLocateRand));
		}
		break;

		default:
			break;
		}

		m_fGeneTime = 0.f;
	}
}

