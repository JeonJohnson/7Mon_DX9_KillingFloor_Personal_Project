#include "stdafx.h"
#include "..\Header\Player_Move.h"

#include "NaviMesh.h"

Player_Move::Player_Move(Desc * _desc)
{
	m_fWalkSpd = _desc->fWalkSpd;
	m_fSprintSpd = _desc->fSprintSpd;
	m_pNaviMesh = _desc->pNaviMesh;
}

Player_Move::~Player_Move()
{
}

void Player_Move::Initialize()
{
}

void Player_Move::Update()
{
	Move();

	DEBUG_LOG(L"Player Pos : "
		+ to_wstring(m_Transform->Get_Position().x) + L"/"
		+ to_wstring(m_Transform->Get_Position().y) + L"/"
		+ to_wstring(m_Transform->Get_Position().z) + L"/");
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

void Player_Move::Move()
{
	m_fCurSpd = m_fWalkSpd;

	if (KeyPress(KEY_STATE_Lshift))
	{
		m_fCurSpd = m_fSprintSpd;
	}

	Vector3	vPos = m_Transform->Get_Position();
	Vector3 vForward = m_Transform->Get_Forward();
	vForward.y = 0.f;
	Vector3 vRight = m_Transform->Get_Right();
	vRight.y = 0.f;

	//if (KeyPress(KEY_STATE_W))
	//{
	//	m_Transform->Add_Position(vForward * m_fCurSpd * fTime);
	//}
	//if (KeyPress(KEY_STATE_S))
	//{
	//	m_Transform->Add_Position(vForward * m_fCurSpd * fTime * -1.f);
	//}
	//if (KeyPress(KEY_STATE_D))
	//{
	//	m_Transform->Add_Position(vRight* m_fCurSpd * fTime);
	//}
	//if (KeyPress(KEY_STATE_A))
	//{
	//	m_Transform->Add_Position(vRight* m_fCurSpd * fTime * -1.f);
	//}


	if (KeyPress(KEY_STATE_D))
	{
		m_Transform->Set_Position(m_pNaviMesh->MoveOn(vPos, vRight * fTime * m_fCurSpd * 1));
	}
	else if (KeyPress(KEY_STATE_A))
	{
		m_Transform->Set_Position(m_pNaviMesh->MoveOn(vPos, vRight * fTime * m_fCurSpd * -1));
	}

	if (KeyPress(KEY_STATE_W))
	{
		m_Transform->Set_Position(m_pNaviMesh->MoveOn(vPos, vForward * fTime * m_fCurSpd));
	}
	else if (KeyPress(KEY_STATE_S))
	{
		m_Transform->Set_Position(m_pNaviMesh->MoveOn(vPos, vForward * fTime * m_fCurSpd * -1));
	}

}

void Player_Move::Set_NaviMesh(NaviMesh * _NaviMesh)
{
	m_pNaviMesh = _NaviMesh;
}
