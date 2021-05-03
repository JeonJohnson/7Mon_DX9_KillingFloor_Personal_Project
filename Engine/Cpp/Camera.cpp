#include "..\Header\Camera.h"
#include "Transform.h"
#include "DeviceManager.h"

Camera::Camera(Desc * _desc)
{
	//m_vUp = Vector3(0.f, 1.f, 0.f);

	m_fFov = D3DXToRadian(_desc->fFov_Degree);

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
	SetUp_ProjSpaceMatrix();
	if (FAILED(Update_ProjSpaceMatrix()))
	{
		MsgBox(L"Error", L"ProjSpace Matrix Update Failed");
	}
}

void Camera::Update()
{
	SetUp_ViewSpaceMatrix();
	//SetUp_ProjSpaceMatrix();

	if (FAILED(Update_ViewSpaceMatrix()))
	{
		MsgBox(L"Error", L"ViewSpace Matrix Update Failed");
	}
	//if (FAILED(Update_ProjSpaceMatrix()))
	//{
	//	MsgBox(L"Error", L"ProjSpace Matrix Update Failed");
	//}
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
	////�츮�� transform ���� ������
	////ī�޶��� Right, Up, Forward ���͸� ���� ���� ��
	////ī�޶��� ����� ��������.
	////Forward = Normalize(At - Eye);
	////Right = Normalize(Cross((0,1,0), Forward));
	////Up = Normalize(Cross(Forward, Right));
	////Cam World Matrix ( 4x4 )
	////	{Right		}
	////	{UP			}
	////	{Forward	}
	////	{Eye		}
	//// �׸��� �� ����� ������� �� ���.
	//// ���� ���� SetTransform�� ���ؼ� ��ġ�� �Ѱ��ָ� ��.

	////�ٵ� ���� WorldMatrix �����ְ�
	////DX9 �Լ��� ������ ��;
	//Matrix Cam_WorldMat = m_Transform->Get_WorldMatrix();

	////1. Eye = Cam�� Pos
	//m_vEye = *(Vector3*)Cam_WorldMat.m[4];

	////2. At ���ϱ�
	//	//-> ī�޶� �ٶ󺸰� �ִ� ���ε�
	//	//�󸶳� ȸ������ �𸣴ϱ� (0,0,1)�� ȸ������ŭ ȸ�����ָ� ��.
	//m_vAt = Vector3(0.f, 0.f, 1.f); //�ϴ� ���밪 

	//Quaternion Cam_Rot = m_Transform->Get_Rotation();
	//Matrix RotMat;
	//D3DXMatrixIdentity(&RotMat);
	//D3DXMatrixRotationQuaternion(&RotMat, &Cam_Rot);
	//D3DXVec3TransformCoord(&m_vAt, &m_vAt, &RotMat);
	////(0,0,1)���ٰ� ȸ����İ����༭ ȸ���Ѱ� ���.
	//m_vAt += *(Vector3*)Cam_WorldMat.m[4];

	////3. Up ���ϱ�.
	//	//-> �� ���� At�� ��������.
	//m_vUp = Vector3(0.f, 1.f, 0.f);
	//D3DXVec3TransformCoord(&m_vUp, &m_vUp, &RotMat);

	//D3DXMatrixLookAtLH(&m_matViewSpaceMatrix, &m_vEye, &m_vAt, &m_vUp);

	///*
	//�ٵ� �������ϰ� LookAtLH���� �½� �����ӿ�ũ ���ϱ�(����ī�޶�)
	//Eye�� ���� Camera�� Position�ε� At�ϰ� Up�� �� (0,0,0), (0,0,1)�ε�
	//�ش�Ƽ��� �ѹ� �غ��� At, Up �ʱⰪ���ε� �غ���
	//*/

	//�� ���� �ʿ������. �� �����̽� ���-> ī�޶� Transform�� �����....
	//����,,, �� ,, �Ӹ���,,, ����,,,, 2222�̤ФФ̤�
	Matrix matTransform = m_Transform->Get_WorldMatrix();
	D3DXMatrixInverse(&m_matViewSpaceMatrix, 0, &matTransform);

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
	//http://egloos.zum.com/EireneHue/v/985792

	///* ���� �ϱ� */

	//D3DXMatrixIdentity(&m_matProjectionMatrix);

	//float h = 1 / tanf(m_fFov / 2.f);

	//m_matProjectionMatrix._11 = h/m_fAspect;
	//m_matProjectionMatrix._22 = h;

	//m_matProjectionMatrix._33 = m_fzFar/(m_fzFar- m_fzNear);
	//m_matProjectionMatrix._43 = (-m_fzNear * m_fzFar) / (m_fzFar - m_fzNear);

	//m_matProjectionMatrix._34 = 1.f;
	//m_matProjectionMatrix._44 = 0.f;

	
	/* �ٷ��Լ� ��� */
	D3DXMatrixIdentity(&m_matProjectionMatrix);
	D3DXMatrixPerspectiveFovLH(
		&m_matProjectionMatrix,
		m_fFov,
		m_fAspect,
		m_fzNear,
		m_fzFar);
};

