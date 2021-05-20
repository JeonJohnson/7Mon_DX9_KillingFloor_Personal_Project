#pragma once

#ifndef _STAGE_2_H_
#define _STAGE_2_H_

#include "CState.h"
class Stage_2 : public CState
{
public:
	Stage_2();
	virtual ~Stage_2();

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

#endif //_STAGE_2_H_