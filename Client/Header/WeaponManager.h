#pragma once

#ifndef _WEAPON_MANAGER_H_
#define _WEAPON_MANAGER_H_

class Weapon;

class WeaponManager
{
	//모든 무기 데이터들 모아놓을 곳.

	Declare_Singleton(WeaponManager)

private:
	WeaponManager();
	~WeaponManager();

public:

public:

public:
	Weapon*		Get_Weapon(const wstring& _szWeaponName);
	Weapon*		Get_CloneWeapon(const wstring& _szWeaponName);

public:
	void Load_WeaponData(const wstring& _szDataPath);
	void Insert_Weapon(Weapon* _pWeapon);

private:
	unordered_map<wstring, Weapon*>	m_umALLWeapon;
};

#endif //_WEAPON_MANAGER_H_