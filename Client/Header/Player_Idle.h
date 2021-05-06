#pragma once

#ifndef _PLAYER_IDLE_H_
#define _PLAYER_IDLE_H_


#include "CState.h"

class Player_Idle : public CState
{
public:
	Player_Idle();
	virtual ~Player_Idle();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;


public:

public:

public:

public:

private:
	class AnimationController*		m_pAnimCtrl = nullptr;
	class Player_TestAttack*		m_pWeapon = nullptr;
};

#endif // _PLAYER_IDLE_H_