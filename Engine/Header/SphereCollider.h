#pragma once

#ifndef _SPHERE_COLLIDER_H_
#define _SPHERE_COLLIDER_H_

#include "Engine_Include.h"

#include "Collider.h"

class DLL_STATE	SphereCollider :public Collider
{
public:
	struct Desc
	{
		float				fRadius = 1.f;
		Vector3				vOffset = { 0.f,0.f,0.f };
		_collision_Layer	iCollisionLayer = -1;
	};

public:
	SphereCollider(Desc* _desc);
	~SphereCollider();
	
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:

public:

private:
	GameObject*			m_pDebuging = nullptr;
	float				m_fRadius = 0.f;
	Vector3				m_vOffset = { 0.f,0.f,0.f };
	_collision_Layer	m_iCollisionLayer = -1;
};

#endif //_SPHERE_COLLIDER_H_