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
	void	Generate_Phase1();
	void	Generate_Phase2();
	void	Generate_PhaseEnd();

public:
	void	Stage2_Skip();


private:
	float	m_fTime = 0.f;
	float	m_fGeneTime = 1.4f;
	bool	m_arrPattern[3] = { false };
	int		m_iCurPattern = 1;

	int		m_iZedTotalCount = 30;
	int		m_iZedCurCount = 0;
	int		m_iZedCount[3] = {10,10,10};
};

#endif //_STAGE_2_H_