#include "stdafx.h"
#include "..\Header\Zed_Run.h"
#include "StateController.h"
#include "AnimationController.h"
#include "Zed.h"
#include "NaviMesh.h"

Zed_Run::Zed_Run()
{
}


Zed_Run::~Zed_Run()
{
}

void Zed_Run::Initialize()
{
}

void Zed_Run::EnterState()
{
	if (m_pAnimCtrl == nullptr)
	{
		m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	}

	if (m_pZedInfo == nullptr)
	{
		m_pZedInfo = m_GameObject->Get_Component<Zed>();
	}

	if (m_pNaviMesh == nullptr)
	{
		m_pNaviMesh = m_pZedInfo->Get_NaviMesh();
	}

	if (m_pZedInfo->Get_ZedInfo().m_eName == 0)
	{
		m_iRunIndex = 1;
	}

	if (m_pAnimCtrl->Get_CurAnimIndex() != m_iRunIndex)
	{
		m_pAnimCtrl->Play(m_iRunIndex, true);
	}

	m_fRunCurTime = 0.f;
	m_fRunFullTime = (rand() % 6) + 1.5f;

	Run_Sound();
}

void Zed_Run::UpdateState()
{
	DEBUG_LOG(L"Zed : Run");

	m_fRunCurTime += fTime;

	Vector3 vForward = m_Transform->Get_Forward();
	//m_Transform->Add_Position(vForward * fTime * m_pZedInfo->Get_ZedInfo().m_fRunSpd);
	m_Transform->Add_Position(m_pNaviMesh->Add_Pos(m_Transform->Get_Position(), vForward * fTime * m_pZedInfo->Get_ZedInfo().m_fWalkSpd, &m_icurCellIndex));

	if (m_GameObject->Get_Component<Zed>()->Get_Distance() <= 30.f)
	{
		m_pStateController->Set_State(L"Zed_Att");
	}
	else 
	{
		if (m_fRunCurTime >= m_fRunFullTime)
		{
			m_pStateController->Set_State(L"Zed_Walk");
		}
	}


}

void Zed_Run::ExitState()
{
}

void Zed_Run::Run_Sound()
{
	wstring SoundName;

	int iRand = 0;
	switch (m_pZedInfo->Get_ZedInfo().m_eName)
	{
	//case 0: //clot
	//{
	//	iRand = rand() % 4;

	//	SoundName = L"Zed_Clot_Attack" + to_wstring(iRand) + L".wav";
	//	EngineFunction->Play_Sound(SoundName, SoundCH_Clot_IDLE);
	//}
	//break;

	case 1: //goreFast
	{
		iRand = rand() % 2;
		SoundName = L"Zed_Gorefast_Sprint" + to_wstring(iRand) + L".wav";
		EngineFunction->OverlapPlay_Sound(SoundName, SoundCH_GoreFast_Run);

	}
	break;

	case 2: //Scrake
	{
		iRand = rand() % 2;
		SoundName = L"Zed_Scrake_Sprint" + to_wstring(iRand) + L".wav";
		EngineFunction->OverlapPlay_Sound(SoundName, SoundCH_Scrake_Run);
	}
	break;


	default:
		break;
	}

}
