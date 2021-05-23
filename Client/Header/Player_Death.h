#pragma once
#include "CState.h"
class Player_Death :	public CState
{
public:
	Player_Death();
	~Player_Death();

	// CState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

