#pragma once

#ifndef _ZED_DEATH_H_
#define _ZED_DEATH_H_

#include "CState.h"

class AnimationController;

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

private:
	AnimationController*		m_pAnimCtrl = nullptr;
};

#endif //_ZED_DEATH_H_