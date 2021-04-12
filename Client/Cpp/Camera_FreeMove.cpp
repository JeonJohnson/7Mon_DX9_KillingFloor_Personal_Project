#include "stdafx.h"
#include "..\Header\Camera_FreeMove.h"


Camera_FreeMove::Camera_FreeMove(Desc * _desc)
{
}

Camera_FreeMove::~Camera_FreeMove()
{
}

void Camera_FreeMove::Initialize()
{
}

void Camera_FreeMove::Update()
{
	
	Move();
	Look();

	

	//if (GetAsyncKeyState(VK_UP) & 0x8000)
	//{
	//	m_Transform->Add_PosY(5.f * dTime);
	//}

	//if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	//{
	//	m_GameObject->Get_Component<Camera>()->Get_Transform()->Add_PosY(-5.f* dTime);
	//}

	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//{
	//	m_GameObject->Get_Component<Camera>()->Get_Transform()->Add_PosX(5.f* dTime);
	//}

	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//{
	//	m_GameObject->Get_Component<Camera>()->Get_Transform()->Add_PosX(-5.f* dTime);
	//}

	//if (GetAsyncKeyState('N') & 0x8000)
	//{
	//	m_GameObject->Get_Component<Camera>()->Get_Transform()->Add_PosZ(5.f* dTime);
	//}
	//if (GetAsyncKeyState('M') & 0x8000)
	//{
	//	m_GameObject->Get_Component<Camera>()->Get_Transform()->Add_PosZ(-5.f* dTime);
	//}


}

void Camera_FreeMove::LateUpdate()
{
}

void Camera_FreeMove::ReadyRender()
{
}

void Camera_FreeMove::Release()
{
}

void Camera_FreeMove::Move()
{
	if (KeyPress(KEY_STATE_W))
	{
		//m_Transform->Add_PosZ(15.f * dTime);
		Vector3 vDir = m_Transform->Get_Forward() * dTime *10.f;
		m_Transform->Add_Position(vDir);

	}
	if (KeyPress(KEY_STATE_S))
	{
		Vector3 vDir = m_Transform->Get_Forward() * dTime * -10.f;
		m_Transform->Add_Position(vDir);
	}

	if (KeyPress(KEY_STATE_A))
	{
		Vector3 vDir = m_Transform->Get_Right() * dTime *-10.f;
		m_Transform->Add_Position(vDir);
	}

	if (KeyPress(KEY_STATE_D))
	{
		Vector3 vDir = m_Transform->Get_Right() * dTime *10.f;
		m_Transform->Add_Position(vDir);
	}

	
}

void Camera_FreeMove::Look()
{
	float fMouseMoveX = MouseMove(KEY_STATE_MouseX) * 30.f;
	float fMouseMoveY = MouseMove(KEY_STATE_MouseY) * 30.f;

	m_Transform->RotateY(fMouseMoveX * dTime);
	m_Transform->RotateX(fMouseMoveY * dTime);

	//Áü¹ú¶ô ³ª¿È -> 
}

