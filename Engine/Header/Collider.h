#pragma once

#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "Engine_Include.h"

#include "Component.h"

class DLL_STATE	Collider abstract  : public Component
{
public:


public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	//bool	CollisionCheck(_collision_Layer _iColLayer, const wstring& _szObjName);
};

#endif //_COLLIDER_H_