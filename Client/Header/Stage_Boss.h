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
	void	Generate_Rand();
public:

private:
	float	m_fTime = 10.f;
	float	m_fGeneTime = 0.f;
	bool	m_bFadeOut = false;
	bool	m_bNextScene = false;
};


#endif//_STAGE_BOSS_H_