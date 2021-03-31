#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Engine_Include.h"
#include "Component.h"

class Camera :
	public Component
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

public:

public:

public:

private:
	Matrix		m_matProjectionMatrix;	//�������
	Matrix		m_matViewPortMatirx;	//����Ʈ ���

	float		m_fFov;		//�þ߰�
	float		m_fAspect;	//ȭ�� ����
	float		m_fNear;	//�Ͼ� ��� �Ÿ�
	float		m_fFar;		//�� ��� �Ÿ�
	


};

#endif //_CAMERA_H_