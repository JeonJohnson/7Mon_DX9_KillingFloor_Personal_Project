#pragma once

#ifndef _PLAYER_TEST_MOVE_H_
#define _PLAYER_TEST_MOVE_H_

#include "Include.h"

#include "Component.h"
class Player_TestMove :
	public Component
{
public:
	struct Desc
	{
		
	};
public:
	Player_TestMove(Desc* _desc);
	virtual ~Player_TestMove();

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