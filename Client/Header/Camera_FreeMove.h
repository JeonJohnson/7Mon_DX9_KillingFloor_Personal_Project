#pragma once

#ifndef _CAMERA_FREEMOVE_H_
#define _CAMERA_FREEMOVE_H_

#include "Component.h"
class Camera_FreeMove : public Component
{
public:
	struct Desc
	{
		

	};
public:
	Camera_FreeMove(Desc* _desc);
	virtual ~Camera_FreeMove();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
};

#endif //_CAMERA_FREEMOVE_H_