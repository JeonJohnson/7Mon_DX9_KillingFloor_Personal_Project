#pragma once

#ifndef _CAMERA_FREEMOVE_H_
#define _CAMERA_FREEMOVE_H_

#include "Tool_Include.h"

#include "Component.h"
class Camera_TestMove : public Component
{
public:
	struct Desc
	{
		float fMouseXSen = 60.f;
		float fMouseYSen = 60.f;

		float fMoveSpd = 10.f;
		float fSprintSpd = 10.f;
	};
public:
	Camera_TestMove(Desc* _desc);
	virtual ~Camera_TestMove();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void Move();
	void Look();

public:

private:
	float m_fMouseX_Sen;
	float m_fMouseY_Sen;

	float m_fMoveSpd;

	float	m_fOriginSpd;
	float	m_fSprintSpd;
};

#endif //_CAMERA_FREEMOVE_H_