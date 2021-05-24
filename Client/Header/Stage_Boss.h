#pragma once

#ifndef _STAGE_BOSS_H_
#define _STAGE_BOSS_H_

#include "CState.h"
class Stage_Boss : public CState
{
public:
	Stage_Boss();
	virtual ~Stage_Boss();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:
	void	StageBoss_Skip();
public:

public:

private:
};


#endif//_STAGE_BOSS_H_