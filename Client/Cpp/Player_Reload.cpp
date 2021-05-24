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

	if (m_pPlayerAttack == nullptr)
	{
		m_pPlayerAttack = m_GameObject->Get_Component<Player_Attack>();
	}

	m_pCurWeaponStatus = m_pPlayerAttack->Get_CurWeaponStatus();
	m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	

	if (m_pCurWeaponStatus->m_tWeaponInfo.m_iCurMagazine <= 0
		|| m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet 
		>= m_pCurWeaponStatus->m_tWeaponInfo.m_iMaxBullet)
	{
		EngineFunction->OverlapPlay_Sound(L"Weapon_DryFire.wav", SoundCH_PLAYER_FIRE);
		m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
		return;
	}

	m_bIronSight = m_pPlayerAttack ->Get_IronSight();
	m_pPlayerAttack->Set_IronSight(false);

	m_bFire			= false;
	m_bReloadFin	= false;
	m_fShotGunTime	= 0.f;

	for (int i = 0; i < 3; ++i)
	{
		m_bAK_Sound[i] = false;
	}
	for (int i = 0; i < 4; ++i)
	{
		m_bBeretta_Sound[i] = false;
	}
	m_bShotGun_Sound = false;
}

void Player_Reload::UpdateState()
{
	DEBUG_LOG(L"Player Cur State : Reload");

	DEBUG_LOG(L"Cur Frame: " + to_wstring(m_pAnimCtrl->Get_CurFrame())
		+ L" / Max Frame : " + to_wstring(m_pAnimCtrl->Get_MaxFrame()));

	AK47_Reload_Sound();
	Beretta_Reload_Sound();
	ShotGun_Reload_Sound();

	if (m_pCurWeaponStatus->m_tWeaponInfo.m_eType == WEAPON_TYPE::Weapon_Shotgun)
	{
		//if (m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet >=
		//	m_pCurWeaponStatus->m_tWeaponInfo.m_iMaxBullet)
		//{
		//	m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
		//	return;
		//}

		int temp = m_GameObject->Get_Component<AnimationController>()->Get_CurAnimIndex();

		if (temp != 2)
		{
			m_pAnimCtrl->Set_AnimSpd(1.25f);
			m_GameObject->Get_Component<AnimationController>()->Play(2);
		}
		else 
		{
			if (MouseDown(KEY_STATE_LMouse) && !m_bFire 
				&& m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet >0)
			{
				if (m_pAnimCtrl->Get_CurFrame() < 3.6f)
				{
					
					m_pAnimCtrl->Set_Frame(3.6f);
				}
				m_bReloadFin = true;
				m_bFire = true;
				//m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Fire");
			}

			if (m_pCurWeaponStatus->m_tWeaponInfo.m_iCurMagazine <= 0)
			{
				//if (m_bIronSight)
				//{
				//	m_pPlayerAttack->On_IronSight();
				//}
				m_pAnimCtrl->Set_AnimSpd(1.0);
				m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
				
				return; 
			}

			m_fShotGunTime += fTime * m_pAnimCtrl->Get_AnimSpd();
			float fCurFrame = (float)m_pAnimCtrl->Get_CurFrame();
			DEBUG_LOG(L"ShotGun Reload Frame : " + to_wstring(fCurFrame));
			
			if (m_fShotGunTime >= 0.6f && !m_bReloadFin)
			{
				int iRand = rand() % 3 + 1;
				EngineFunction->OverlapPlay_Sound(L"ShotGun_Bullet_Insert_0" + to_wstring(iRand) +L".wav", SoundCH_PLAYER_FIRE);
				--m_pCurWeaponStatus->m_tWeaponInfo.m_iCurMagazine;
				++m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet;

				if (m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet 
					>= m_pCurWeaponStatus->m_tWeaponInfo.m_iMaxBullet
					&& !m_bReloadFin)
				{
					m_pAnimCtrl->Set_Frame(3.6f);
					//EngineFunction->OverlapPlay_Sound(L"ShotGun_Pump.wav", SoundCH_PLAYER_FIRE);
					m_bReloadFin = true;
					//m_fShotGunTime = 0.f;
					//return;
				}

				m_fShotGunTime = 0.f;
			}

			if (m_GameObject->Get_Component<AnimationController>()->IsEnd())
			{
				//if (m_bFire)
				//{
				//	m_pPlayerAttack->Set_IronSight(m_bIronSight);
				//	m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Fire");
				//}
				//else
				//{
				//if (m_bIronSight)
				//{
				//	m_pPlayerAttack->On_IronSight();
				//}
					m_pAnimCtrl->Set_AnimSpd(1.0);
					m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
				//}
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

			//if (m_bIronSight)
			//{
			//	m_pPlayerAttack->On_IronSight();
			//}
			m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
		}
	
	}


	
}

void Player_Reload::ExitState()
{

}

void Player_Reload::AK47_Reload_Sound()
{
	if (m_pCurWeaponStatus->m_tWeaponInfo.m_szName == L"AK47")
	{
		float curFrame = m_pAnimCtrl->Get_CurFrame();

		if(curFrame >= 0.6f && !m_bAK_Sound[0])
		{ 
			EngineFunction->OverlapPlay_Sound(L"AK47_Reload_011.wav", SoundCH_PLAYER_FIRE);
			m_bAK_Sound[0] = true;
		}

		if (curFrame >= 1.9f && !m_bAK_Sound[1])
		{
			EngineFunction->OverlapPlay_Sound(L"AK47_Reload_047.wav", SoundCH_PLAYER_FIRE);
			m_bAK_Sound[1] = true;
		}

		if (curFrame >= 2.4f && !m_bAK_Sound[2])
		{
			EngineFunction->OverlapPlay_Sound(L"AK47_Reload_071.wav", SoundCH_PLAYER_FIRE);
			m_bAK_Sound[2] = true;
		}

	}

}

void Player_Reload::Beretta_Reload_Sound()
{
	if (m_pCurWeaponStatus->m_tWeaponInfo.m_szName == L"Beretta")
	{
		float curFrame = m_pAnimCtrl->Get_CurFrame();

		if (curFrame >= 0.0f && !m_bBeretta_Sound[0])
		{
			EngineFunction->OverlapPlay_Sound(L"Beretta_Reload_000.wav", SoundCH_PLAYER_FIRE);
			m_bBeretta_Sound[0] = true;
		}

		if (curFrame >= 0.9f && !m_bBeretta_Sound[1])
		{
			EngineFunction->OverlapPlay_Sound(L"Beretta_Reload_026.wav", SoundCH_PLAYER_FIRE);
			m_bBeretta_Sound[1] = true;
		}

		if (curFrame >= 1.2f && !m_bBeretta_Sound[2])
		{
			EngineFunction->OverlapPlay_Sound(L"Beretta_Reload_036.wav", SoundCH_PLAYER_FIRE);
			m_bBeretta_Sound[2] = true;
		}

		if (curFrame >= 1.6f && !m_bBeretta_Sound[3])
		{
			EngineFunction->OverlapPlay_Sound(L"Beretta_Reload_049.wav", SoundCH_PLAYER_FIRE);
			m_bBeretta_Sound[3] = true;
		}
	}
}

void Player_Reload::ShotGun_Reload_Sound()
{

	if (m_pCurWeaponStatus->m_tWeaponInfo.m_szName == L"ShotGun")
	{
		float curFrame = m_pAnimCtrl->Get_CurFrame();

		if (curFrame >= 3.8f && !m_bShotGun_Sound)
		{
			EngineFunction->OverlapPlay_Sound(L"ShotGun_Pump.wav", SoundCH_PLAYER_FIRE);
			m_bShotGun_Sound = true;
		}
	}
}
