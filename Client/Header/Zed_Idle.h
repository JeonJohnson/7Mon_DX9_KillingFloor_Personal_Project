#pragma once

#ifndef _ZED_IDLE_H_
#define _ZED_IDLE_H_

#include "CState.h"
#include "Include.h"
class AnimationController;
class Zed;
class Zed_Idle : public CState
{
public:
	Zed_Idle();
	virtual ~Zed_Idle();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

public:

private:
	AnimationController*	m_pAnimCtrl = nullptr;
	Zed*				m_pZedInfo = nullptr;
	int						m_iIdleIndex = 0;

	int						m_iRandWalkRun = 0;
	//float					m_fDownAcc = 0.f;
};

#endif //_ZED_IDLE_H_