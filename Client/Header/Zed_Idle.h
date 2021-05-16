#pragma once

#ifndef _ZED_IDLE_H_
#define _ZED_IDLE_H_

#include "CState.h"
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

};

#endif //_ZED_IDLE_H_