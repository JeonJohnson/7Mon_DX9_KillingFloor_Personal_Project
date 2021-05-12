#pragma once

#ifndef _PLAYER_SWAP_H_
#define _PLAYER_SWAP_H_

#include "CState.h"

class Player_Attack;

class Player_Swap : public CState
{
public:
	Player_Swap();
	virtual ~Player_Swap();

	// CState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
	
public:
	Player_Attack*		m_pPlayerAttack = nullptr;
};

#endif //_PLAYER_SWAP_H_