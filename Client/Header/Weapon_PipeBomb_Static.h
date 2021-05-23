#pragma once

#ifndef _WEAPON_PIPEBOMB_STATIC_H_
#define _WEAPON_PIPEBOMB_STATIC_H_

#include "Component.h"

class Weapon_PipeBomb_Static :	public Component
{
public:
	struct Desc
	{
		Vector3		vPlayerPos;
		Vector3		vPlayerForward;
		Vector3		vPlayerDown;
		float		fSpd = 50;
		float		fMaxTime = 2.f;
		int			iDmg = 200;

	};
public:
	Weapon_PipeBomb_Static(Desc* _desc);
	virtual ~Weapon_PipeBomb_Static();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void Throw();

	void Bomb();
public:

public:

private:
	Vector3		m_vDir;
	float		m_fSpd;
	int			m_iDmg;
	float		m_fMaxTime;

	float		m_fBombTime = 0.f;
	bool		m_bCountDown = false;
};

#endif //_WEAPON_PIPEBOMB_STATIC_H_