#pragma once

#ifndef _CAMERA_FREEMOVE_H_
#define _CAMERA_FREEMOVE_H_

#include "Component.h"
class Camera_FreeMove : public Component
{
public:
	struct Desc
	{
		float fMouseXSen = 40.f;
		float fMouseYSen = 40.f;

		float fMoveSpd = 10.f;

	};
public:
	Camera_FreeMove(Desc* _desc);
	virtual ~Camera_FreeMove();

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

};

#endif //_CAMERA_FREEMOVE_H_