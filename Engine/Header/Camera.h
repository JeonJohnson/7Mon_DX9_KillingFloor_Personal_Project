#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Engine_Include.h"

#include "Component.h"

class DLL_STATE Camera : public Component
{
public:
	struct Desc
	{


	};

public:
	explicit Camera();
	explicit Camera(Desc* _desc);
	virtual ~Camera();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public: /* Functions */
	void	Update_ViewSpaceMatrix();
	void	Update_ProjSpaceMatrix();

public: /* Get */
	const Matrix&	Get_ViweSpaceMat() const;
	const Matrix&	Get_ProjMat() const;
	const Matrix&	Get_ViewPortMat() const;


public: /* Set */


private:
	Matrix		m_matViewSpaceMatrix;
	Matrix		m_matProjectionMatrix;	//투영행렬
	Matrix		m_matViewPortMatirx;	//뷰포트 행렬

	float		m_fFov;		//시야각
	float		m_fAspect;	//화면 비율
	float		m_fNear;	//니어 평면 거리
	float		m_fFar;		//파 평면 거리
	


};

#endif //_CAMERA_H_