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
	int		m_iCurIndex = 9999; //������� �ִϸ��̼� ��ȣ
	int		m_iMaxIndex; // = Animation Count


	//Ʈ�� = �ִϸ��̼��� ����� Ʋ. 
		//=> ���� : 2���� Ʋ�� ���� ���� ������ �����.
		//=> ���� �� ������Ʈ�� 1~2���� (2���� ��� ��ü/��ü ����)
	int		m_iCurTrack = 0;
	int		m_iNewTrack = 1;

	float	m_fCurKeyFrame = 0.f;		//= m_fAccTime;
	double	m_dMaxKeyFrame = 0.0;		//= m_dPeriod;

	float	m_fdTime = 0.f;
	float	m_fAnimSpd = 1.f;

	bool	m_bPlay = true;	//Play�������� Stop��������(���� ������ΰŶ� ����.)
	bool	m_bLoop = true;	//
	//�ϴ� ����� ������ �� �ǰ� ���� ���ֱ�.

	//{Play / Stop = > PlayAnimationSet�� ���� ������.}
	//{�ִϸ��̼� �ݺ�O / �ݺ� X}
	//{�÷��� ������ ? / �������� ? }
	//{�ִϸ��̼� ��� �ӵ� = > AdvancedTime �ð� �ٿ��ָ� ��.}
};


#endif //_ANIM_CONTROLLER_H_