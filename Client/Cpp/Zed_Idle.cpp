#include "stdafx.h"
#include "..\Header\Zed_Idle.h"
#include "AnimationController.h"
#include "Zed.h"
#include "StateController.h"

Zed_Idle::Zed_Idle()
{
}


Zed_Idle::~Zed_Idle()
{
}

void Zed_Idle::Initialize()
{
}

void Zed_Idle::EnterState()
{
	if (m_pAnimCtrl == nullptr)
	{
		m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	}

	if (m_pZedInfo == nullptr)
	{
		m_pZedInfo = m_GameObject->Get_Component<Zed>();
	}

	m_iRandWalkRun = rand() % 2;

	m_pAnimCtrl->Play(0, true);
}

void Zed_Idle::UpdateState()
{
	DEBUG_LOG(L"Zed : Idle");

	if (m_iRandWalkRun == 0)
	{
		m_pStateController->Set_State(L"Zed_Walk");
	}
	else if (m_iRandWalkRun == 1)
	{
		m_pStateController->Set_State(L"Zed_Run");
	}
	//if (m_GameObject->Get_Component<Zed>()->Get_Distance() >= 70.f)
	//{
	//	m_pStateController->Set_State(L"Zed_Run");
	//}

}

void Zed_Idle::ExitState()
{
}
