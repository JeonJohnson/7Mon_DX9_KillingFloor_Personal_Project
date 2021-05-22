#pragma once

#ifndef _PLAYER_FIRE_H_
#define _PLAYER_FIRE_H_

#include "CState.h"

//class Weapon;
class Weapon_Status;
class SphereCollider;
class Player_Attack;
class Camera_FPS;

class Player_Fire : public CState
{
public:
	Player_Fire();
	virtual ~Player_Fire();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:


private:
	Weapon_Status*		m_pCurWeaponStatus = nullptr;
	SphereCollider*		m_pPlayerCol = nullptr;
	Player_Attack*		m_pPlayerAttack = nullptr;
	Camera_FPS*			m_pCamera = nullptr;

};

#endif //_PLAYER_FIRE_H_