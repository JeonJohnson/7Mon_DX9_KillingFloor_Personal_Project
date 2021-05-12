#include "stdafx.h"
#include "..\Header\WeaponManager.h"
#include "Weapon.h"

Implement_Singleton(WeaponManager)

WeaponManager::WeaponManager()
{
}


WeaponManager::~WeaponManager()
{
	for (auto& weapon : m_umALLWeapon)
	{
		if (weapon.second != nullptr)
		{
			Safe_Delete(weapon.second);
			weapon.second = nullptr;
		}
	}

	m_umALLWeapon.clear();
}

Weapon * WeaponManager::Get_Weapon(const wstring & _szWeaponName)
{
	auto iter_find = m_umALLWeapon.find(_szWeaponName);

	if (iter_find == m_umALLWeapon.end())
	{
		return nullptr;
	}
	
	return (*iter_find).second;
}

Weapon * WeaponManager::Get_CloneWeapon(const wstring & _szWeaponName)
{
	return nullptr;
}

void WeaponManager::Load_WeaponData(const wstring & _szDataPath)
{
	ifstream	readFile;
	readFile.open(_szDataPath.c_str());

	if (readFile.is_open())
	{
		
		while (!readFile.eof())
		{
			string str;
			getline(readFile, str);

			
		}

		readFile.close();
	}
}

void WeaponManager::Insert_Weapon(Weapon * _pWeapon)
{
	wstring szName = _pWeapon->m_szName;

	m_umALLWeapon.emplace(szName, _pWeapon);

}

void WeaponManager::Nogada_Data()
{
	Weapon* AK = new Weapon;
	AK->m_szName = L"AK47";
	AK->m_ePriority = WEAPON_PRIORITY::Weapon_Primary;
	AK->m_eType = WEAPON_TYPE::Weapon_Rifle;
	AK->m_iDmg = 40;
	AK->m_iBuck = 1;
	AK->m_bAuto = true;
	AK->m_iMaxBullet = 30;
	AK->m_iCurBullet = 30;
	AK->m_iMaxMagazine = 6;
	AK->m_iCurMagazine = 6;
	AK->m_fMaxRapid = 0.1f;
	AK->m_fCurRapid = 0.f;
	AK->m_fAccuracy = 1.f;
	AK->m_fRecoilForce = 10.f;
	AK->m_iWeight = 6;
	AK->m_iPrice = 1500;
	AK->m_iMagazinePrice = 40;
	Insert_Weapon(AK);

	Weapon* ShotGun = new Weapon;
	ShotGun->m_szName = L"ShotGun";
	ShotGun->m_ePriority = WEAPON_PRIORITY::Weapon_Primary;
	ShotGun->m_eType = WEAPON_TYPE::Weapon_Shotgun;
	ShotGun->m_iDmg = 30;
	ShotGun->m_iBuck = 6;
	ShotGun->m_bAuto = false;
	ShotGun->m_iMaxBullet = 6;
	ShotGun->m_iCurBullet = 6;
	ShotGun->m_iMaxMagazine = 60;
	ShotGun->m_iCurMagazine = 60;
	ShotGun->m_fMaxRapid = 1.f;
	ShotGun->m_fCurRapid = 0.f;
	ShotGun->m_fAccuracy = 1.f;
	ShotGun->m_fRecoilForce = 10.f;
	ShotGun->m_iWeight = 5;
	ShotGun->m_iPrice = 1000;
	ShotGun->m_iMagazinePrice = 30;
	Insert_Weapon(ShotGun);

	Weapon* M99 = new Weapon;
	M99->m_szName = L"M99";
	M99->m_ePriority = WEAPON_PRIORITY::Weapon_Primary;
	M99->m_eType = WEAPON_TYPE::Weapon_Sniper;
	M99->m_iDmg = 150;
	M99->m_iBuck = 1;
	M99->m_bAuto = false;
	M99->m_iMaxBullet = 1;
	M99->m_iCurBullet = 1;
	M99->m_iMaxMagazine = 20;
	M99->m_iCurMagazine = 20;
	M99->m_fMaxRapid = 2.f;
	M99->m_fCurRapid = 0.f;
	M99->m_fAccuracy = 1.f;
	M99->m_fRecoilForce = 10.f;
	M99->m_iWeight = 12;
	M99->m_iPrice = 2000;
	M99->m_iMagazinePrice = 50;
	Insert_Weapon(M99);

	Weapon* Beretta = new Weapon;
	Beretta->m_szName = L"Beretta";
	Beretta->m_ePriority = WEAPON_PRIORITY::Weapon_Secondary;
	Beretta->m_eType = WEAPON_TYPE::Weapon_Pistol;
	Beretta->m_iDmg = 20;
	Beretta->m_iBuck = 1;
	Beretta->m_bAuto = false;
	Beretta->m_iMaxBullet = 15;
	Beretta->m_iCurBullet = 15;
	Beretta->m_iMaxMagazine = 3;
	Beretta->m_iCurMagazine = 3;
	Beretta->m_fMaxRapid = 0.2f;
	Beretta->m_fCurRapid = 0.f;
	Beretta->m_fAccuracy = 1.f;
	Beretta->m_fRecoilForce = 10.f;
	Beretta->m_iWeight = 1;
	Beretta->m_iPrice = 0;
	Beretta->m_iMagazinePrice = 10;
	Insert_Weapon(Beretta);


	Weapon* Revolver = new Weapon;
	Revolver->m_szName = L"Revolver";
	Revolver->m_ePriority = WEAPON_PRIORITY::Weapon_Secondary;
	Revolver->m_eType = WEAPON_TYPE::Weapon_Pistol;
	Revolver->m_iDmg = 50;
	Revolver->m_iBuck = 1;
	Revolver->m_bAuto = false;
	Revolver->m_iMaxBullet = 6;
	Revolver->m_iCurBullet = 6;
	Revolver->m_iMaxMagazine = 5;
	Revolver->m_iCurMagazine = 5;
	Revolver->m_fMaxRapid = 0.4f;
	Revolver->m_fCurRapid = 0.f;
	Revolver->m_fAccuracy = 1.f;
	Revolver->m_fRecoilForce = 10.f;
	Revolver->m_iWeight = 3;
	Revolver->m_iPrice = 750;
	Revolver->m_iMagazinePrice = 50;
	Insert_Weapon(Revolver);

	Weapon* Knife = new Weapon;
	Knife->m_szName = L"Knife";
	Knife->m_ePriority = WEAPON_PRIORITY::Weapon_Melee;
	Knife->m_eType = WEAPON_TYPE::Weapon_Knife;
	Knife->m_iDmg = 35;
	Knife->m_iBuck = 1;
	Knife->m_bAuto = false;
	Knife->m_iMaxBullet = 0;
	Knife->m_iCurBullet = 0;
	Knife->m_iMaxMagazine = 0;
	Knife->m_iCurMagazine = 0;
	Knife->m_fMaxRapid = 0.6f;
	Knife->m_fCurRapid = 0.f;
	Knife->m_fAccuracy = 1.f;
	Knife->m_fRecoilForce = 0.f;
	Knife->m_iWeight = 0;
	Knife->m_iPrice = 0;
	Knife->m_iMagazinePrice = 0;
	Insert_Weapon(Knife);

}
