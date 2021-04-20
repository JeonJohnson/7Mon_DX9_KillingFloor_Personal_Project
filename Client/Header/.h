#pragma once

#ifndef _ANIMATIONTEST_H_
#define _ANIMATIONTEST_H_

#include "Component.h"

class AnimationTest :	public Component
{
public:
	struct Desc
	{


	};

public:
	AnimationTest(Desc* _desc);
	virtual ~AnimationTest();

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


#endif //_ANIMATIONTEST_H_