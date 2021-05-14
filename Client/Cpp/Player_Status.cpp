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
