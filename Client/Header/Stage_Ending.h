#pragma once

#include "CState.h"

class Stage_Ending :	public CState
{
public:
	Stage_Ending();
	virtual ~Stage_Ending();

	// CState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	
public:
	GameObject*			m_pChopper = nullptr;
	Mesh_Renderer*		m_pChopperRender = nullptr;

	GameObject*	m_pPlayer = nullptr;
	float	m_fEndingTime = 0.f;
	//float	m_f연출용Time = 0.f;
};

