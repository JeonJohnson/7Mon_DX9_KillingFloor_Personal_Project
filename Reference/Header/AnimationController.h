#pragma once

#ifndef _ANIMATION_CONTROLLER_H_
#define _ANIMATION_CONTROLLER_H_

#include "Engine_Include.h"

class DLL_STATE AnimationController
{
	//나중에는 얘를 컴포넌트로 바꿔서
	//일단 MeshRenderer컴포넌트를 가지고 있는 애에다가
	//이 컴포넌트도 달아준다음
	//애니메이션 정보가 있으면 재생하고 없으면 그냥 스태틱 매쉬로 출력하도록.

public:
	AnimationController();
	~AnimationController();

public:


public:
	HRESULT				Ready_Controller();
	
	void				Set_AnimationSet(int _i);
	void				Play_AnimationSet();

public: /* Get */

public: /* Set */
	LPD3DXANIMATIONCONTROLLER		Get_Controller();
	bool							Get_IsPlaying();

private:
	LPD3DXANIMATIONCONTROLLER		m_pAnimationController = nullptr;


	int		m_iCurrentTrack = -1;
	int		m_iNewTrack = -1;

	float	m_fAccTime = 0.f; //누적시간
	int		m_iOldIndex = 0;

	double	m_dPeriod = 0.0;


};

#endif //_ANIMATION_CONTROLLER_H_