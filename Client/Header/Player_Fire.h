#pragma once

#ifndef _PLAYER_FIRE_H_
#define _PLAYER_FIRE_H_

#include "CState.h"

class Weapon;
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

private:
	Weapon*		m_pCurWeapon = nullptr;
};

#endif //_PLAYER_FIRE_H_