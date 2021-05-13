#include "stdafx.h"
#include "..\Header\Player_Reload.h"
//#include "..\..\Engine\Header\Anim_Controller.h"
#include "AnimationController.h"
#include "..\..\Engine\Header\StateController.h"

#include "Weapon.h"
#include "Player_Attack.h"


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
		Player_Attack* temp = m_GameObject->Get_Component<Player_Attack>();

		temp->Get_CurWeapon()->m_iCurBullet = temp->Get_CurWeapon()->m_iMaxBullet;
		m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
	}
}

void Player_Reload::ExitState()
{

}
