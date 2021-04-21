#pragma once

#ifndef _ANIM_CONTROLLER_H_
#define _ANIM_CONTROLLER_H_

#include "Engine_Include.h"

#include "Component.h"

class Anim_Controller :	public Component
{
public:
	Anim_Controller();
	virtual ~Anim_Controller();

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

#endif //_ANIM_CONTROLLER_H_