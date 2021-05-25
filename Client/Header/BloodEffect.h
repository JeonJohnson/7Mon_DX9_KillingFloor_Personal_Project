#pragma once

#include "Component.h"

class VIBuffer_Renderer;
class BloodEffect :	public Component
{
public:
	struct Desc
	{
		float fBloodInitScale = 7.5f;

	};
public:
	BloodEffect(Desc* _desc);
	virtual ~BloodEffect();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:

private:

	GameObject*		m_pPlayer = nullptr;

	GameObject*			m_pBloodObj = nullptr;
	VIBuffer_Renderer*	m_pBloodBuffer = nullptr;

	float	m_fBloodScale;
	float	m_fBloodSpd = 2.f;
	float	m_fBloodTime = 0.f;

};

