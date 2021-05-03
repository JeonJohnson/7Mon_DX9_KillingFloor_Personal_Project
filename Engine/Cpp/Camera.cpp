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
{//Component라서 생성될때 불러와짐.
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	assert(L"Device Load Failed at Camera" && m_pDX9_Device);

	//지금 Init이 컴포넌트 Instiate에서 불러와지는데
	//그 다음 단계에서 m_Transform을 세팅해주기 때문에 다음 줄에서 무적권 막힘.

	//일단 지금 이렇게 하는 방식이 아닌거같음. ViewSpcae 행렬을 여기서 처리하는게.
	//아침에 인나서 다시 봐보자.

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
	////우리가 transform 값이 없으면
	////카메라의 Right, Up, Forward 벡터를 직접 구한 뒤
	////카메라의 행렬을 만들어야함.
	////Forward = Normalize(At - Eye);
	////Right = Normalize(Cross((0,1,0), Forward));
	////Up = Normalize(Cross(Forward, Right));
	////Cam World Matrix ( 4x4 )
	////	{Right		}
	////	{UP			}
	////	{Forward	}
	////	{Eye		}
	//// 그리고 이 행렬의 역행렬이 뷰 행렬.
	//// 구한 값을 SetTransform을 통해서 장치에 넘겨주면 됨.

	////근데 나는 WorldMatrix 값도있고
	////DX9 함수도 쓸꺼라서 ㅎ;
	//Matrix Cam_WorldMat = m_Transform->Get_WorldMatrix();

	////1. Eye = Cam의 Pos
	//m_vEye = *(Vector3*)Cam_WorldMat.m[4];

	////2. At 구하기
	//	//-> 카메라가 바라보고 있는 쪽인데
	//	//얼마나 회전한지 모르니까 (0,0,1)을 회전값만큼 회전해주면 됨.
	//m_vAt = Vector3(0.f, 0.f, 1.f); //일단 절대값 

	//Quaternion Cam_Rot = m_Transform->Get_Rotation();
	//Matrix RotMat;
	//D3DXMatrixIdentity(&RotMat);
	//D3DXMatrixRotationQuaternion(&RotMat, &Cam_Rot);
	//D3DXVec3TransformCoord(&m_vAt, &m_vAt, &RotMat);
	////(0,0,1)에다가 회전행렬곱해줘서 회전한값 얻기.
	//m_vAt += *(Vector3*)Cam_WorldMat.m[4];

	////3. Up 구하기.
	//	//-> 얘 또한 At과 마찬가지.
	//m_vUp = Vector3(0.f, 1.f, 0.f);
	//D3DXVec3TransformCoord(&m_vUp, &m_vUp, &RotMat);

	//D3DXMatrixLookAtLH(&m_matViewSpaceMatrix, &m_vEye, &m_vAt, &m_vUp);

	///*
	//근데 직접안하고 LookAtLH쓰는 태쌤 프레임워크 보니까(메인카메라)
	//Eye는 ㄹㅇ Camera의 Position인데 At하고 Up은 걍 (0,0,0), (0,0,1)인데
	//준니티대로 한번 해보고 At, Up 초기값으로도 해보자
	//*/

	//다 좆도 필요없었다. 뷰 스페이스 행렬-> 카메라 Transform의 역행렬....
	//쓰냐,,, 나 ,, 머리가,,, 띵해,,,, 2222ㅜㅠㅠㅜㅍ
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

	///* 직접 하기 */

	//D3DXMatrixIdentity(&m_matProjectionMatrix);

	//float h = 1 / tanf(m_fFov / 2.f);

	//m_matProjectionMatrix._11 = h/m_fAspect;
	//m_matProjectionMatrix._22 = h;

	//m_matProjectionMatrix._33 = m_fzFar/(m_fzFar- m_fzNear);
	//m_matProjectionMatrix._43 = (-m_fzNear * m_fzFar) / (m_fzFar - m_fzNear);

	//m_matProjectionMatrix._34 = 1.f;
	//m_matProjectionMatrix._44 = 0.f;

	
	/* 다렉함수 사용 */
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
	//프로젝션은 원래 딱히 매 프레임 해 줄 필요는 없음.
	//안에 값들이 애초에 잘 바뀔 값들이 아니니까...
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
	//투영 스페이스 범위	|	스크린 좌표 
	//좌상 -1,	1			|	0,		0
	//우상 1,	1			|	1280,	0
	//좌하 -1,	-1			|	0,		720
	//우하 1.	-1			|	1280,	720
	Vector3	ProjectionTransform;
	ProjectionTransform.x = ((2.f * screenPos.x) / wincx) - 1.f;
	ProjectionTransform.y = ((-2.f * screenPos.y) / wincy) + 1.f;
	ProjectionTransform.z = 1.;

/* ProjectionPos To ViewSpacePos */
//투영스페이스 역행렬 구하기.
	Matrix invProjection;
	m_pDX9_Device->GetTransform(D3DTS_PROJECTION, &invProjection);
	D3DXMatrixInverse(&invProjection, 0, &invProjection);
//뷰스페이스의 좌표 구하기.
	Vector3 ViewSpaceTrans;
	D3DXVec3TransformCoord(&ViewSpaceTrans, &ProjectionTransform, &invProjection);

/* ViewSpacePos To WorldSpacePos */
//뷰스페이스의 역행렬 구하기.
	Matrix invViewSpace;
	m_pDX9_Device->GetTransform(D3DTS_VIEW, &invViewSpace);
	D3DXMatrixInverse(&invViewSpace, 0, &invViewSpace);
//월드 스페이스의 좌표 구하기.
	Vector3	WorldSpaceTrans;
	D3DXVec3TransformCoord(&WorldSpaceTrans, &ViewSpaceTrans, &invViewSpace);
	

/* 거리 조절 해주기 */
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

