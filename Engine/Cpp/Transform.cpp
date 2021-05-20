#include "..\Header\Transform.h"
#include "DeviceManager.h"
#include "GameObject.h"
#include "TimeManager.h"


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

Vector3 Transform::QuaternionToEuler(Quaternion _quaternion)
{
	double roll, pitch, yaw;

	// roll (x-axis rotation)
	double sinR_cosP = 2 * (_quaternion.w * _quaternion.x + _quaternion.y * _quaternion.z);
	double cosR_cosP = 1 - 2 * (_quaternion.x * _quaternion.x + _quaternion.y * _quaternion.y);
	roll = atan2(sinR_cosP, cosR_cosP);

	// pitch (y-axis rotation)
	double sinP = 2 * (_quaternion.w * _quaternion.y - _quaternion.z * _quaternion.x);
	if (std::abs(sinP) >= 1)
		pitch = copysign(D3DX_PI * 0.5f, sinP);	// use 90 degrees if out of range
	else
		pitch = asin(sinP);

	// yaw (z-axis rotation)
	double sinY_cosP = 2 * (_quaternion.w * _quaternion.z + _quaternion.x * _quaternion.y);
	double cosY_cosP = 1 - 2 * (_quaternion.y * _quaternion.y + _quaternion.z * _quaternion.z);
	yaw = atan2(sinY_cosP, cosY_cosP);

	return Vector3(D3DXToDegree((float)roll), D3DXToDegree((float)pitch), D3DXToDegree((float)yaw));
}

Quaternion Transform::EulerToQuternion(Vector3 _eulerVector)
{
	return Quaternion();
}

void Transform::LookAt(GameObject * _pTarget, float _fSpd, Quaternion * _pOutRot)
{
	Vector3 vDir = _pTarget->Get_Transform()->Get_Position() - m_Transform->Get_Position();
	D3DXVec3Normalize(&vDir, &vDir);

	Vector3	 vForward = m_Transform->Get_Forward();

	if (D3DXVec3Dot(&vDir, &vForward) > 0.999f)
	{
		return;
	}

	Vector3 vAxis = { 0.f, 0.f, 0.f };

	D3DXVec3Cross(&vAxis, &vForward, &vDir);
	D3DXVec3Normalize(&vAxis, &vAxis);

	Quaternion QuatTemp = m_Transform->RotateAxis(vAxis, Engine_fTime*_fSpd);

	if (_pOutRot != nullptr)
	{
		*_pOutRot = QuatTemp;
	}
}

void Transform::LookAt(const Vector3 & _pTargetPos, float _fSpd, Quaternion * _pOutRot)
{
	Vector3 vDir = _pTargetPos- m_Transform->Get_Position();
	D3DXVec3Normalize(&vDir, &vDir);

	Vector3	 vForward = m_Transform->Get_Forward();

	//Vector3	Dot

	if (D3DXVec3Dot(&vDir, &vForward) > 0.999f)
	{
		return;
	}

	Vector3 vAxis = { 0.f, 0.f, 0.f };

	D3DXVec3Cross(&vAxis, &vForward, &vDir);
	D3DXVec3Normalize(&vAxis, &vAxis);

	Quaternion QuatTemp = m_Transform->RotateAxis(vAxis, Engine_fTime*_fSpd);

	if (_pOutRot != nullptr)
	{
		*_pOutRot = QuatTemp;
	}
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

void Transform::Set_WorldMatrix(const Matrix& _world)
{
	m_matWorldMatrix = _world;
}

Vector3  Transform::Get_Right()
{
	//11, 12, 13 at WorldMatirx (1행)
	Update_WorldMatrix();

	Vector3 vRight = *((Vector3*)(&m_matWorldMatrix.m[0]));
	D3DXVec3Normalize(&vRight, &vRight);
	return vRight;
}

Vector3 Transform::Get_Up()
{
	//21, 22, 23 at WorldMatrix (2행)
	Update_WorldMatrix();

	Vector3 vUp = *((Vector3*)(&m_matWorldMatrix.m[1]));
	D3DXVec3Normalize(&vUp, &vUp);
	return vUp;

}
Vector3 Transform::Get_Forward()
{
	//31,32,33 at WorldMatrix (3행)
	Update_WorldMatrix();

	Vector3 vForward = *((Vector3*)(&m_matWorldMatrix.m[2]));
	D3DXVec3Normalize(&vForward, &vForward);
	return vForward;
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


Quaternion  Transform::Get_Rotation() const
{
	return m_qRotation;
}

Vector3 Transform::Get_Rotation_Euler()
{
	return QuaternionToEuler(m_qRotation);
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

void Transform::Set_Rotation(Quaternion _quaternion)
{
	m_qRotation = _quaternion;
}

void Transform::Set_Rotation(const Vector3 & _eulerVector)
{
	D3DXQuaternionRotationYawPitchRoll(
		&m_qRotation,
		D3DXToRadian(_eulerVector.y), 
		D3DXToRadian(_eulerVector.x), 
		D3DXToRadian(_eulerVector.z));
}

void Transform::Set_Rotation(float _eulerX, float _eulerY, float _eulerZ)
{
	D3DXQuaternionRotationYawPitchRoll(&m_qRotation,
		D3DXToRadian(_eulerY), D3DXToRadian(_eulerX), D3DXToRadian(_eulerZ));
}

void Transform::Set_RotationX(float _eulerX)
{
	Vector3 CurrentAngle = QuaternionToEuler(m_qRotation);
	RotateX(-CurrentAngle.x);
	RotateX(_eulerX);
}

void Transform::Set_RotationY(float _eulerY)
{
	Vector3 CurrentAngle = QuaternionToEuler(m_qRotation);
	RotateY(-CurrentAngle.y);
	RotateY(_eulerY);
}

void Transform::Set_RotationZ(float _eulerZ)
{
	Vector3 CurrentAngle = QuaternionToEuler(m_qRotation);
	RotateZ(-CurrentAngle.z);
	RotateZ(_eulerZ);
}

void Transform::Rotate(const Vector3 & _eulerVector)
{
}

void Transform::RotateX(float _eulerX)
{
	Quaternion rot;
	D3DXQuaternionIdentity(&rot);
	D3DXQuaternionRotationAxis(&rot, &Vector3(1.f, 0.f, 0.f), D3DXToRadian(_eulerX));

	m_qRotation *= rot;
}

void Transform::RotateY(float _eulerY)
{
	Quaternion rot;
	D3DXQuaternionIdentity(&rot);
	D3DXQuaternionRotationAxis(&rot, &Vector3(0.f, 1.f, 0.f), D3DXToRadian(_eulerY));

	m_qRotation *= rot;
}

void Transform::RotateZ(float _eulerZ)
{
	Quaternion rot;
	D3DXQuaternionIdentity(&rot);
	D3DXQuaternionRotationAxis(&rot, &Vector3(0.f, 0.f, 1.f), D3DXToRadian(_eulerZ));

	m_qRotation *= rot;
}

Quaternion Transform::RotateAxis(const Vector3& _axis, float _radian, Quaternion* _pOut)
{
	Quaternion rot;
	D3DXQuaternionRotationAxis(&rot, &_axis, _radian);
	
	*_pOut = rot;
	m_qRotation *= rot;
	return rot;
}

Quaternion Transform::RotateAxis(const Vector3 & _axis, float _radian)
{
	Quaternion rot;
	D3DXQuaternionRotationAxis(&rot, &_axis, _radian);

	m_qRotation *= rot;
	return rot;
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



