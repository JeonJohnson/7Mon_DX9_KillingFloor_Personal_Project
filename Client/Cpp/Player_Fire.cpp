#include "stdafx.h"
#include "..\Header\Player_Fire.h"
#include "AnimationController.h"
#include "StateController.h"
#include "Player_Attack.h"
#include "Weapon.h"

Player_Fire::Player_Fire()
{
}


Player_Fire::~Player_Fire()
{
}

void Player_Fire::Initialize()
{
}

void Player_Fire::EnterState()
{
	m_pCurWeapon = m_GameObject->Get_Component<Player_Attack>()->Get_CurWeapon();
}

void Player_Fire::UpdateState()
{

	DEBUG_LOG(L"Player cur State : Fire");
	


	m_pCurWeapon->m_fCurRapid += fTime;

	if (m_pCurWeapon->m_fCurRapid >= m_pCurWeapon->m_fMaxRapid)
	{
		if (m_pCurWeapon->m_bAuto)
		{
			if (MousePress(KEY_STATE_LMouse))
			{
				m_GameObject->Get_Component<AnimationController>()->Play(3);
			}
		}
		else
		{
			if (MouseDown(KEY_STATE_LMouse))
			{
				m_GameObject->Get_Component<AnimationController>()->Play(3);
			}
		}

		m_pCurWeapon->m_fCurRapid = 0.f;
	}


	
	if (m_GameObject->Get_Component<AnimationController>()->IsEnd())
	{
		m_pStateController->Set_State(L"Player_Idle");
	}
}

void Player_Fire::ExitState()
{
}
