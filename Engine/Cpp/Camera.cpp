#include "..\Header\Camera.h"
#include "Transform.h"
#include "DeviceManager.h"

Camera::Camera(Desc * _desc)
{
	m_fFov = _desc->fFov;

	if (m_fAspect == 0.f)
	{
		float x = (float)(DeviceManager::Get_Instance()->Get_WindowSize().x);
		float y = (float)(DeviceManager::Get_Instance()->Get_WindowSize().y);
		m_fAspect = x / y;
	}
	else { m_fAspect = _desc->fAspect; }


	m_fzNear = _desc->fzNear;
	m_fzFar = _desc->fzFar;
}

Camera::~Camera()
{
}

void Camera::Initialize()
{//Component�� �����ɶ� �ҷ�����.
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	assert(L"Device Load Failed at Camera" && m_pDX9_Device);

	//���� Init�� ������Ʈ Instiate���� �ҷ������µ�
	//�� ���� �ܰ迡�� m_Transform�� �������ֱ� ������ ���� �ٿ��� ������ ����.

	//�ϴ� ���� �̷��� �ϴ� ����� �ƴѰŰ���. ViewSpcae ����� ���⼭ ó���ϴ°�.
	//��ħ�� �γ��� �ٽ� ������.

	//assert(L"Camera Transform is nullptr" && m_Transform);

	//SetUp_ViewSpaceMatrix();
	//SetUp_ProjSpaceMatrix();
}

void Camera::Update()
{
	Update_ViewSpaceMatrix();
	Update_ProjSpaceMatrix();
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
	if (FAILED(m_pDX9_Device->SetTransform(D3DTS_VIEW, &m_matViewSpaceMatrix)))
	{
		return E_FAIL;
	}

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
	if (FAILED(m_pDX9_Device->SetTransform(D3DTS_PROJECTION, &m_matProjectionMatrix)))
	{
		return E_FAIL;
	}

	return S_OK;
}

const Matrix & Camera::Get_ViweSpaceMat() const
{
	return m_matViewSpaceMatrix;
}

const Matrix & Camera::Get_ProjMat() const
{
	return m_matProjectionMatrix;
}

