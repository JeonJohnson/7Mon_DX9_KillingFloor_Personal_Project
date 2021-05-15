#pragma once

#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "Component.h"
class SkyBox :
	public Component
{
public:
	struct Desc
	{
	
	};

public:
	SkyBox(Desc* _desc);
	virtual ~SkyBox();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	Camera*			pMainCam = nullptr;
};

#endif//_SKYBOX_H_