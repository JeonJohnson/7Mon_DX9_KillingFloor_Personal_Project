#include "stdafx.h"
#include "..\Header\Player_Swap.h"
#include "AnimationController.h"
#include "GameObject.h"
#include "Player_Attack.h"
#include "StateController.h"
#include "Weapon_Status.h"
#include "HudManager.h"


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
	m_pCurWeaponStatus = m_pPlayerAttack->Get_CurWeaponStatus();

	if (m_pCurWeaponStatus->m_tWeaponInfo.m_eType != Weapon_Knife)
	{
		HudManager::Get_Instance()->Get_Hud(L"Bullet")->Set_Active(true);
		HudManager::Get_Instance()->Get_Hud(L"Magazine")->Set_Active(true);
	}
	else 
	{
		HudManager::Get_Instance()->Get_Hud(L"Bullet")->Set_Active(false);
		HudManager::Get_Instance()->Get_Hud(L"Magazine")->Set_Active(false);
	}

	EngineFunction->OverlapPlay_Sound(L"Weapon_Select.wav", SoundCH_PLAYER_FIRE);
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
