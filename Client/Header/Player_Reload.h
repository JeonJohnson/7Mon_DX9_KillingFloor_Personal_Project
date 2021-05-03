#pragma once

#ifndef _PLAYER_RELOAD_H_
#define _PLAYER_RELOAD_H_

#include "CState.h"

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

};

#endif //_PLAYER_RELOAD_H_