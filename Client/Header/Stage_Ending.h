#pragma once

#include "CState.h"

class Stage_Ending :	public CState
{
public:
	Stage_Ending();
	virtual ~Stage_Ending();

	// CState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	
public:
	GameObject*	m_pChopper = nullptr;
};

