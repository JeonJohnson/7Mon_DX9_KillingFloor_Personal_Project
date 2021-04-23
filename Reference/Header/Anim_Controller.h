#pragma once

#ifndef _ANIM_CONTROLLER_H_
#define _ANIM_CONTROLLER_H_

#include "Engine_Include.h"

#include "Component.h"

class DLL_STATE Anim_Controller :	public Component
{
public:
	struct Desc
	{
		int		iInitIndex = 0;
		float	fAnimSpd = 1.f;

		GameObject*		pGameObject;
	};

public:
	explicit Anim_Controller(Desc* _desc);
	virtual ~Anim_Controller();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public: /* Function */
	HRESULT			Setup_AnimController(GameObject* _pGameObject);
	void			Play_Animation();
	void			Stop_Animation();

public: /* Get */
	LPD3DXANIMATIONCONTROLLER		Get_AnimController() const;
	int								Get_CurIndex() const;
	int								Get_MaxIndex() const;
	float							Get_AnimCurSpd() const;
	bool							Get_Playing() ;

public: /* Set */
	void							Set_AnimController(LPD3DXANIMATIONCONTROLLER _pAnimCtrl);
	void							Set_AnimIndex(int _iNewIndex);
	void							Set_AnimSpd(float _fAnimSpd);

private:
	LPD3DXANIMATIONCONTROLLER		m_pAnimController = nullptr;
	int		m_iCurIndex = 9999; //재생중인 애니메이션 번호
	int		m_iMaxIndex; // = Animation Count


	//트랙 = 애니메이션을 재생할 틀. 
		//=> 블랜딩 : 2개의 틀을 만들어서 섞는 식으로 사용함.
		//=> 보통 한 오브젝트당 1~2개씀 (2개인 경우 상체/하체 따로)
	int		m_iCurTrack = 0;
	int		m_iNewTrack = 1;

	float	m_fCurKeyFrame = 0.f;		//= m_fAccTime;
	double	m_dMaxKeyFrame = 0.0;		//= m_dPeriod;

	float	m_fdTime = 0.f;
	float	m_fAnimSpd = 1.f;

	bool	m_bPlay = true;	//Play상태인지 Stop상태인지(현재 재생중인거랑 무관.)
	bool	m_bLoop = true;	//
	//일단 얘들은 나머지 잘 되고 나서 해주기.

	//{Play / Stop = > PlayAnimationSet안 돌면 정지함.}
	//{애니메이션 반복O / 반복 X}
	//{플레이 중인지 ? / 끝났는지 ? }
	//{애니메이션 재생 속도 = > AdvancedTime 시간 줄여주면 됨.}
};


#endif //_ANIM_CONTROLLER_H_