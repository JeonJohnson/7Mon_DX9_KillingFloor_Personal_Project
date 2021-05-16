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
		double dAnimSpd = 1.0;

		bool bLoop = false;
		bool bPlay = true;
		bool bClone = false;//하나의 매쉬가 여러 오브젝트에 공유 될 경우 
		//LPD3DXANIMATIONCONTROLLER가 클론이 되야함.
		//플레이어 경우 한 애니메이션 컨트롤러에
		//여러 매쉬들이 필요하니까 클론 하지말고
		//몬스터같은 경우 한 매쉬에 여러 오브젝트들이 들어오니까 Clone해줘 야함.
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
	//HRESULT				SetUp_Clone_AnimCtrl();
	HRESULT				SetUp_AnimCtrl();
	void				Animating();
	void				Play(int _iNewAnimIndex, bool _bBlending = false);
	void				Play(const wstring& _szNewAnimName, bool _bBlending = false);
	bool				IsEnd();
	//void				Play(const wstring& _szAnimName, bool _bBlending = false);


public: /* Get */
	LPD3DXANIMATIONCONTROLLER		Get_AnimController();
	LPD3DXANIMATIONSET				Get_AnimSet();
	LPD3DXTRACK_DESC				Get_TrackInfo();

	wstring							Get_CurAnimName();
	int								Get_CurAnimIndex();
	int								Get_MaxAnimIndex();

	double							Get_CurFrame();
	double							Get_MaxFrame();

	double							Get_AnimSpd();

	bool							Get_Playing();



	


public: /* Set */
	void		Set_AnimController(LPD3DXANIMATIONCONTROLLER _pAnimCtrl);

	void		Set_AnimSpd(double _dAnimSpd);
	void		Set_Play(bool _OnOff);
	void		Set_Loop(bool _OnOff);
	void		Set_OffSet(double _dOffSet);

private:
	bool							m_bClone;
	LPD3DXANIMATIONCONTROLLER		m_pAnimCtrl = nullptr;
	LPD3DXANIMATIONSET				m_pAnimSet = nullptr;

	int								m_iCurIndex = 9999; //Current Anim Index
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