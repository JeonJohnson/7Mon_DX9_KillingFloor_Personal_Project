#pragma once

#ifndef _ZED_INIT_WALK_H_
#define _ZED_INIT_WALK_H_

#include "CState.h"
class Zed_InitWalk : public CState
{
public:
	Zed_InitWalk();
	virtual ~Zed_InitWalk();

	// CState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;


private:
	float m_fRandTime;
};

#endif //_ZED_INIT_WALK_H_