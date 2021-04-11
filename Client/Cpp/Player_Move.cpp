#include "stdafx.h"
#include "..\Header\Player_Move.h"


Player_Move::Player_Move(Desc * _desc)
{
}

Player_Move::~Player_Move()
{
}

void Player_Move::Initialize()
{
}

void Player_Move::Update()
{
	Move_Test();


	
}

void Player_Move::LateUpdate()
{
}

void Player_Move::ReadyRender()
{
}

void Player_Move::Release()
{
}

void Player_Move::Move_Test()
{
	/* Test */

	if (KeyPress(DIK_W))
	{
		m_Transform->Add_PosY(5.f * dTime);
	}

	if (KeyPress(DIK_S))
	{
		m_Transform->Add_PosY(-5.f* dTime);
	}

	if (KeyPress(DIK_D))
	{
		m_Transform->Add_PosX(5.f* dTime);
	}

	if (KeyPress(DIK_A))
	{
		m_Transform->Add_PosX(-5.f* dTime);
	}

	if (KeyPress(DIK_Q))
	{
		m_Transform->Add_PosZ(5.f* dTime);
	}

	if (KeyPress(DIK_E))
	{
		m_Transform->Add_PosZ(-5.f* dTime);
	}



	//if (GetAsyncKeyState('W') & 0x8000)
	//{
	//	m_Transform->Add_PosY(5.f * dTime);
	//}

	//if (GetAsyncKeyState('S') & 0x8000)
	//{
	//	m_Transform->Add_PosY(-5.f* dTime);
	//}

	//if (GetAsyncKeyState('D') & 0x8000)
	//{
	//	m_Transform->Add_PosX(5.f* dTime);
	//}

	//if (GetAsyncKeyState('A') & 0x8000)
	//{
	//	m_Transform->Add_PosX(-5.f* dTime);
	//}

	//if (GetAsyncKeyState('Q') & 0x8000)
	//{
	//	m_Transform->Add_PosZ(5.f* dTime);
	//}
	//if (GetAsyncKeyState('E') & 0x8000)
	//{
	//	m_Transform->Add_PosZ(-5.f* dTime);
	//}
	/* Test */
}
