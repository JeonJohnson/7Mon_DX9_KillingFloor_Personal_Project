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
	explicit AnimationController();
	explicit AnimationController(LPD3DXANIMATIONCONTROLLER pAniCtrl);
	explicit AnimationController(const AnimationController& rhs);
	~AnimationController();

public:


public:
	HRESULT				Ready_Controller();
	
	void				Set_AnimationSet(int _iIndex);
	void				Play_AnimationSet();

public: /* Get */
	void		Set_AnimContoller(LPD3DXANIMATIONCONTROLLER _controller);

public: /* Set */
	LPD3DXANIMATIONCONTROLLER		Get_Controller();
	bool							Get_IsPlaying();

private:
	LPD3DXANIMATIONCONTROLLER		m_pAnimationController = nullptr;

	//트랙 -> 애니메이션을 재생할 틀
	//보통 1개~2개씀
	//우리는 2개씀. 애니메이션 블랜딩을 위해서.
	int		m_iCurrentTrack = 0; 
	int		m_iNewTrack = 1; //

	float	m_fAccTime = 0.f; //누적시간, 키 프레임이라고 보면 될듯
	int		m_iOldIndex = 999; //재생중인 인덱스 

	double	m_dPeriod = 0.0; //현재 애니메이션의 전체 재생 시간(키 프레임?)

	float	m_fAnimSpd = 1.f;
};

#endif //_ANIMATION_CONTROLLER_H_