HRESULT Camera::Update_ProjSpaceMatrix()
{
	//���������� ���� ���� �� ������ �� �� �ʿ�� ����.
	//�ȿ� ������ ���ʿ� �� �ٲ� ������ �ƴϴϱ�...
	if (FAILED(m_pDX9_Device->SetTransform(D3DTS_PROJECTION, &m_matProjectionMatrix)))
	{
		return E_FAIL;
	}

	return S_OK;
}

Vector2 Camera::World2Screen(const Vector3 & _WorldPos)
{
	float fHalfWinCX = DeviceManager::Get_Instance()->Get_WindowSize().x;
	float fHalfWinCY = DeviceManager::Get_Instance()->Get_WindowSize().y;
	
	Vector3 vTemp;
	D3DXVec3TransformCoord(&vTemp, &_WorldPos, &Get_ViewSpaceMat());
	D3DXVec3TransformCoord(&vTemp, &vTemp, &Get_ProjMat());
	D3DXVec3TransformCoord(&vTemp, &vTemp, &Get_ViewPortMat());

	return Vector2(vTemp.x - fHalfWinCX, fHalfWinCY - vTemp.y);
}

Vector3 Camera::Screen2World(const Vector2 & _ScreenPos, float _DistanceFromCam)
{
	float wincx = (float)DeviceManager::Get_Instance()->Get_WindowSize().x;
	float wincy = (float)DeviceManager::Get_Instance()->Get_WindowSize().y;

	Vector2 screenPos = _ScreenPos;
	
/* ViewSpace(ScreenView)Pos To ProjectionPos */
	//���� �����̽� ����	|	��ũ�� ��ǥ 
	//�»� -1,	1			|	0,		0
	//��� 1,	1			|	1280,	0
	//���� -1,	-1			|	0,		720
	//���� 1.	-1			|	1280,	720
	Vector3	ProjectionTransform;
	ProjectionTransform.x = ((2.f * screenPos.x) / wincx) - 1.f;
	ProjectionTransform.y = ((-2.f * screenPos.y) / wincy) + 1.f;
	ProjectionTransform.z = 1.;

/* ProjectionPos To ViewSpacePos */
//���������̽� ����� ���ϱ�.
	Matrix invProjection;
	m_pDX9_Device->GetTransform(D3DTS_PROJECTION, &invProjection);
	D3DXMatrixInverse(&invProjection, 0, &invProjection);
//�佺���̽��� ��ǥ ���ϱ�.
	Vector3 ViewSpaceTrans;
	D3DXVec3TransformCoord(&ViewSpaceTrans, &ProjectionTransform, &invProjection);

/* ViewSpacePos To WorldSpacePos */
//�佺���̽��� ����� ���ϱ�.
	Matrix invViewSpace;
	m_pDX9_Device->GetTransform(D3DTS_VIEW, &invViewSpace);
	D3DXMatrixInverse(&invViewSpace, 0, &invViewSpace);
//���� �����̽��� ��ǥ ���ϱ�.
	Vector3	WorldSpaceTrans;
	D3DXVec3TransformCoord(&WorldSpaceTrans, &ViewSpaceTrans, &invViewSpace);
	

/* �Ÿ� ���� ���ֱ� */
	Vector3 BetweenVector;
	Vector3 ResultPos;
	BetweenVector = WorldSpaceTrans - m_Transform->Get_Position();
	D3DXVec3Normalize(&BetweenVector, &BetweenVector);
	ResultPos = m_Transform->Get_Position() + (BetweenVector * _DistanceFromCam);

	return ResultPos;
}

const Matrix & Camera::Get_ViewSpaceMat()
{
	Update_ViewSpaceMatrix();
	return m_matViewSpaceMatrix;
}

const Matrix & Camera::Get_ProjMat()
{
	Update_ProjSpaceMatrix();
	return m_matProjectionMatrix;
}

Matrix Camera::Get_ViewPortMat() const
{
	float halfWincx = DeviceManager::Get_Instance()->Get_WindowSize().x* 0.5f;
	float halfWincy = DeviceManager::Get_Instance()->Get_WindowSize().y* 0.5f;

	return Matrix
	{
		halfWincx,	0.f        , 0.f             , 0.f,
		0.f       , -halfWincy, 0.f             , 0.f,
		0.f       , 0.f        , m_fzFar - m_fzNear, 0.f,
		halfWincx, halfWincy , m_fzNear         , 1.f
	};
}

