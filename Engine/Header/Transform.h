#pragma once

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Engine_Define.h"

#include "Cycle.h"

#include "Component.h"

//class Component;

class DLL_STATE Transform : /*public Cycle*/ public Component
{
public:
	struct Desc
	{

	};

public:
	Transform(Desc* _desc);
	~Transform();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;

};


#endif //_TRANSFORM_H_