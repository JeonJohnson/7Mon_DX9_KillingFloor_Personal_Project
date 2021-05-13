#include "stdafx.h"
#include "..\Header\Weapon_Status.h"


Weapon_Status::Weapon_Status(Desc * _desc)
{
	//m_tWeaponInfo.m_szName = _desc->szName;

	//m_tWeaponInfo.m_ePriority = _desc->ePriority;
	//m_tWeaponInfo.m_eType = _desc->eType;

	//m_tWeaponInfo.m_iDmg = _desc->iDmg;

	//m_tWeaponInfo.m_iBuck = _desc->iBuck;
	//m_tWeaponInfo.m_bAuto = _desc->bAuto;
	//
	//m_tWeaponInfo.m_iMaxBullet = _desc->iMaxBullet;
	//m_tWeaponInfo.m_iCurBullet = _desc->iCurBullet;
	//
	//m_tWeaponInfo.m_iMaxMagazine = _desc->iMaxMagazine;
	//m_tWeaponInfo.m_iCurMagazine = _desc->iCurMagazine;

	//m_tWeaponInfo.m_fMaxRapid = _desc->iMaxMagazine;
	//m_tWeaponInfo.m_fCurRapid = _desc->fCurRapid;

	//m_tWeaponInfo.m_fAccuracy = _desc->fAccuracy;

	//m_tWeaponInfo.m_fRecoilForce = _desc->fRecoilForce;

	//m_tWeaponInfo.m_iWeight = _desc->iWeight;
	//m_tWeaponInfo.m_iPrice = _desc->iPrice;
	//m_tWeaponInfo.m_iMagazinePrice = _desc->iMagazinePrice;

	m_tWeaponInfo = _desc->tWeaponStatus;
}

Weapon_Status::~Weapon_Status()
{
}

void Weapon_Status::Initialize()
{
}

void Weapon_Status::Update()
{
}

void Weapon_Status::LateUpdate()
{
}

void Weapon_Status::ReadyRender()
{
}

void Weapon_Status::Release()
{
}
