#include "stdafx.h"
#include "..\Header\Player_Heal.h"
#include "Mesh_Renderer.h"
#include "Player_Attack.h"
#include "Player_Status.h"
#include "AnimationController.h"

#include "Weapon_Status.h"
#include "StateController.h"


Player_Heal::Player_Heal()
{
}


Player_Heal::~Player_Heal()
{
}

void Player_Heal::Initialize()
{
}

void Player_Heal::EnterState()
{
	if (m_pPlayerAttack == nullptr)
	{
		m_pPlayerAttack= 	m_GameObject->Get_Component<Player_Attack>();
	}

	if (m_pPlayerStatus == nullptr)
	{
		m_pPlayerStatus=	m_GameObject->Get_Component<Player_Status>();
	}

	if (m_pWeaponRenderer == nullptr)
	{
		m_pWeaponRenderer =	m_GameObject->Get_Component<Mesh_Renderer>();
	}

	if (m_pAnimCtrl == nullptr)
	{
		m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	}

	m_pCurWeapon = m_pPlayerAttack->Get_CurWeaponStatus();


	m_pWeaponRenderer->Set_Mesh(m_pPlayerAttack->Get_HealInjector_Status()->m_tWeaponInfo.m_szName);
	m_pAnimCtrl->SetUp_AnimCtrl();
	m_pAnimCtrl->Set_AnimSpd(1.f);
	m_pAnimCtrl->Play(0);
	m_pPlayerAttack->Set_IronSight(false);

	m_pPlayerStatus->Set_Heal(true);

}

void Player_Heal::UpdateState()
{
	if (m_pAnimCtrl->IsEnd())
	{
		m_pWeaponRenderer->Set_Mesh(m_pCurWeapon->m_tWeaponInfo.m_szName);
		m_pAnimCtrl->SetUp_AnimCtrl();
		m_pStateController->Set_State(L"Player_Swap");
	}
}

void Player_Heal::ExitState()
{
}
