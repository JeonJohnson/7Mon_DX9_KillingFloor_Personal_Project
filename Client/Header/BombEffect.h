#pragma once

#ifndef _BOMB_EFFECT_H_
#define _BOMB_EFFECT_H_

#include "Component.h"
class BombEffect : 	public Component
{
public:
	struct Desc
	{
	
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
};

#endif //_BOMB_EFFECT_H_