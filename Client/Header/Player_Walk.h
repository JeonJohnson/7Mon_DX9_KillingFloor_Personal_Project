#pragma once

#ifndef _PLAYER_WALK_H_
#define _PLAYER_WALK_H_

#include "CState.h"

class Player_Walk :	public CState
{
public:
	Player_Walk();
	virtual ~Player_Walk();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

#endif //_PLAYER_WALK_H_