#pragma once

#ifndef _MUZZLE_EFFECT_H_
#define _MUZZLE_EFFECT_H_

#include "Component.h"

#include "Include.h"

class MuzzleEffect : public Component
{
public:
	struct Desc
	{
		float fmaxsize = 3.5f;
		float fSpd = 100.f;

		GameObject* pPlayer = nullptr;
		Mesh* pMesh = nullptr;
	};

public:
	MuzzleEffect(Desc* _desc);
	virtual ~MuzzleEffect();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:
	void PositionUpdate();
	void ScaleUpdate();


private:
	bool	m_bOn = true;

	float	m_fMaxScale = 0;
	float	m_fSpd;

	GameObject*	m_pPlayer;
	Mesh*		m_pMesh;

};
#endif //_MUZZLE_EFFECT_H_