#include "stdafx.h"
#include "..\Header\Player_TestMove.h"


Player_TestMove::Player_TestMove(Desc * _desc)
{
}

Player_TestMove::~Player_TestMove()
{
}

void Player_TestMove::Initialize()
{
}

void Player_TestMove::Update()
{
	Move_Test();

	
	m_Transform->Add_PosY(MouseMove(KEY_STATE_WHEEL) * dTime);

	if(MouseDown(KEY_STATE_LMouse))
	{
		m_Transform->Add_PosY(10.f * dTime);
	}
}

void Player_TestMove::LateUpdate()
{
}

void Player_TestMove::ReadyRender()
{
}

void Player_TestMove::Release()
{
}

void Player_TestMove::Move_Test()
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
