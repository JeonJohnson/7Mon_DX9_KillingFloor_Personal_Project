#pragma once

#ifndef _PLAYER_RELOAD_H_
#define _PLAYER_RELOAD_H_

#include "CState.h"

class Weapon_Status;
class AnimationController;
class Player_Attack;

class Player_Reload :	public CState
{
public:
	Player_Reload();
	virtual ~Player_Reload();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

private:
	Weapon_Status*			m_pCurWeaponStatus = nullptr;
	AnimationController*	m_pAnimCtrl = nullptr;
	Player_Attack*			m_pPlayerAttack = nullptr;
	
	float					m_fShotGunTime = 0.f;
	bool					m_bReloadFin = false;
	bool					m_bFire = false;

	bool					m_bIronSight = false;

};

#endif //_PLAYER_RELOAD_H_