#include "stdafx.h"
#include "..\Header\Stage_1.h"

#include "StateController.h"
#include "ZedManager.h"

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
	Generate_Phase1();
}

void Stage_1::UpdateState()
{
	DEBUG_LOG(L"CurStage : Stage1_" + to_wstring(m_iCurPattern));

	if (m_arrPattern[0] == true && m_arrPattern[1] == false
		&& ZedManager::Get_Instance()->Get_ZedCount() == 2)
	{
		Generate_Phase2();
		m_iCurPattern = 2;
	}

	if (m_arrPattern[1] == true && m_arrPattern[2] == false
		&& ZedManager::Get_Instance()->Get_ZedCount() == 2)
	{
		Generate_Phase3();
		m_iCurPattern = 2;
	}

	if (m_arrPattern[2] == true && m_arrPattern[3] == false
		&& ZedManager::Get_Instance()->Get_ZedCount() == 2)
	{
		Generate_PhaseEnd();
		m_iCurPattern = 3;
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

	for (int i = 0; i < 3; ++i)
	{
		ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(CHURCH));
	}

	for (int i = 0; i < 2; ++i)
	{
		ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(POLICE));
	}

	m_arrPattern[0] = true;
}

void Stage_1::Generate_Phase2()
{
	for (int i = 0; i < 2; ++i)
	{
		ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(HOTEL_LEFT));
	}

	for (int i = 0; i < 2; ++i)
	{
		ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(HOTEL_RIGHT));
	}

	for (int i = 0; i < 1; ++i)
	{
		ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(POLICE));
	}

	m_arrPattern[1] = true;
}

void Stage_1::Generate_Phase3()
{
	
	ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(HOTEL_LEFT));
	
	ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(HOTEL_RIGHT));

	for (int i = 0; i < 2; ++i)
	{
		ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(POLICE));
	}
	
	for (int i = 0; i < 2; ++i)
	{
		ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(CHURCH));
	}

	m_arrPattern[2] = true;
}

void Stage_1::Generate_PhaseEnd()
{

	ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(HOTEL_LEFT));

	ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(HOTEL_RIGHT));

	for (int i = 0; i < 2; ++i)
	{
		ZedManager::Get_Instance()->Generate_Clot(ZedManager::Get_Instance()->Get_ZedGenLocate(POLICE));
	}

	for (int i = 0; i < 2; ++i)
	{
		int k = rand() % 4;
		ZedManager::Get_Instance()->Generate_GoreFast(ZedManager::Get_Instance()->Get_ZedGenLocate(k));
	}

	m_arrPattern[3] = true;

}
