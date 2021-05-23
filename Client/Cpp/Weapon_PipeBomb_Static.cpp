#include "stdafx.h"
#include "..\Header\Weapon_PipeBomb_Static.h"
#include "BulletManager.h"


Weapon_PipeBomb_Static::Weapon_PipeBomb_Static(Desc * _desc)
{
	Vector3 vAdd = _desc->vPlayerDown + _desc->vPlayerForward;
	

	//m_vDir = vAdd - _desc->vPlayerPos;
	m_vDir = vAdd - Vector3(0.f, 0.f, 0.f);
	D3DXVec3Normalize(&m_vDir, &m_vDir);

	m_fSpd = _desc->fSpd;

	m_fMaxTime = _desc->fMaxTime;

	m_iDmg = _desc->iDmg;


}

Weapon_PipeBomb_Static::~Weapon_PipeBomb_Static()
{
}

void Weapon_PipeBomb_Static::Initialize()
{
}

void Weapon_PipeBomb_Static::Update()
{
	Throw();
	Bomb();
}

void Weapon_PipeBomb_Static::LateUpdate()
{
}

void Weapon_PipeBomb_Static::ReadyRender()
{
}

void Weapon_PipeBomb_Static::Release()
{
}

void Weapon_PipeBomb_Static::Throw()
{
	if (m_Transform->Get_Position().y >= -1.f)
	{
		m_Transform->Add_Position(m_vDir * m_fSpd * fTime);
	}
	

	if (m_Transform->Get_Position().y <= -1.f)
	{
		m_Transform->Set_RotationX(0.f);
		m_Transform->Set_RotationZ(0.f);
		m_bCountDown = true;
	}

}

void Weapon_PipeBomb_Static::Bomb()
{
	if (m_bCountDown)
	{
		m_fBombTime += fTime;

		if (m_fBombTime >= m_fMaxTime)
		{
			BulletManager::Get_Instance()->Create_Explosion(m_Transform->Get_Position(), m_iDmg, 0.f);
			m_GameObject->Set_Alive(false);
		}
	}
}
