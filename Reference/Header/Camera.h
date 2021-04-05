#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Engine_Include.h"

#include "Component.h"
#include "DeviceManager.h"

class DLL_STATE Camera : public Component
{
	//���� -> ���� ��ȯ => Ʈ������
	//����->�佺���̽�->���������̽�->�� ��Ʈ => ī�޶�

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
	Matrix		m_matViewSpaceMatrix;		//���� -> �� �����̽�
				//ī�޶��� ����� => �����
	
	Vector3		m_vEye;					//ī�޶��� ��ġ Pos
	Vector3		m_vAt;					//ī�޶� �ٶ� ��
	Vector3		m_vUp = { 0.f, 1.f, 0.f };			//������ UpVector.(0,1,0)

	/* To ProjectionSpace */
	//���� �� �ѹ��� ���ָ� ��.
	Matrix		m_matProjectionMatrix;		//�� �����̽� -> ���� �����̽�
											
	float		m_fFov= 45.f;			//�þ߰�
	float		m_fAspect = 0.f;
	float		m_fzNear = 0.1f;			//�Ͼ� ��� �Ÿ�
	float		m_fzFar = 1000.f;		//�� ��� �Ÿ�
	
	
	//Matrix		m_matViewPortMatirx;	//����Ʈ ���

};

#endif //_CAMERA_H_