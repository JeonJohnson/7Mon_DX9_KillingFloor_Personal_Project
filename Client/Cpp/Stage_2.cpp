#include "stdafx.h"
#include "..\Header\Stage_2.h"
#include "StageManager.h"
#include "HudManager.h"
#include "ZedManager.h"
#include "StateController.h"

Stage_2::Stage_2()
{
}


Stage_2::~Stage_2()
{
}

void Stage_2::Initialize()
{
}

void Stage_2::EnterState()
{
	HudManager::Get_Instance()->Get_Hud(L"EnemyCount")->Set_Active(true);
	HudManager::Get_Instance()->Get_Hud(L"Clock")->Set_Active(false);

	StageManager::Get_Instance()->Set_CurStage(STAGE_NAME::STAGE_2);
}

void Stage_2::UpdateState()
{
	DEBUG_LOG(L"CurStage : Stage2_" + to_wstring(m_iCurPattern));

	Stage2_Skip();

	if (m_arrPattern[0] == false)
	{
		Generate_Phase1();
	}


	if (m_arrPattern[0] == true && m_arrPattern[1] == false)
	{
		Generate_Phase2();
		m_iCurPattern = 2;
	}

	if (m_arrPattern[1] == true && m_arrPattern[2] == false)
	{
		Generate_PhaseEnd();
		m_iCurPattern = 3;
	}


	if (m_arrPattern[2] == true && ZedManager::Get_Instance()->Get_ZedCount() <= 0)
	{
		m_pStateController->Set_State(L"Stage_Shop");
	}
}

void Stage_2::ExitState()
{
}

void Stage_2::Generate_Phase1()
{
	m_fTime += fTime;

	if (m_fTime >= m_fGeneTime)
	{
		if (m_iZedCount > 0)
		{
			int iRand = rand() % 4;

			int zedRand = rand() % 2;
			if (zedRand == 0)
			{
				ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));
			}
			else if (zedRand == 1)
			{
				ZedManager::Get_Instance()->Generate_GoreFast(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));
			}

			m_fGeneTime = Function_Math::RandFloat(1.f, 4.5f);
			m_fTime = 0.f;
			--m_iZedCount;
		}
	}


	if (m_iZedCount <= 0)
	{
		m_arrPattern[0] = true;

		m_fGeneTime = Function_Math::RandFloat(1.5f, 4.5f);
		m_fTime = 0.f;
		m_iZedCount = 6;
	}
}

void Stage_2::Generate_Phase2()
{

	m_fTime += fTime;

	if (m_fTime >= m_fGeneTime)
	{
		if (m_iZedCount > 0)
		{
			if (m_iZedCount == 6 || m_iZedCount == 3)
			{
				int iRand = rand() % 4;
				ZedManager::Get_Instance()->Generate_Scrake(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));
				m_fGeneTime = Function_Math::RandFloat(1.5f, 4.5f);
				m_fTime = 0.f;
				--m_iZedCount;
			}
			else
			{
				int iRand = rand() % 4;

				int zedRand = rand() % 2;
				if (zedRand == 0)
				{
					ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));
					m_fGeneTime = Function_Math::RandFloat(1.5f, 4.5f);
					m_fTime = 0.f;
					--m_iZedCount;

				}
				else if (zedRand == 1)
				{
					ZedManager::Get_Instance()->Generate_GoreFast(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));
					m_fGeneTime = Function_Math::RandFloat(1.5f, 4.5f);
					m_fTime = 0.f;
					--m_iZedCount;
				}
			}
		}
	}

	if (m_iZedCount <= 0 && ZedManager::Get_Instance()->Get_ZedCount() <= 2)
	{
		m_arrPattern[1] = true;

		m_fGeneTime = Function_Math::RandFloat(1.5f, 4.5f);
		m_fTime = 0.f;
		m_iZedCount = 8;
	}

}

void Stage_2::Generate_PhaseEnd()
{

	m_fTime += fTime;

	if (m_fTime >= m_fGeneTime)
	{
		if (m_iZedCount > 0)
		{
			if (m_iZedCount == 8 || m_iZedCount == 4 || m_iZedCount == 1)
			{
				int iRand = rand() % 4;
				ZedManager::Get_Instance()->Generate_Scrake(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));
				m_fGeneTime = Function_Math::RandFloat(1.5f, 4.5f);
				m_fTime = 0.f;
				--m_iZedCount;
			}
			else
			{
				int iRand = rand() % 4;

				int zedRand = rand() % 2;
				if (zedRand == 0)
				{
					ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));
					m_fGeneTime = Function_Math::RandFloat(1.5f, 4.5f);
					m_fTime = 0.f;
					--m_iZedCount;

				}
				else if (zedRand == 1)
				{
					ZedManager::Get_Instance()->Generate_GoreFast(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));
					m_fGeneTime = Function_Math::RandFloat(1.5f, 4.5f);
					m_fTime = 0.f;
					--m_iZedCount;
				}
			}
		}
	}

	if (m_iZedCount <= 0 )
	{
		m_arrPattern[2] = true;
	}

}

void Stage_2::Stage2_Skip()
{
	if (KeyPress(KEY_STATE_LCtrl) && KeyDown(KEY_STATE_F1))
	{
		m_pStateController->Set_State(L"Stage_Shop");
	}
}
