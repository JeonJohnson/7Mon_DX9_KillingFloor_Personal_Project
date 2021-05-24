#pragma once

#ifndef _ZED_HIT_H_
#define _ZED_HIT_H_

#include "CState.h"

#include "Include.h"
class AnimationController;
class Zed;
class Zed_Hit :	public CState
{
public:
	Zed_Hit();
	virtual ~Zed_Hit();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	void Hit_Sound();
public:

private:
	AnimationController*	m_pAnimCtrl = nullptr;
	Zed*				m_pZedInfo = nullptr;
	int		m_iHitAnimIndex = 4;
};

#endif //_ZED_HIT_H_