#pragma once

#ifndef _ANIMATION_CONTROLLER_H_
#define _ANIMATION_CONTROLLER_H_

#include "Engine_Include.h"

class DLL_STATE AnimationController
{
	//���߿��� �긦 ������Ʈ�� �ٲ㼭
	//�ϴ� MeshRenderer������Ʈ�� ������ �ִ� �ֿ��ٰ�
	//�� ������Ʈ�� �޾��ش���
	//�ִϸ��̼� ������ ������ ����ϰ� ������ �׳� ����ƽ �Ž��� ����ϵ���.

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

	//Ʈ�� -> �ִϸ��̼��� ����� Ʋ
	//���� 1��~2����
	//�츮�� 2����. �ִϸ��̼� ������ ���ؼ�.
	int		m_iCurrentTrack = 0; 
	int		m_iNewTrack = 1; //

	float	m_fAccTime = 0.f; //�����ð�, Ű �������̶�� ���� �ɵ�
	int		m_iOldIndex = 999; //������� �ε��� 

	double	m_dPeriod = 0.0; //���� �ִϸ��̼��� ��ü ��� �ð�(Ű ������?)

	float	m_fAnimSpd = 1.f;
};

#endif //_ANIMATION_CONTROLLER_H_