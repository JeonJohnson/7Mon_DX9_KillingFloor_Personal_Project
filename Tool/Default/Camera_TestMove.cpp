#include "stdafx.h"
#include "Camera_TestMove.h"


Camera_TestMove::Camera_TestMove(Desc * _desc)
{
	m_fMouseX_Sen = _desc->fMouseXSen;
	m_fMouseY_Sen = _desc->fMouseYSen;

	m_fMoveSpd = _desc->fMoveSpd;
	m_fSprintSpd = _desc->fSprintSpd;
	m_fOriginSpd = m_fMoveSpd;
}

Camera_TestMove::~Camera_TestMove()
{
}

void Camera_TestMove::Initialize()
{
}

void Camera_TestMove::Update()
{
	
	Move();
	Look();


}

void Camera_TestMove::LateUpdate()
{
}

void Camera_TestMove::ReadyRender()
{
}

void Camera_TestMove::Release()
{
}

void Camera_TestMove::Move()
{
	if (KeyDown(KEY_STATE_Lshift))
	{
		m_fMoveSpd *= m_fSprintSpd;
	}
	if (KeyUp(KEY_STATE_Lshift))
	{
		m_fMoveSpd = m_fOriginSpd;
	}

	if (KeyPress(KEY_STATE_W))
	{
		Vector3 vDir = m_Transform->Get_Forward() * dTime * m_fMoveSpd;
		m_Transform->Add_Position(vDir);

	}
	if (KeyPress(KEY_STATE_S))
	{
		Vector3 vDir = m_Transform->Get_Forward() * dTime * -m_fMoveSpd;
		m_Transform->Add_Position(vDir);
	}

	if (KeyPress(KEY_STATE_A))
	{
		Vector3 vDir = m_Transform->Get_Right() * dTime * -m_fMoveSpd;
		m_Transform->Add_Position(vDir);
	}

	if (KeyPress(KEY_STATE_D))
	{
		Vector3 vDir = m_Transform->Get_Right() * dTime * m_fMoveSpd;
		m_Transform->Add_Position(vDir);
	}

	
}

void Camera_TestMove::Look()
{
	float fMouseMoveX = MouseMove(KEY_STATE_MouseX) * dTime * m_fMouseX_Sen;
	float fMouseMoveY = MouseMove(KEY_STATE_MouseY)* dTime * m_fMouseX_Sen;

	//m_Transform->RotateY(fMouseMoveX * dTime);
	//m_Transform->RotateX(fMouseMoveY * dTime);

	Vector3 vUp = m_Transform->Get_Up();
	Vector3 vRight = m_Transform->Get_Right();

	m_Transform->RotateAxis(vUp, D3DXToRadian(fMouseMoveX));
	m_Transform->RotateAxis(vRight, D3DXToRadian( fMouseMoveY));
}

