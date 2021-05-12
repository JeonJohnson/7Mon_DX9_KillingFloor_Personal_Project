#include "stdafx.h"
#include "..\Header\Player_Idle.h"
#include "AnimationController.h"
#include "Player_Attack.h"


Player_Idle::Player_Idle()
{
}


Player_Idle::~Player_Idle()
{
}

void Player_Idle::Initialize()
{
	//m_pAnimCtrl = m_GameObject->Get_NewComponent<AnimationController>();
	//assert(L"AnimCtrl find failed" && m_pAnimCtrl);

	//m_pWeapon = m_GameObject->Get_NewComponent<Player_TestAttack>();
	
	m_pAnimCtrl = m_GameObject->Get_NewComponent<AnimationController>();
}

void Player_Idle::EnterState()
{
	if (m_pAnimCtrl == nullptr)
	{
		m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	}

}

void Player_Idle::UpdateState()
{
	DEBUG_LOG(L"Player Cur State : Idle");

	if (m_pAnimCtrl->IsEnd() == true)
	{
		m_pAnimCtrl->Play(0);
	}


}

void Player_Idle::ExitState()
{
}
