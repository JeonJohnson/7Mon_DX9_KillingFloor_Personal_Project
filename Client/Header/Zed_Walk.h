#pragma once

#ifndef _ZED_WALK_H_
#define _ZED_WALK_H_

#include "CState.h"
class Zed_Walk :public CState
{
public:
	Zed_Walk();
	virtual ~Zed_Walk();

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

#endif //_ZED_WALK_H_