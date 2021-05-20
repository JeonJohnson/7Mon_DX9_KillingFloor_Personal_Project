#pragma once
#include "Component.h"

class ShakeObject :	public Component
{
public:
	struct Desc
	{
		//float	fDuring;
		float	fInterval = 0.1f;
		float	fPower = 0.1f;
		int		iCount = 0;

	};
public:
	ShakeObject(Desc* _desc);
	virtual ~ShakeObject();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void Shaking(float _fPower, int _iCount, float _fInterval);
	//void Shaking()
public:

public:

private:
	float	m_fTime = 0.f;
	float	m_fInterval;
	int		m_iCount;
	float	m_fPower;
	Vector3 m_vStartPos;

};

