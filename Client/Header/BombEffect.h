#pragma once

#ifndef _BOMB_EFFECT_H_
#define _BOMB_EFFECT_H_

#include "Component.h"

class VIBuffer_Renderer;
class BombEffect : 	public Component
{
public:
	struct Desc
	{
		float fSmokeInitScale = 5.f;
	};
public:
	BombEffect(Desc* _desc);
	virtual ~BombEffect();

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
	GameObject*		m_pPlayer = nullptr;

	GameObject*		m_pExplosionObj = nullptr;
	VIBuffer_Renderer*	m_pExplosionBuffer = nullptr;
	float		m_fExplosionTime;

	GameObject*		m_pBigSmokeObj = nullptr;
	VIBuffer_Renderer*	m_pSmokeBuffer = nullptr;
	float	m_fSmokeScale;
	float	m_fSmokeSpd = 50.f;
	float	m_fSmokeTime;

};

#endif //_BOMB_EFFECT_H_