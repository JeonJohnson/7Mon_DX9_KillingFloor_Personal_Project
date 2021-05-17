#pragma once

#ifndef _ZED_ATT_H_
#define _ZED_ATT_H_

#include "CState.h"

#include "Include.h"
class AnimationController;
class Zed;
class SphereCollider;

class Zed_Att :	public CState
{
public:
	Zed_Att();
	virtual ~Zed_Att();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

public:

private:
	AnimationController*	m_pAnimCtrl = nullptr;
	Zed*					m_pZedInfo = nullptr;
	int						m_iAttAnimIndex = 3;
	int						m_iStrongAnimIndex;
	
	SphereCollider*			m_pCol = nullptr;
	GameObject*				m_pPlayer = nullptr;
};

#endif //_ZED_ATT_H_