#pragma once
#ifndef _ANIMATION_CONTROLLER_H_
#define _ANIMATION_CONTROLLER_H_

#include "Engine_Include.h"

#include "Component.h"

class DLL_STATE AnimationController : public Component
{
public:
	struct Desc
	{
		


	};

public:
	explicit AnimationController(Desc* _desc);
	virtual ~AnimationController();

public:

public:

public:

public:

private:
	LPD3DXANIMATIONCONTROLLER		m_pAnimCtrl = nullptr;
	LPD3DXANIMATIONSET				m_pAnimSet = nullptr;

	int								m_iCurIndex = 9999;
	int								m_iMaxIndex = 0;
	
	int								m_iCurTrackIndex = 0;
	int								m_iNewTrackIndex = 1;
	LPD3DXTRACK_DESC				m_pCurTrackInfo = nullptr;




};

#endif //_ANIMATION_CONTROLLER_H_