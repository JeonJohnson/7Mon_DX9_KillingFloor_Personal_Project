#pragma once

#ifndef _BULLET_MOVE_H_
#define _BULLET_MOVE_H_

#include "Component.h"
class Bullet_Move : public Component
{
public:
	struct Desc
	{
		float Spd = 550.f;
	};
public:
	Bullet_Move(Desc* _desc);
	virtual ~Bullet_Move();

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
	float m_fTime = 0.f;
	float m_fSpd = 150.f;

};

#endif //_BULLET_MOVE_H_