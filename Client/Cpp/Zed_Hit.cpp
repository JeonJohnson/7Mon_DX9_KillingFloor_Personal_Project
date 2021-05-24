#include "stdafx.h"
#include "..\Header\Zed_Hit.h"
#include "Zed.h"
#include "AnimationController.h"
#include "StateController.h"


Zed_Hit::Zed_Hit()
{
}


Zed_Hit::~Zed_Hit()
{
}

void Zed_Hit::Initialize()
{
}

void Zed_Hit::EnterState()
{
	if (m_pAnimCtrl == nullptr)
	{
		m_pAnimCtrl= 	m_GameObject->Get_Component<AnimationController>();
	}

	if (m_pZedInfo == nullptr)
	{
		m_pZedInfo = m_GameObject->Get_Component<Zed>();
	}

	if (m_pZedInfo->Get_ZedInfo().m_eName == 2)
	{
		m_iHitAnimIndex = 5;
	}


	if (m_pAnimCtrl->Get_CurAnimIndex() == m_iHitAnimIndex)
	{
		return;
	}

	//m_pAnimCtrl->SEt
	m_pAnimCtrl->Play(m_iHitAnimIndex);

	Hit_Sound();
	//switch (m_pZedInfo->m_eName)
	//{
	//case 0:
	//{m_pAnimCtrl->Play(4); }
	//break;

	//case 1:
	//{m_pAnimCtrl->Play(4); }
	//break;
	//
	//case 2:
	//{m_pAnimCtrl->Play(5); }
	//break;

	//case 3:
	//{m_pAnimCtrl->Play(4); }
	//break;

	//default:
	//	break;
	//}
}

void Zed_Hit::UpdateState()
{
	DEBUG_LOG(L"Zed : Hit");

	if (m_pAnimCtrl->IsEnd())
	{
		m_pStateController->Set_State(L"Zed_Idle");
	}

	


	
}

void Zed_Hit::ExitState()
{
}

void Zed_Hit::Hit_Sound()
{
	wstring SoundName;

	int iRand = 0;
	switch (m_pZedInfo->Get_ZedInfo().m_eName)
	{
	case 0: //clot
	{
		iRand = rand() % 4;

		SoundName = L"Zed_Clot_Pain" + to_wstring(iRand) + L".wav";
		EngineFunction->OverlapPlay_Sound(SoundName, SoundCH_Clot_HIT);
	}
	break;

	case 1: //goreFast
	{
		iRand = rand() % 4;

		SoundName = L"Zed_Clot_Pain" + to_wstring(iRand) + L".wav";
		EngineFunction->OverlapPlay_Sound(SoundName, SoundCH_GoreFast_Hit);

	}
	break;

	case 2: //Scrake
	{
		iRand = rand() % 4;

		SoundName = L"Zed_Clot_Pain" + to_wstring(iRand) + L".wav";
		EngineFunction->OverlapPlay_Sound(SoundName, SoundCH_Scrake_Hit);
	}
	break;


	default:
		break;
	}
}
