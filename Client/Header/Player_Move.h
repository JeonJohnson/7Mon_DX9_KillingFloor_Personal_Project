#pragma once

#ifndef _PLYAER_MOVE_H_
#define _PLYAER_MOVE_H_

#include "Component.h"
class Player_Move :	public Component
{
public:
	struct Desc
	{
		float	fWalkSpd = 20.f;
		float	fSprintSpd = 30.f;
	};

public:
	explicit Player_Move(Desc* _desc);
	virtual ~Player_Move();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void Move();
public:

public:

private:
	float	m_fCurSpd = 0.f;
	float	m_fWalkSpd = 0.f;
	float	m_fSprintSpd = 0.f;



};

#endif //_PLYAER_MOVE_H_