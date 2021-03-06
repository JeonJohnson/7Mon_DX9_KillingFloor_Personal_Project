#pragma once

#ifndef _PLAYER_SWAP_H_
#define _PLAYER_SWAP_H_

#include "CState.h"

class Player_Attack;
class Weapon_Status;
class Player_Swap : public CState
{
public:
	Player_Swap();
	virtual ~Player_Swap();

	// CState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
	
public:
	Player_Attack*		m_pPlayerAttack = nullptr;
	Weapon_Status*		m_pCurWeaponStatus = nullptr;

};

#endif //_PLAYER_SWAP_H_