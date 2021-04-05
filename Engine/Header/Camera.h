#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Engine_Include.h"

#include "Component.h"
#include "DeviceManager.h"

class DLL_STATE Camera : public Component
{
	//로컬 -> 월드 변환 => 트랜스폼
	//월드->뷰스페이스->투영스페이스->뷰 포트 => 카메라

public:
	struct Desc
	{
		float		fFov_Degree = 45.f;
		float		fAspect = 0.f;
		float		fzNear = 0.1f;
		float		fzFar = 1000.f;
	};

public:
	explicit Camera(Desc* _desc);
	virtual ~Camera();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public: /* Functions */
	void		SetUp_ViewSpaceMatrix();
	HRESULT		Update_ViewSpaceMatrix();

	void		SetUp_ProjSpaceMatrix();
	HRESULT		Update_ProjSpaceMatrix();


public: /* Get */
	const Matrix&	Get_ViweSpaceMat() const;
	const Matrix&	Get_ProjMat() const;
	//const Matrix&	Get_ViewPortMat() const;


public: /* Set */

	
private:
	LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;
	/* To ViewSpace */
	Matrix		m_matViewSpaceMatrix;		//월드 -> 뷰 스페이스
				//카메라의 역행렬 => 뷰행렬
	
	Vector3		m_vEye;					//카메라의 위치 Pos
	Vector3		m_vAt;					//카메라가 바라볼 곳
	Vector3		m_vUp = { 0.f, 1.f, 0.f };			//절대적 UpVector.(0,1,0)

	/* To ProjectionSpace */
	//최초 단 한번만 해주면 됨.
	Matrix		m_matProjectionMatrix;		//뷰 스페이스 -> 투영 스페이스
											
	float		m_fFov= 45.f;			//시야각
	float		m_fAspect = 0.f;
	float		m_fzNear = 0.1f;			//니어 평면 거리
	float		m_fzFar = 1000.f;		//파 평면 거리
	
	
	//Matrix		m_matViewPortMatirx;	//뷰포트 행렬

};

#endif //_CAMERA_H_