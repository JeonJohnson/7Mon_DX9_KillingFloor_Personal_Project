#pragma once

#ifndef _ZED_RUN_H_
#define _ZED_RUN_H_

#include "CState.h"

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
};

#endif//_ZED_RUN_H_