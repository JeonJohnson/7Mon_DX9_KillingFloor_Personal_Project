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
		int	InitIndex = 0;
		double fAnimSpd = 1.f;

		bool bLoop = true;
		bool bPlay = true;
		
		//wstring		MeshName = L"";
	};

public:
	explicit AnimationController(Desc* _desc);
	virtual ~AnimationController();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public: /* Func */
	HRESULT				SetUp_AnimCtrl();
	HRESULT				Change_Mesh();
	void				Animating();
	void				Play(int _iNewIndex, bool _bBlending = false);
	//void				Play(const wstring& _szAnimName, bool _bBlending = false);


public: /* Get */
	LPD3DXANIMATIONCONTROLLER		Get_AnimController();
	LPD3DXANIMATIONSET				Get_AnimSet();
	LPD3DXTRACK_DESC				Get_TrackInfo();

	wstring							Get_AnimName();
	int								Get_CurIndex();
	int								Get_MaxIndex();

	bool							IsEnd();
	


public: /* Set */
	void		Set_AnimController(LPD3DXANIMATIONCONTROLLER _pAnimCtrl);

	void		Set_AnimSpd(double _dAnimSpd);
	void		Set_Play(bool _OnOff);
	void		Set_Loop(bool _OnOff);

private:
	LPD3DXANIMATIONCONTROLLER		m_pAnimCtrl = nullptr;
	LPD3DXANIMATIONSET				m_pAnimSet = nullptr;

	int								m_iCurIndex = 9999;
	int								m_iMaxIndex = 0; //Full Anim Count
	
	LPD3DXTRACK_DESC				m_pCurTrackInfo = nullptr;
	int								m_iCurTrackIndex = 0; 
	int								m_iNewTrackIndex = 1; //for Blending

	double							m_dCurKeyFrame = 0.0;
	double							m_dMaxKeyFrame = 0.0;

	double							m_dDeltaTime = 0.0;
	double							m_dOffSet = 0.01;
	double							m_dAnimSpd = 1.0;

	bool							m_bLoop = true;
	bool							m_bPlay = true;





};

#endif //_ANIMATION_CONTROLLER_H_