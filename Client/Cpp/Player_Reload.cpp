#include "stdafx.h"
#include "..\Header\Player_Reload.h"
//#include "..\..\Engine\Header\Anim_Controller.h"
#include "AnimationController.h"
#include "..\..\Engine\Header\StateController.h"

//#include "Weapon.h"
#include "Player_Attack.h"
#include "Weapon_Status.h"


Player_Reload::Player_Reload()
{
}


Player_Reload::~Player_Reload()
{
}

void Player_Reload::Initialize()
{
}

void Player_Reload::EnterState()
{
	m_pCurWeaponStatus = m_GameObject->Get_Component<Player_Attack>()->Get_CurWeaponStatus();
	if (m_pCurWeaponStatus->m_tWeaponInfo.m_iCurMagazine <= 0)
	{
		m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
	}
}

void Player_Reload::UpdateState()
{

	DEBUG_LOG(L"Player Cur State : Reload");


	int temp = m_GameObject->Get_Component<AnimationController>()->Get_CurAnimIndex();
	
	if (temp != 2)
	{
		m_GameObject->Get_Component<AnimationController>()->Play(2);
	}

	if (m_GameObject->Get_Component<AnimationController>()->IsEnd())
	{
	
		--m_pCurWeaponStatus->m_tWeaponInfo.m_iCurMagazine;
		m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet = m_pCurWeaponStatus->m_tWeaponInfo.m_iMaxBullet;
		m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
	}
}

void Player_Reload::ExitState()
{

}
