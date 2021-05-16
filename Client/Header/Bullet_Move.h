#pragma once

#ifndef _BULLET_MOVE_H_
#define _BULLET_MOVE_H_

#include "Component.h"

class SphereCollider;

class Bullet_Move : public Component
{
public:
	struct Desc
	{
		int		Dmg = 10;
		float Spd = 2000.f;
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
	void ColCheck_Zeds();

public:

public:

private:
	SphereCollider*		m_pCol;
	float	m_fTime = 0.f;
	int		m_iDmg = 0;
	float	m_fSpd = 150.f;

};

#endif //_BULLET_MOVE_H_