#pragma once

#include "Component.h"

class SphereCollider;
class BombExplosion : public Component
{
public:
	struct Desc
	{
		Vector3 vPos;
		int iDmg;
		float fLiveTime;
	};
public:
	BombExplosion(Desc* _desc);
	virtual ~BombExplosion();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	SphereCollider*		m_pCol = nullptr;
	int			m_iDmg = 0;

	float m_fTime = 0.f;
	float m_fMaxTime;
};

