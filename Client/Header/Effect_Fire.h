#pragma once

#ifndef _EFFECT_FIRE_H_
#define _EFFECT_FIRE_H_

#include "Component.h"

class VIBuffer_Renderer;

class Effect_Fire :	public Component
{
public:
	struct Desc
	{
		VIBuffer_Renderer*		pVibufferRenderer;
	};

public:
	Effect_Fire(Desc* _desc);
	virtual ~Effect_Fire();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:

private:
	VIBuffer_Renderer*	m_pRenderer = nullptr;
	float		m_fIndex = 0.f;
};

#endif //_EFFECT_FIRE_H_