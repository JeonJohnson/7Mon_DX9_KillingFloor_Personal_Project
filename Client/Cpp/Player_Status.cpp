#include "stdafx.h"
#include "..\Header\Player_Status.h"

#include "Player_Attack.h"
#include "Weapon_Status.h"

#include "HudManager.h"

Player_Status::Player_Status(Desc * _desc)
{
	m_tPlayerStatus = _desc->tPlayerStatus;

}

Player_Status::~Player_Status()
{
}

void Player_Status::Initialize()
{
}

void Player_Status::Update()
{
	auto PlayerAttack = m_GameObject->Get_Component<Player_Attack>();
	
	Heal();

	int weight = 0;

	for (int i = 0; i < 3; ++i) 
	{
		for (auto& weapon : PlayerAttack->Get_WeaponsArr()[i])
		{
			weight += weapon->Get_Component<Weapon_Status>()->m_tWeaponInfo.m_iWeight;
		}
	}
	m_tPlayerStatus.m_iCurWeight = weight;


	HudManager::Get_Instance()->Set_TextHp(m_tPlayerStatus.m_iCurHp);
	HudManager::Get_Instance()->Set_TextArmor(m_tPlayerStatus.m_iCurArmor);
	HudManager::Get_Instance()->Set_TextWeight(m_tPlayerStatus.m_iCurWeight);
	HudManager::Get_Instance()->Set_TextMoney(m_tPlayerStatus.m_iGold);
}

void Player_Status::LateUpdate()
{
}

void Player_Status::ReadyRender()
{
}

void Player_Status::Release()
{
}

void Player_Status::Damaged(int _iDmg)
{
	int iHpDmg;

	int	iRand = rand() % 16;
	//24~32
	int Channel = rand() % 8 + 24;
	EngineFunction->OverlapPlay_Sound(L"All_Hit" + to_wstring(iRand) + L".wav", Channel);

	iRand = rand() % 12;
	//PlayerHit0~12
	EngineFunction->Play_Sound(L"PlayerHit" + to_wstring(iRand) + L".wav", SoundCH_PLAYER_HIT);

	if (m_tPlayerStatus.m_iCurArmor > 0)
	{
		m_tPlayerStatus.m_iCurArmor -= _iDmg;

		if (m_tPlayerStatus.m_iCurArmor < 0)
		{
			iHpDmg = m_tPlayerStatus.m_iCurArmor;
			m_tPlayerStatus.m_iCurArmor = 0;

			m_tPlayerStatus.m_iCurHp -= iHpDmg;

			if (m_tPlayerStatus.m_iCurHp < 0)
			{
				m_tPlayerStatus.m_iCurHp = 0;
			}
		}
	}
	else 
	{
		m_tPlayerStatus.m_iCurHp -= _iDmg;

		if (m_tPlayerStatus.m_iCurHp < 0)
		{
			m_tPlayerStatus.m_iCurHp = 0;
		}
	}
}

void Player_Status::Heal()
{
	if (m_bHeal)
	{
		if (m_tPlayerStatus.m_iCurHp <= 100)
		{
			m_fHealTime += fTime * 7.5f;

			if (m_fHealTime >= 1.f)
			{
				++m_tPlayerStatus.m_iCurHp;
				--m_iHealAmount;
				m_fHealTime = 0.f;
			}
		}
		
		if (m_tPlayerStatus.m_iCurHp > 100 || m_iHealAmount <= 0)
		{
			if (m_tPlayerStatus.m_iCurHp > 100)
			{
				m_tPlayerStatus.m_iCurHp = 100;
			}
			Set_Heal(false);
		}
	}

}

void Player_Status::Set_Heal(bool _OnOff)
{
	m_fHealTime = 0.f;
	m_iHealAmount = 50;
	m_bHeal = _OnOff;
}


PLAYER_INFO Player_Status::Get_PlayerStatus()
{
	return m_tPlayerStatus;
}
