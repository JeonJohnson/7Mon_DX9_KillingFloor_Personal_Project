#include "stdafx.h"
#include "..\Header\Player_Swap.h"
#include "AnimationController.h"
#include "..\..\Engine\Header\StateController.h"


Player_Swap::Player_Swap()
{
}


Player_Swap::~Player_Swap()
{
}

void Player_Swap::Initialize()
{
}

void Player_Swap::EnterState()
{
	if (m_pPlayerAttack == nullptr)
	{
		m_pPlayerAttack = m_GameObject->Get_Component<Player_Attack>();
	}
}

void Player_Swap::UpdateState()
{

	DEBUG_LOG(L"Player Cur State : Swap");

	if (m_GameObject->Get_Component<AnimationController>()->Get_CurAnimIndex() != 1)
	{
		m_GameObject->Get_Component<AnimationController>()->Play(1);
	}

	if (m_GameObject->Get_Component<AnimationController>()->IsEnd())
	{
		m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
	}

}

void Player_Swap::ExitState()
{
}
