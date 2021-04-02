#include "..\Header\Camera.h"
#include "Transform.h"

Camera::Camera(Desc * _desc)
{
}

Camera::~Camera()
{
}

void Camera::Initialize()
{//Component라서 생성될때 불러와짐.

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
	//우리가 transform 값이 없으면
	//카메라의 Right, Up, Forward 벡터를 직접 구한 뒤
	//카메라의 행렬을 만들어야함.
	//Forward = Normalize(At - Eye);
	//Right = Normalize(Cross((0,1,0), Forward));
	//Up = Normalize(Cross(Forward, Right));
	//Cam World Matrix ( 4x4 )
	//	{Right		}
	//	{UP			}
	//	{Forward	}
	//	{Eye		}
	// 그리고 이 행렬의 역행렬이 뷰 행렬.
	// 구한 값을 SetTransform을 통해서 장치에 넘겨주면 됨.

	//근데 나는 WorldMatrix 값도있고
	//DX9 함수도 쓸꺼라서 ㅎ;
	Matrix Cam_WorldMat = m_Transform->Get_WorldMatrix();

	//1. Eye = Cam의 Pos
	m_vEye = *(Vector3*)Cam_WorldMat.m[4];

	//2. At 구하기
		//-> 카메라가 바라보고 있는 쪽인데
		//얼마나 회전한지 모르니까 (0,0,1)을 회전값만큼 회전해주면 됨.
	m_vAt = Vector3(0.f, 0.f, 1.f); //일단 절대값 

	Quaternion Cam_Rot = m_Transform->Get_Rotation();
	Matrix RotMat;
	D3DXMatrixIdentity(&RotMat);
	D3DXMatrixRotationQuaternion(&RotMat, &Cam_Rot);
	D3DXVec3TransformCoord(&m_vAt, &m_vAt, &RotMat);
	//(0,0,1)에다가 회전행렬곱해줘서 회전한값 얻기.
	m_vAt += *(Vector3*)Cam_WorldMat.m[4];

	//3. Up 구하기.
		//-> 얘 또한 At과 마찬가지.
	m_vUp = Vector3(0.f, 1.f, 0.f);
	D3DXVec3TransformCoord(&m_vUp, &m_vUp, &RotMat);

	D3DXMatrixLookAtLH(&m_matViewSpaceMatrix, &m_vEye, &m_vAt, &m_vUp);

	/*
	근데 직접안하고 LookAtLH쓰는 태쌤 프레임워크 보니까(메인카메라)
	Eye는 ㄹㅇ Camera의 Position인데 At하고 Up은 걍 (0,0,0), (0,0,1)인데
	준니티대로 한번 해보고 At, Up 초기값으로도 해보자
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

