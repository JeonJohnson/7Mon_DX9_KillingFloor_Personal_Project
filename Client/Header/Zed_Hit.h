#pragma once

#ifndef _ZED_HIT_H_
#define _ZED_HIT_H_

#include "CState.h"
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

public:

private:

};

#endif //_ZED_HIT_H_