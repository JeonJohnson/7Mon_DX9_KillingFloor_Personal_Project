#pragma once

#ifndef _STAGE_1_H_
#define _STAGE_1_H_

#include "CState.h"
#include "Include.h"

class Stage_1 : public CState

{
public:
	Stage_1();
	virtual ~Stage_1();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:
	void	Generate_Phase1();
	void	Generate_Phase2();
	void	Generate_Phase3();
	void	Generate_PhaseEnd();

public:

public:

private:
	float	m_fTime = 0.f;
	float	m_fGeneTime = 2.4f;
	bool	m_arrPattern[4] = { false };
	int		m_iCurPattern = 1;

	int		m_iZedCount = 6;
};

#endif//_STAGE_1_H_