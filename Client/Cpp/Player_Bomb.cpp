#include "stdafx.h"
#include "..\Header\Player_Bomb.h"

#include "Player_Attack.h"
#include "Player_Status.h"
#include "Weapon_Status.h"
#include "Mesh_Renderer.h"
#include "AnimationController.h"
#include "StateController.h"
#include "BulletManager.h"

Player_Bomb::Player_Bomb()
{
}


Player_Bomb::~Player_Bomb()
{
}

void Player_Bomb::Initialize()
{
}

void Player_Bomb::EnterState()
{
	if (m_pPlayerAttack == nullptr)
	{
		m_pPlayerAttack = m_GameObject->Get_Component<Player_Attack>();
	}

	if (m_pPlayerStatus == nullptr)
	{
		m_pPlayerStatus = m_GameObject->Get_Component<Player_Status>();
	}

	if (m_pWeaponRenderer == nullptr)
	{
		m_pWeaponRenderer = m_GameObject->Get_Component<Mesh_Renderer>();
	}

	if (m_pAnimCtrl == nullptr)
	{
		m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	}
	m_pPlayerAttack->Set_IronSight(false);

	m_pCurWeapon = m_pPlayerAttack->Get_CurWeaponStatus();

	m_pWeaponRenderer->Set_Mesh(m_pPlayerAttack->Get_PipeBomb_Status()->m_tWeaponInfo.m_szName);
	m_pAnimCtrl->SetUp_AnimCtrl();
	m_pBombStatus = m_pPlayerAttack->Get_PipeBomb_Status();
	m_pAnimCtrl->Set_AnimSpd(1.f);
	m_pAnimCtrl->Play(0);

	EngineFunction->OverlapPlay_Sound(L"Weapon_Select.wav", SoundCH_PLAYER_FIRE);
	//m_pPlayerStatus->Set_Heal(true);
	m_bThrow = false;
}

void Player_Bomb::UpdateState()
{
	double curFrame = m_pAnimCtrl->Get_CurFrame();

	//DEBUG_LOG(L"CurFrame : " + to_wstring(curFrame));

	if (curFrame >= 0.8 && !m_bThrow)
	{
		EngineFunction->OverlapPlay_Sound(L"Bomb_Throw.wav", SoundCH_PLAYER_FIRE);
		m_bThrow = true;
	}


	if (m_pAnimCtrl->IsEnd())
	{
		m_pWeaponRenderer->Set_Mesh(m_pCurWeapon->m_tWeaponInfo.m_szName);
		m_pAnimCtrl->SetUp_AnimCtrl();
		BulletManager::Get_Instance()->Create_PipeBomb(m_GameObject, m_pBombStatus->m_tWeaponInfo);
		m_pStateController->Set_State(L"Player_Swap");
	}
}

void Player_Bomb::ExitState()
{
}
