#include "stdafx.h"
#include "..\Header\Player_Reload.h"
//#include "..\..\Engine\Header\Anim_Controller.h"
#include "AnimationController.h"
#include "StateController.h"

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
	m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	


	if (m_pCurWeaponStatus->m_tWeaponInfo.m_iCurMagazine <= 0)
	{
		m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
	}

	m_bReloadFin = false;
}

void Player_Reload::UpdateState()
{
	DEBUG_LOG(L"Player Cur State : Reload");

	if (m_pCurWeaponStatus->m_tWeaponInfo.m_eType == WEAPON_TYPE::Weapon_Shotgun)
	{
		int temp = m_GameObject->Get_Component<AnimationController>()->Get_CurAnimIndex();
		if (temp != 2)
		{
			m_GameObject->Get_Component<AnimationController>()->Play(2);
		}
		else 
		{
			if (m_pCurWeaponStatus->m_tWeaponInfo.m_iCurMagazine <= 0)
			{
				m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
				return;
			}

			m_fShotGunTime += fTime;
			float fCurFrame = m_pAnimCtrl->Get_CurFrame();
			DEBUG_LOG(L"ShotGun Reload Frame : " + to_wstring(fCurFrame));
			
			if (m_fShotGunTime >= 0.6f && !m_bReloadFin)
			{
				--m_pCurWeaponStatus->m_tWeaponInfo.m_iCurMagazine;
				++m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet;
				
				if (m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet >= 6
					&& !m_bReloadFin)
				{
					m_pAnimCtrl->Set_Frame(3.6f);
					m_bReloadFin = true;
					//m_fShotGunTime = 0.f;
					//return;
				}

				m_fShotGunTime = 0.f;
			}

			if (m_GameObject->Get_Component<AnimationController>()->IsEnd())
			{
				m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
			}

		}

	}
	else 
	{
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


	
}

void Player_Reload::ExitState()
{

}
