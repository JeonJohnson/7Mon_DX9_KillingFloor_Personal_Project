#include "stdafx.h"
#include "..\Header\Player_Idle.h"
//#include "..\..\Engine\Header\Anim_Controller.h"
#include "AnimationController.h"
#include "Player_TestAttack.h"


Player_Idle::Player_Idle()
{
}


Player_Idle::~Player_Idle()
{
}

void Player_Idle::Initialize()
{
	m_pAnimCtrl = m_GameObject->Get_NewComponent<AnimationController>();
	assert(L"AnimCtrl find failed" && m_pAnimCtrl);

	m_pWeapon = m_GameObject->Get_NewComponent<Player_TestAttack>();

}

void Player_Idle::EnterState()
{
}

void Player_Idle::UpdateState()
{

	switch (m_pWeapon->Get_CurWeaponIndex())
	{
	case 0:
	{
		if(m_pAnimCtrl->IsEnd() == true )
		{m_pAnimCtrl->Play(2); }
	}
	break;

	case 1:
	{
		if (m_pAnimCtrl->IsEnd() == true)
		m_pAnimCtrl->Play(4); 
	}
	break;

	case 2:
	{
		if (m_pAnimCtrl->IsEnd() == true)
		m_pAnimCtrl->Play(2); 
	}
	break;

	default:
		break;
	}
}

void Player_Idle::ExitState()
{
}
