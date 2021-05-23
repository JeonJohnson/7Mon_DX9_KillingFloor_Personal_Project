
#include "stdafx.h"
#include "..\Header\Camera_FPS.h"
#include "ShopManager.h"

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

	Vector3 vforward = m_Transform->Get_Forward();
		DEBUG_LOG(L"Player Forward : " + to_wstring(vforward.x) + L", "
			+ to_wstring(vforward.y) + L", "
			+ to_wstring(vforward.z));

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

	if (!ShopManager::Get_Instance()->Get_ShopOn())
	{
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

}

void Camera_FPS::Recoil(float _fRecoilPower)
{

	int RandX = rand() % 2;
	//float RandY = rand() % 2;
	
	if (RandX == 0)
	{
		m_fRotX += _fRecoilPower / 15.f;
	}
	else 
	{
		m_fRotX -= _fRecoilPower / 15.f;
	}

// 	if (RandY == 0)
// 	{
		m_fRotY -= _fRecoilPower / 10.f;
	//}
	//else 
	//{
	//	m_fRotY -= _fRecoilPower / 10.f;
	//}
	



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

