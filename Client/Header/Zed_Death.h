#pragma once

#ifndef _ZED_DEATH_H_
#define _ZED_DEATH_H_

#include "CState.h"

#include "Include.h"
class AnimationController;
class Zed;
class Zed_Death : public CState
{
public:
	Zed_Death();
	virtual ~Zed_Death();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	void Death_Sound();

private:
	AnimationController*	m_pAnimCtrl = nullptr;
	Zed*				m_pZedInfo = nullptr;
	int						m_iDeathIndex = 6;

	float					m_fDownAcc = 0.f;

	Vector3 vRight;
};

#endif //_ZED_DEATH_H_