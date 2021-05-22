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

	//m_pAnimCtrl->SEt
	m_pAnimCtrl->Play(m_iHitAnimIndex);


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
