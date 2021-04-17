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
	AnimationController();
	~AnimationController();

public:


public:
	HRESULT				Ready_Controller();
	
	void				Set_AnimationSet(int _iIndex);
	void				Play_AnimationSet();

public: /* Get */

public: /* Set */
	LPD3DXANIMATIONCONTROLLER		Get_Controller();
	bool							Get_IsPlaying();

private:
	LPD3DXANIMATIONCONTROLLER		m_pAnimationController = nullptr;

	//Ʈ�� -> �ִϸ��̼��� ����� Ʋ
	//���� 1��~2����
	//�츮�� 2����. �ִϸ��̼� ������ ���ؼ�.
	int		m_iCurrentTrack = -1; 
	int		m_iNewTrack = -1; //

	float	m_fAccTime = 0.f; //�����ð�, Ű �������̶�� ���� �ɵ�
	int		m_iOldIndex = 0; //������� �ε��� 

	double	m_dPeriod = 0.0; //���� �ִϸ��̼��� ��ü ��� �ð�(Ű ������?)


};

#endif //_ANIMATION_CONTROLLER_H_