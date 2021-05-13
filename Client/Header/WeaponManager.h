#pragma once

#ifndef _WEAPON_MANAGER_H_
#define _WEAPON_MANAGER_H_

#include "Include.h"

#include "Component.h"

class Weapon;

class WeaponManager : public Component
{
	//모든 무기 데이터들 모아놓을 곳.
public:
	struct Desc 
	{
	};


public:
	WeaponManager(Desc* _desc);
	virtual ~WeaponManager();
	
private:
	static WeaponManager*	m_pInstance;
public:
	static WeaponManager*	Get_Instance();
	static void				Destroy_Instance();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public: /* Func */
	void			Nogada_Data();


public: /* Get */
	GameObject*		Get_ProtoWeapon(const wstring& _szWeaponName);
	GameObject*		Get_CloneWeapon(const wstring& _szWeaponName);
	

public: /* Set */
	void			Insert_Weapon(const wstring& _szName, GameObject* _pWeapon );


private:
	unordered_map<wstring, GameObject*> m_umPrototypeWeapons;
	list<GameObject*>					m_listCloneWeapons;

//public:
//	Weapon*		Get_Weapon(const wstring& _szWeaponName);
//	Weapon*		Get_CloneWeapon(const wstring& _szWeaponName);
//
//public:
//	void Load_WeaponData(const wstring& _szDataPath);
//	void Insert_Weapon(Weapon* _pWeapon);
//	void Nogada_Data();
//
//private:
//	unordered_map<wstring, Weapon*>	m_umALLWeapon;
//	list<Weapon*> m_listCloneWeapons;
};

#endif //_WEAPON_MANAGER_H_