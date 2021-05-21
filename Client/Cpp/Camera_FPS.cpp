
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
	//int fMouseMoveX = MouseMove(KEY_STATE_MouseX);
	//int fMouseMoveY = MouseMove(KEY_STATE_MouseY);

	LONG	lMouseMoveX = Engine_Mother::Get_Instance()->GetMouseMoveX();
	LONG	lMouseMoveY = Engine_Mother::Get_Instance()->GetMouseMoveY();
	
	DEBUG_LOG(L"MouseX : " + to_wstring(lMouseMoveX));
	DEBUG_LOG(L"MouseY : " + to_wstring(lMouseMoveY));


	m_fRotX += lMouseMoveX * m_fSensitive * fTime;
	m_fRotY += lMouseMoveY * m_fSensitive * fTime;

	DEBUG_LOG(L"RotX : " + to_wstring(m_fRotX));
	DEBUG_LOG(L"RotY : " + to_wstring(m_fRotY));

	
	//if (KeyPress(KEY_STATE_Up))
	//{
	//	m_fRotY -= m_fSensitive * fTime * 2.f;
	//}
	//if (KeyPress(KEY_STATE_Down))
	//{
	//	m_fRotY += m_fSensitive * fTime * 2.f;
	//}

	//if (KeyPress(KEY_STATE_Right))
	//{
	//	m_fRotX+= m_fSensitive * fTime * 2.f;
	//}
	//if (KeyPress(KEY_STATE_Left))
	//{
	//	m_fRotX -= m_fSensitive * fTime* 2.f ;
	//}


	//m_fRotZ -= asinf(fMouseMoveX) * 2.f / 3.14159265f * 450 * dTime;

	if (m_fRotY >= 70.f)
	{
		m_fRotY = 70.f;
	}

	if (m_fRotY <= -70.f)
	{
		m_fRotY = -70.f;
	}

	m_Transform->Set_Rotation(Vector3(m_fRotY, m_fRotX, m_fRotZ));

}

