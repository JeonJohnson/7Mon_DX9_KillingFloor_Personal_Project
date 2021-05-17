#pragma once

#ifndef _ZED_RUN_H_
#define _ZED_RUN_H_

#include "CState.h"
#include "Include.h"
class AnimationController;
class Zed;
class Zed_Run :	public CState
{
public:
	Zed_Run();
	virtual ~Zed_Run();

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
	int						m_iRunIndex = 2;

	float					m_fRunFullTime = 0.f;
	float					m_fRunCurTime = 0.f;
};

#endif//_ZED_RUN_H_