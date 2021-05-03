#include "stdafx.h"
#include "..\Header\Player_Att.h"
#include "Player_Attack.h"
#include "Anim_Controller.h"
#include "StateController.h"


Player_Att::Player_Att()
{
}


Player_Att::~Player_Att()
{
}

void Player_Att::Initialize()
{
}

void Player_Att::EnterState()
{
}

void Player_Att::UpdateState()
{
	int iCurWeapon = m_GameObject->Get_Component<Player_Attack>()->Get_CurWeaponIndex();

	switch (iCurWeapon)
	{
	case 0:
	{
		if (MousePress(KEY_STATE_LMouse))
		{
			m_GameObject->Get_Component<Anim_Controller>()->Set_AnimIndex(4);
		}

		if (MouseUp(KEY_STATE_LMouse))
		{
			m_pStateController->Set_State(L"Player_Idle");
		}
	}
	break;

	case 1:
	{
		if (MouseDown(KEY_STATE_LMouse))
		{
			m_GameObject->Get_Component<Anim_Controller>()->Set_AnimIndex(3);
		}

		if (m_GameObject->Get_Component<Anim_Controller>()->Get_End())
		{
			m_pStateController->Set_State(L"Player_Idle");
		}
	}
	break;

	case 2:
	{
		if (MousePress(KEY_STATE_LMouse))
		{
			m_GameObject->Get_Component<Anim_Controller>()->Set_AnimIndex(6);
		}
		if (MouseUp(KEY_STATE_LMouse))
		{
			m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
		}
	}
	break;

	default:
		break;
	}
	
}

void Player_Att::ExitState()
{
}
