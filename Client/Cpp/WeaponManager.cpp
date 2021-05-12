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
}

void WeaponManager::Insert_Weapon(Weapon * _pWeapon)
{
	wstring szName = _pWeapon->m_szName;

	m_umALLWeapon.emplace(szName, _pWeapon);

}
