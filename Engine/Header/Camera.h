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
		float		fFov;
		float		fAspect 
			= (float)(DeviceManager::Get_Instance()->Get_WindowSize().x)/DeviceManager::Get_Instance()->Get_WindowSize().y;
		float		fzNear = 1.f;
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
	/* To ViewSpace */
	Matrix		m_matViewSpaceMatrix;		//���� -> �� �����̽�
				//ī�޶��� ����� => �����
	
	Vector3		m_vEye;					//ī�޶��� ��ġ Pos
	Vector3		m_vAt;					//ī�޶� �ٶ� ��
	Vector3		m_vUp;			//������ UpVector.(0,1,0)

	/* To ProjectionSpace */
	//���� �� �ѹ��� ���ָ� ��.
	Matrix		m_matProjectionMatrix;		//�� �����̽� -> ���� �����̽�
											
	float		m_fFov = 90.f;			//�þ߰�
	float		m_fAspect 
		 = (float)(DeviceManager::Get_Instance()->Get_WindowSize().x)/DeviceManager::Get_Instance()->Get_WindowSize().y;
	float		m_fzNear = 1.f;			//�Ͼ� ��� �Ÿ�
	float		m_fzFar = 1000.f;		//�� ��� �Ÿ�
	
	
	//Matrix		m_matViewPortMatirx;	//����Ʈ ���

};

#endif //_CAMERA_H_