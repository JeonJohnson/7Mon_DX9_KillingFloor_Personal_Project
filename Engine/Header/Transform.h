#pragma once

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Engine_Define.h"

#include "Component.h"
#include "Cycle.h"


class _declspec(dllexport) Transform : /*public Cycle*/ public Component
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


#endif