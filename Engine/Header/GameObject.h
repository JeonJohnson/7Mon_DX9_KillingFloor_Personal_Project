#pragma once

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Cycle.h"
class _declspec(dllexport) GameObject : public Cycle
{
public:
	GameObject();
	virtual ~GameObject();

	// Cycle을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
};

#endif