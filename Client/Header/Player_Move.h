#pragma once

#ifndef _PLYAER_MOVE_H_
#define _PLYAER_MOVE_H_

#include "Include.h"

#include "Component.h"

class Camera;

class Player_Move :	public Component
{
public:
	struct Desc
	{
		float	fWalkSpd = 20.f;
		float	fSprintSpd = 30.f;
		NaviMesh*	pNaviMesh = nullptr;
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
	void	Set_NaviMesh(NaviMesh* _NaviMesh);

private:
	float			m_fCurSpd = 0.f;
	float			m_fWalkSpd = 0.f;
	float			m_fSprintSpd = 0.f;

	NaviMesh*		m_pNaviMesh = nullptr;
	int				m_icurCellIndex = 0;


};

#endif //_PLYAER_MOVE_H_