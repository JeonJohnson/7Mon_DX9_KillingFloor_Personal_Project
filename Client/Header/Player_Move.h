#pragma once

#ifndef _PLAYER_MOVE_H_
#define _PLAYER_MOVE_H_

#include "Include.h"

#include "Component.h"
class Player_Move :
	public Component
{
public:
	struct Desc
	{
		
	};
public:
	Player_Move(Desc* _desc);
	virtual ~Player_Move();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public: /* functions */
	void Move_Test();

public: /* Get */ 

public: /* Set */


public:
	float	m_fWalkSpd;
	float	m_fSprintSpd;
};

#endif //_PLAYER_MOVE_H_