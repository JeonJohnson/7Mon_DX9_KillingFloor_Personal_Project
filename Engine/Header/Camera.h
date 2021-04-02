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
	Matrix		m_matProjectionMatrix;	//�������
	Matrix		m_matViewPortMatirx;	//����Ʈ ���

	float		m_fFov;		//�þ߰�
	float		m_fAspect;	//ȭ�� ����
	float		m_fNear;	//�Ͼ� ��� �Ÿ�
	float		m_fFar;		//�� ��� �Ÿ�
	


};

#endif //_CAMERA_H_