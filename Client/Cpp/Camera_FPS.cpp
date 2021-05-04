
#include "stdafx.h"
#include "..\Header\Camera_FPS.h"

Camera_FPS::Camera_FPS(Desc * _desc)
{
	m_fSensitive = _desc->fSensitive;
}

Camera_FPS::~Camera_FPS()
{
}

void Camera_FPS::Initialize()
{
}

void Camera_FPS::Update()
{
	Look();
}

void Camera_FPS::LateUpdate()
{
}

void Camera_FPS::ReadyRender()
{
}

void Camera_FPS::Release()
{
}

void Camera_FPS::Look()
{
	int fMouseMoveX = MouseMove(KEY_STATE_MouseX);
	int fMouseMoveY = MouseMove(KEY_STATE_MouseY);
	
	m_fRotX += fMouseMoveX * m_fSensitive * fTime;
	m_fRotY += fMouseMoveY * m_fSensitive * fTime;

	if (m_fRotY >= 70.f)
	{
		m_fRotY = 70.f;
	}

	if (m_fRotY <= -70.f)
	{
		m_fRotY = -70.f;
	}

	m_Transform->Set_Rotation(Vector3(m_fRotY, m_fRotX,0.f));

	//if(fMouseMoveX != 0)
	//{
	//	Vector3 vDir = { (float)fMouseMoveY , (float)fMouseMoveX, 0.f };
	//	Vector3 vAngle = m_Transform->Get_Rotation_Euler();
	//	vAngle += vDir * m_fSensitive * dTime;

	//	m_Transform->Set_Rotation(vAngle);
	//}
	
	////////////////////
	//m_Transform->RotateY(fMouseMoveX * m_fSensitive * dTime);
	//m_Transform->RotateX(fMouseMoveY *m_fSensitive * dTime);

	///////////////////
	//Vector3 vUp = m_Transform->Get_Up();
	//Vector3 vRight = m_Transform->Get_Right();
	//m_Transform->RotateAxis(vUp, D3DXToRadian(fMouseMoveX) * m_fSensitive * dTime);
	//m_Transform->RotateAxis(vRight, D3DXToRadian(fMouseMoveY)* m_fSensitive * dTime);
}

