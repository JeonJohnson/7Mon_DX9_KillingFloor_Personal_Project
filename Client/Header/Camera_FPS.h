#pragma once

#ifndef _CAMERA_FPS_H_
#define _CAMERA_FPS_H_

#include "Component.h"

class Camera_FPS : public Component
{
public:
	struct Desc
	{
		float fSensitive = 10.f;
	};
public:
	explicit Camera_FPS(Desc* _desc);
	virtual ~Camera_FPS();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void Look();
	void Recoil(float _fRecoilPower);

public:

public:

private:
	float	m_fSensitive;

	float	m_fRotX = 0.f;
	float	m_fRotY = 0.f;
	float	m_fRotZ = 0.f;
};

#endif //_CAMERA_FPS_H_