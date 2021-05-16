#include "stdafx.h"
#include "..\Header\Bullet_Move.h"
#include "SphereCollider.h"
#include "Zed_Status.h"
#include "Zed.h"


Bullet_Move::Bullet_Move(Desc * _desc)
{
	m_fSpd = _desc->Spd;
	m_iDmg = _desc->Dmg;
}

Bullet_Move::~Bullet_Move()
{
}

void Bullet_Move::Initialize()
{
}

void Bullet_Move::Update()
{

	if (m_pCol == nullptr)
	{
		m_pCol = m_GameObject->Get_Component<SphereCollider>();
	}
	ColCheck_Zeds();



	m_fTime += fTime;
	
	if (m_fTime >= 5.f)
	{
		m_GameObject->Set_Alive(false);
	}

	Vector3	vDir = m_Transform->Get_Forward() * fTime * m_fSpd;
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

void Bullet_Move::ColCheck_Zeds()
{
	auto pZeds = EngineFunction->Get_GameObjectListbyTag(OBJECT_TAG_ZED);

	for (auto& zed : pZeds)
	{
		if (m_pCol->Collision_Check(zed, L"Body"))
		{
			if (auto pStatus = zed->Get_Component<Zed>())
			{
				pStatus->Damaged(m_iDmg);
			}
			m_pCol->Set_Check(false);

			m_GameObject->Set_Alive(false);
			return;
		}
	}

	
}
