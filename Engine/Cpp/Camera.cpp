#include "..\Header\Camera.h"
#include "Transform.h"

Camera::Camera(Desc * _desc)
{
}

Camera::~Camera()
{
}

void Camera::Initialize()
{//Component�� �����ɶ� �ҷ�����.

}

void Camera::Update()
{

}

void Camera::LateUpdate()
{
}

void Camera::ReadyRender()
{
}

void Camera::Release()
{
}

void Camera::SetUp_ViewSpaceMatrix()
{
	//�츮�� transform ���� ������
	//ī�޶��� Right, Up, Forward ���͸� ���� ���� ��
	//ī�޶��� ����� ��������.
	//Forward = Normalize(At - Eye);
	//Right = Normalize(Cross((0,1,0), Forward));
	//Up = Normalize(Cross(Forward, Right));
	//Cam World Matrix ( 4x4 )
	//	{Right		}
	//	{UP			}
	//	{Forward	}
	//	{Eye		}
	// �׸��� �� ����� ������� �� ���.
	// ���� ���� SetTransform�� ���ؼ� ��ġ�� �Ѱ��ָ� ��.

	//�ٵ� ���� WorldMatrix �����ְ�
	//DX9 �Լ��� ������ ��;
	Matrix Cam_WorldMat = m_Transform->Get_WorldMatrix();

	//1. Eye = Cam�� Pos
	m_vEye = *(Vector3*)Cam_WorldMat.m[4];

	//2. At ���ϱ�
		//-> ī�޶� �ٶ󺸰� �ִ� ���ε�
		//�󸶳� ȸ������ �𸣴ϱ� (0,0,1)�� ȸ������ŭ ȸ�����ָ� ��.
	m_vAt = Vector3(0.f, 0.f, 1.f); //�ϴ� ���밪 

	Quaternion Cam_Rot = m_Transform->Get_Rotation();
	Matrix RotMat;
	D3DXMatrixIdentity(&RotMat);
	D3DXMatrixRotationQuaternion(&RotMat, &Cam_Rot);
	D3DXVec3TransformCoord(&m_vAt, &m_vAt, &RotMat);
	//(0,0,1)���ٰ� ȸ����İ����༭ ȸ���Ѱ� ���.
	m_vAt += *(Vector3*)Cam_WorldMat.m[4];

	//3. Up ���ϱ�.
		//-> �� ���� At�� ��������.
	m_vUp = Vector3(0.f, 1.f, 0.f);
	D3DXVec3TransformCoord(&m_vUp, &m_vUp, &RotMat);

	D3DXMatrixLookAtLH(&m_matViewSpaceMatrix, &m_vEye, &m_vAt, &m_vUp);

	/*
	�ٵ� �������ϰ� LookAtLH���� �½� �����ӿ�ũ ���ϱ�(����ī�޶�)
	Eye�� ���� Camera�� Position�ε� At�ϰ� Up�� �� (0,0,0), (0,0,1)�ε�
	�ش�Ƽ��� �ѹ� �غ��� At, Up �ʱⰪ���ε� �غ���
	*/
}

HRESULT Camera::Update_ViewSpaceMatrix()
{
	return S_OK;
}

void Camera::SetUp_ProjSpaceMatrix()
{
	D3DXMatrixPerspectiveFovLH(
		&m_matProjectionMatrix,
		m_fFov,
		m_fAspect,
		m_fzNear,
		m_fzFar);
};

HRESULT Camera::Update_ProjSpaceMatrix()
{
	return S_OK;
}

