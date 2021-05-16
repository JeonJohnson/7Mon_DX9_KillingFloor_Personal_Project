#pragma once

#ifndef _ZED_ATT_H_
#define _ZED_ATT_H_

#include "CState.h"
class Zed_Att :	public CState
{
public:
	Zed_Att();
	virtual ~Zed_Att();

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

#endif //_ZED_ATT_H_