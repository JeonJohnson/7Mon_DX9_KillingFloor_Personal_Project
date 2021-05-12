#include "stdafx.h"
#include "..\Header\Bullet_Move.h"


Bullet_Move::Bullet_Move(Desc * _desc)
{
	m_fSpd = _desc->Spd;
}

Bullet_Move::~Bullet_Move()
{
}

void Bullet_Move::Initialize()
{
}

void Bullet_Move::Update()
{

	m_fTime += fTime;
	
	if (m_fTime >= 15.f)
	{
		m_GameObject->Set_Alive(false);
	}

	Vector3	vDir = m_Transform->Get_Forward() * dTime * m_fSpd;
	m_Transform->Add_Position(vDir);
}

void Bullet_Move::LateUpdate()
{
}

void Bullet_Move::ReadyRender()
{
}

void Bullet_Move::Release()
{
}
