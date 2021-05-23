#pragma once

#ifndef _PlAYER_BOMB_H_
#define _PlAYER_BOMB_H_

#include "CState.h"

class Player_Attack;
class Player_Status;
class Weapon_Status;
class Mesh_Renderer;
class AnimationController;

class Player_Bomb :	public CState
{
public:
	Player_Bomb();
	virtual ~Player_Bomb();

	// CState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:


public:

public:

private:

	Player_Attack*			m_pPlayerAttack = nullptr;
	Player_Status*			m_pPlayerStatus = nullptr;

	Weapon_Status*			m_pBombStatus = nullptr;
	Weapon_Status*			m_pCurWeapon = nullptr;
	Mesh_Renderer*			m_pWeaponRenderer = nullptr;
	AnimationController*	m_pAnimCtrl = nullptr;
};

#endif //_PlAYER_BOMB_H_