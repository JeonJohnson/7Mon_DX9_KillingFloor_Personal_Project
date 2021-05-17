#include "stdafx.h"
#include "..\Header\Zed_Att.h"
#include "Zed.h"
#include "StateController.h"
#include "AnimationController.h"


Zed_Att::Zed_Att()
{
}


Zed_Att::~Zed_Att()
{
}

void Zed_Att::Initialize()
{
}

void Zed_Att::EnterState()
{
	if (m_pAnimCtrl == nullptr)
	{
		m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	}

	if (m_pZedInfo == nullptr)
	{
		m_pZedInfo = m_GameObject->Get_Component<Zed>();
	}

	
	if (m_pAnimCtrl->Get_CurAnimIndex() != m_iAttAnimIndex)
	{
		m_pAnimCtrl->Play(m_iAttAnimIndex,true);
	}
}

void Zed_Att::UpdateState()
{
	DEBUG_LOG(L"Zed : Attack");

	if (m_pAnimCtrl->IsEnd())
	{
		m_pStateController->Set_State(L"Zed_Idle");
	}
}

void Zed_Att::ExitState()
{
}
