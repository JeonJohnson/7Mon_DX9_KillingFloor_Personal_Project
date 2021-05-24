#pragma once

#ifndef _PLAYER_ATTACK_H_
#define _PLAYER_ATTACK_H_

//#include "Include.h"
#include "stdafx.h"

#include "Component.h"

class StateController;
class Mesh_Renderer;
class AnimationController;
class Weapon_Status;
class Player_Status;

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
	void			ChangeWeapon();

	void			Heal();
	void			Bomb_Drop();

	void			Drop();

	void			SetUp();

	void			Player_Ending();
public: /* Get */
	GameObject*					Get_CurWeapon();
	Weapon_Status*				Get_CurWeaponStatus();
	Mesh_Renderer*				Get_Renderer();
	AnimationController*		Get_AnimCtrl();
	int							Get_iCurKind();
	vector<GameObject*>*		Get_WeaponsArr();

	GameObject*					Get_HealInjector();
	Weapon_Status*				Get_HealInjector_Status();

	GameObject*					Get_PipeBomb();
	Weapon_Status*				Get_PipeBomb_Status();

	bool						Get_IronSight();
public: /* Set  */
	//void					Insert_Weapon();
	void					Set_CurWeapon(GameObject* _pWeapon);
	void					Set_IronSight(bool _OnOff);

	void					On_IronSight();
private:

	StateController*		m_pStateCtlr = nullptr;
	Mesh_Renderer*			m_pWeaponRenderer = nullptr;
	AnimationController*	m_pWeaponAnim = nullptr;

	Player_Status*			m_pPlayerStatus = nullptr;

	GameObject*				m_pHealInjector = nullptr;
	Weapon_Status*			m_pHealInjector_Status = nullptr;
	float					m_fHealTime = 0.f;
	GameObject*				m_pBomb = nullptr;
	Weapon_Status*			m_pBomb_Status = nullptr;

	vector<GameObject*>		m_arrWeapons[WEAPON_PRIORITY::Weapon_Priority_End];
	GameObject*				m_pCurWeapon;
	Weapon_Status*			m_pCurWeaponStatus;
	int						m_iNewWeaponKind = 0;
	int						m_iCurWeaponKind = -1;

	int						m_iCurKindIndex = 0;


	bool					m_bIronSight = false;
	float					m_fIronSpdX = 0.f;
	float					m_fIronSpdZ = 0.f;

	
	int					m_iTest = 1;

	bool				m_bEnding = false;

};

#endif //_PLAYER_ATTACK_H_
