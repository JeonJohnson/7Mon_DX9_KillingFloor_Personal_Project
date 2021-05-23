#pragma once
#include "CState.h"
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
};

