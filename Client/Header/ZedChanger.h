#pragma once

#ifndef _ZED_CHANGER_H_
#define _ZED_CHANGER_H_

#include "Component.h"

class UI;

class ZedChanger :	public Component
{

public:
	struct Desc
	{
		UI* ZedSprite = nullptr;

		int		iPastNum = 0;
		float	fMaxTime = 3.f;
	};

public:
	ZedChanger(Desc* _desc);
	virtual ~ZedChanger();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:

private:
	UI*		m_pZedSprite = nullptr;
	float	m_fCurTime = 0.f;
	float	m_fMaxTime = 0.f;

	
	int		m_iRandNum = 2;
	int		m_iPastNum = 0;

	bool	m_bChange = false;
	bool	m_bFadeOn = false;

};

#endif //_ZED_CHANGER_H_