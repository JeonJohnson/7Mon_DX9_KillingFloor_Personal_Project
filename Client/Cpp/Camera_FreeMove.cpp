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
