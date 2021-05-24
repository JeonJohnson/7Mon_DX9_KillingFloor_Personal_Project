#include "stdafx.h"
#include "..\Header\Stage_1.h"

#include "StateController.h"
#include "ZedManager.h"
#include "StageManager.h"

Stage_1::Stage_1()
{
}


Stage_1::~Stage_1()
{
}

void Stage_1::Initialize()
{
}

void Stage_1::EnterState()
{
	StageManager::Get_Instance()->Set_CurStage(STAGE_NAME::STAGE_1);
}

void Stage_1::UpdateState()
{
	DEBUG_LOG(L"CurStage : Stage1_" + to_wstring(m_iCurPattern));
	DEBUG_LOG(L"GeneTime : " + to_wstring(m_fGeneTime));


	Stage1_Skip();

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
		Generate_Phase3();
		m_iCurPattern = 3;
	}

	if (m_arrPattern[2] == true && m_arrPattern[3] == false)
	{
		Generate_PhaseEnd();
		m_iCurPattern = 4;
	}


	if (m_arrPattern[3] == true && ZedManager::Get_Instance()->Get_ZedCount() <= 0)
	{
		m_pStateController->Set_State(L"Stage_Shop");
	}
}

void Stage_1::ExitState()
{
}

void Stage_1::Generate_Phase1()
{

	m_fTime += fTime;

	if (m_fTime >= m_fGeneTime)
	{
		if (m_iZedCount >= 2)
		{
			ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(CHURCH_RIGHT));

			ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(CHURCH_LEFT));
		}
		
		m_fTime = 0.f;
		m_iZedCount -= 2;
	}


	if (m_iZedCount <= 0 && ZedManager::Get_Instance()->Get_ZedCount() <= 2)
	{
		m_arrPattern[0] = true;

		m_fGeneTime = Function_Math::RandFloat(1.5f, 4.5f);
		m_fTime = 0.f;
		m_iZedCount = 6;
	}
}

void Stage_1::Generate_Phase2()
{
	m_fTime += fTime;

	if (m_fTime >= m_fGeneTime)
	{
		if (m_iZedCount > 0) {
			int iRand = rand() % 2 + 2;
			ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));
			m_fGeneTime = Function_Math::RandFloat(1.f, 4.5f);
			m_fTime = 0.f;
			--m_iZedCount;
		}
	}

	if (m_iZedCount <= 0 && ZedManager::Get_Instance()->Get_ZedCount() <= 2)
	{
		m_arrPattern[1] = true;

		m_fGeneTime = Function_Math::RandFloat(1.5f, 4.5f);
		m_iZedCount = 6;
		m_fTime = 0.f;
	}


	
}

void Stage_1::Generate_Phase3()
{
	m_fTime += fTime;
	
	{
		if (m_iZedCount > 0)
		{
			int iRand = rand() % 4;

			ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));

			m_fGeneTime = Function_Math::RandFloat(1.f, 4.5f);
			m_fTime = 0.f;
			--m_iZedCount;
		}
	}

	if (m_iZedCount <= 0 && ZedManager::Get_Instance()->Get_ZedCount() <= 2)
	{
		m_arrPattern[2] = true;

		m_fGeneTime = Function_Math::RandFloat(1.5f, 4.5f);
		m_fTime = 0.f;
		m_iZedCount = 6;
	}



	//m_arrPattern[2] = true;
}

void Stage_1::Generate_PhaseEnd()
{
	m_fTime += fTime;

	if (m_fTime >= m_fGeneTime)
	{
		int iRand = rand() % 4;

		int iRand2 = rand() % 2;

		if (iRand2 == 0)
		{
			ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));
		}
		if (iRand2 == 1)
		{
			ZedManager::Get_Instance()->Generate_GoreFast(ZedManager::Get_Instance()->Get_ZedGenLocate(iRand));
		}


		m_fGeneTime = Function_Math::RandFloat(1.f, 4.5f);
		m_fTime = 0.f;
		--m_iZedCount;
	}

	if (m_iZedCount <= 0)
	{
		m_arrPattern[3] = true;

		//m_fGeneTime = Function_Math::RandFloat(1.5f, 2.5f);
		//m_fTime = 0.f;
		//m_iZedCount = 6;
	}


}

void Stage_1::Stage1_Skip()
{
	if (KeyPress(KEY_STATE_LCtrl) && KeyDown(KEY_STATE_F1))
	{
		m_pStateController->Set_State(L"Stage_Shop");
	}
}
