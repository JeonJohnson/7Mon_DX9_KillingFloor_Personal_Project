#include "..\Header\Transform.h"
#include "DeviceManager.h"



Transform::Transform(Desc * _desc)
{
}

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Initialize()
{
	m_vPosition = { 0.f, 0.f, 0.f };
	m_vScale = { 1.f, 1.f, 1.f };
	m_qRotation = { 0.f, 0.f,0.f,1.f };

	D3DXMatrixIdentity(&m_matWorldMatrix);
	Update_WorldMatrix();
}

void Transform::Update()
{
	Update_WorldMatrix();
}

void Transform::LateUpdate()
{
}

void Transform::ReadyRender()
{
}

void Transform::Release()
{
}

void Transform::Set_Transform(Transform * _pTransform)
{
	/*
	Gameobject를 init하는 과정에서 m_Transform도 Component기 때문에 Add_Component를 하는데
	Add Component안에서 Set_Transform을 함.
	근디 아직 GameObject의 transform은 없지. 만드는 중인데...
	그래서 자기 자신을 받을꺼임.
	헌테 이게 Component(부모) 함수가 호출되는거니까 override 걸어주면 딱 되것다. 이거야.
	*/
	m_Transform = this;
}

void Transform::Update_WorldMatrix()
{
	//월드 행렬을 장치로 넘겨주는건 각 객체 Renderer에서 그리기 전에 해주자.

	{//다렉함수로 월드매트릭스 지정해주기
		//크자이공부 순
		Matrix matScale, matRot, matTrans;
		D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixRotationQuaternion(&matRot, &m_qRotation);
		///*Test*/
		//Vector3 tempPos = { 2.f, -2.f,0.f };
		//D3DXMatrixTranslation(&matTrans, tempPos.x, tempPos.y, tempPos.z);
		///*Test*/
		D3DXMatrixTranslation(&matTrans, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	
		m_matWorldMatrix = matScale * matRot * matTrans;
	}

	//{//직접 돌리기

	//float wincx =	DeviceManager::Get_Instance()->Get_WindowSize().x;
	//float wincy = DeviceManager::Get_Instance()->Get_WindowSize().y;
	////float wincx = 1280.f;
	////float wincy = 720.f;

	//	float halfWincx = wincx * 0.5f;
	//	float halfWincy = wincy * 0.5f;

	//	Vector3 right = { 1.f,0.f,0.f };
	//	Vector3 up = { 0.f,1.f,0.f };
	//	Vector3 look = { 0.f,0.f,1.f };

	//	/* scale */
	//	right.x *= m_vScale.x;
	//	up.y *= m_vScale.y;
	//	look.z *= m_vScale.z;

	//	/* rotate */
	//	Get_RotationX(&right, right);
	//	Get_RotationY(&right, right);
	//	Get_RotationZ(&right, right);

	//	Get_RotationX(&up, up);
	//	Get_RotationY(&up, up);
	//	Get_RotationZ(&up, up);

	//	Get_RotationX(&look, look);
	//	Get_RotationY(&look, look);
	//	Get_RotationZ(&look, look);

	//	D3DXMatrixIdentity(&m_matWorldMatrix);
	//	memcpy(&m_matWorldMatrix.m[0][0], &right, sizeof(Vector3));
	//	memcpy(&m_matWorldMatrix.m[1][0], &up, sizeof(Vector3));
	//	memcpy(&m_matWorldMatrix.m[2][0], &look, sizeof(Vector3));
	//	memcpy(&m_matWorldMatrix.m[3][0], &m_vPosition, sizeof(Vector3));


	//	Vector3 correctPos = {
	//		(m_matWorldMatrix.m[3][0] - halfWincx) / halfWincx,
	//		(halfWincy - m_matWorldMatrix.m[3][1]) / halfWincy,
	//		m_matWorldMatrix.m[3][2] };

	//	memcpy(&m_matWorldMatrix.m[3][0], &correctPos, sizeof(Vector3));
	//}


}

const Matrix & Transform::Get_WorldMatrix() const
{
	return m_matWorldMatrix;
}

void Transform::Set_WorldMatrix() const
{
}

const Vector3 & Transform::Get_Scale() const
{
	return m_vScale;
}

void Transform::Set_Scale(const Vector3 & _vScale)
{
	m_vScale = _vScale;
}

void Transform::Add_Scale(const Vector3 & _vScale)
{
	m_vScale += _vScale;
}

void Transform::Add_ScaleX(float _x)
{
	m_vScale.x += _x;
}

void Transform::Add_ScaleY(float _y)
{
	m_vScale.y += _y;
}

void Transform::Add_ScaleZ(float _z)
{
	m_vScale.y += _z;
}

const Quaternion & Transform::Get_Rotation() const
{
	return m_qRotation;
}

void Transform::Get_RotationX(Vector3 * _pOut, Vector3 _In)
{
	//Roll
	/*
	1	0	0	0
	0	c	s	0
	0	-s	c	0
	0	0	0	1
	*/
	double sinR_cosP = 2 * (m_qRotation.w * m_qRotation.x + m_qRotation.y * m_qRotation.z);
	double cosR_cosP = 1 - 2 * (m_qRotation.x * m_qRotation.x + m_qRotation.y * m_qRotation.y);
	float radian = (float)atan2(sinR_cosP, cosR_cosP);

	_pOut->y = _In.y * cosf(radian) - _In.z * sinf(radian);
	_pOut->z = _In.y * sinf(radian) + _In.z * cosf(radian);
}

void Transform::Get_RotationY(Vector3 * _pOut, Vector3 _In)
{
	//Pitch
	/*
	c	0	-s	0
	0	1	0	0
	s	0	c	0
	0	0	0	1
	*/
	double sinP = 2 * (m_qRotation.w * m_qRotation.y - m_qRotation.z * m_qRotation.x);
	float radian = 0.f;
	if (std::abs(sinP) >= 1)
		radian = (float)copysign(D3DX_PI * 0.5f, sinP);	// use 90 degrees if out of range
	else
		radian = (float)asin(sinP);

	_pOut->x = _In.x * cosf(radian) + _In.z * sinf(radian);
	_pOut->z = _In.x * -sinf(radian) + _In.z * cosf(radian);
}

void Transform::Get_RotationZ(Vector3 * _pOut, Vector3 _In)
{
	//Yaw 
	/*
	c	s	0	0
	-s	c	0	0
	0	0	1	0
	0	0	0	1
	*/
	double sinY_cosP = 2 * (m_qRotation.w * m_qRotation.z + m_qRotation.x * m_qRotation.y);
	double cosY_cosP = 1 - 2 * (m_qRotation.y * m_qRotation.y + m_qRotation.z * m_qRotation.z);
	float radian = (float)atan2(sinY_cosP, cosY_cosP);

	_pOut->x = _In.x * cosf(radian) - _In.y * sinf(radian);
	_pOut->y = _In.x * sinf(radian) + _In.y * cosf(radian);
}



const Vector3 & Transform::Get_Position() const
{
	return m_vPosition;
}

void Transform::Set_Position(const Vector3 & _vPos)
{
	m_vPosition = _vPos;
}

void Transform::Add_Position(const Vector3 & _vPos)
{
	m_vPosition += _vPos;
}

void Transform::Add_PosX(float _x)
{
	m_vPosition.x += _x;
}

void Transform::Add_PosY(float _y)
{
	m_vPosition.y += _y;
}

void Transform::Add_PosZ(float _z)
{
	m_vPosition.z += _z;
}



