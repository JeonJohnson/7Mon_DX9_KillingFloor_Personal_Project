#pragma once

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Engine_Define.h"

#include "Component.h"


class _declspec(dllexport) Transform : public Component
{
public:
	struct Desc
	{

	};

public:
	Transform(Desc* _desc);
	~Transform();

public:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
};


#endif