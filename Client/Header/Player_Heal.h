#pragma once

#ifndef _PLAYER_HEAL_H_
#define _PLAYER_HEAL_H_

#include "CState.h"

class Player_Attack;
class Player_Status;
class Mesh_Renderer;
class AnimationController;
class Weapon_Status;

class Player_Heal : public CState
{
public:
	Player_Heal();
	virtual ~Player_Heal();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
	Player_Attack*			m_pPlayerAttack = nullptr;
	Player_Status*			m_pPlayerStatus = nullptr;

	Weapon_Status*			m_pCurWeapon = nullptr;
	Mesh_Renderer*			m_pWeaponRenderer = nullptr;
	AnimationController*	m_pAnimCtrl = nullptr;


	bool m_bHeal = false;
};

#endif //_PLAYER_HEAL_H_