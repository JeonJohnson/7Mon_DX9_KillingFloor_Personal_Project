#pragma once

#ifndef _PLAYER_ATTACK_H_
#define _PLAYER_ATTACK_H_

//#include "Include.h"
#include "stdafx.h"

#include "Component.h"

class StateController;
class Mesh_Renderer;
class AnimationController;
class Weapon;

class Player_Attack : public Component
{
public:
	struct Desc
	{
		wstring szInitWeapon = L""; //ÁÖ¹«±â, ¾øÀ¸¸é ±ÇÃÑ µê.
		

	};

public:
	Player_Attack(Desc* _desc);
	virtual ~Player_Attack();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public: /* Func */
	void			Fire();
	void			IronSight();
	void			Reload();
	void			Swap();

	void			SetUp();

public: /* Get */
	Weapon*					Get_CurWeapon();
	Mesh_Renderer*			Get_Renderer();
	AnimationController*	Get_AnimCtrl();
	int						Get_iCurIndex();
	vector<Weapon*>*		Get_WeaponsArr();

public: /* Set  */
	//void					Insert_Weapon();
	void					Set_CurWeapon(Weapon* _pWeapon);

private:
	StateController*	m_pStateCtlr = nullptr;
	Mesh_Renderer*		m_pWeaponRenderer = nullptr;
	AnimationController* m_pWeaponAnim = nullptr;

	vector<Weapon*>		m_arrWeapons[WEAPON_PRIORITY::Weapon_Priority_End];
	Weapon*				m_pCurWeapon;
	int					m_iNewWeaponIndex = 0;
	int					m_iCurWeaponIndex = -1;



	bool				m_bIronSight = false;



};

#endif //_PLAYER_ATTACK_H_
