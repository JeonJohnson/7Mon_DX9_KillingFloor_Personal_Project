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

	
	m_Transform->Add_PosY(MouseMove(KEY_STATE_WHEEL) * dTime);

	if(MouseDown(KEY_STATE_LMouse))
	{
		m_Transform->Add_PosY(10.f * dTime);
	}
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

	//if (KeyPress(DIK_W))
	//{
	//	m_Transform->Add_PosY(5.f * dTime);
	//}

	//if (KeyPress(DIK_S))
	//{
	//	m_Transform->Add_PosY(-5.f* dTime);
	//}

	//if (KeyPress(DIK_D))
	//{
	//	m_Transform->Add_PosX(5.f* dTime);
	//}

	//if (KeyPress(DIK_A))
	//{
	//	m_Transform->Add_PosX(-5.f* dTime);
	//}

	//if (KeyPress(DIK_Q))
	//{
	//	m_Transform->Add_PosZ(5.f* dTime);
	//}

	//if (KeyPress(DIK_E))
	//{
	//	m_Transform->Add_PosZ(-5.f* dTime);
	//}


}
