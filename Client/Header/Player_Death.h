#pragma once
#include "CState.h"
class Player_Death :	public CState
{
public:
	Player_Death();
	~Player_Death();

	// CState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

